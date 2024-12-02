#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "gps.h"

// Sensores e variáveis
Adafruit_BMP085 bmp;
const int rainSensorPin = 34;
const int ldrPin = 35;
const int batteryPin = 32;

// Estrutura de dados enviada
typedef struct SensorData
{
  float temperatura;
  float pressao;
  int luminosidade;
  int chuva;
  int bateria;
  long latitude;
  long longitude;
  unsigned short ano;
  unsigned char mes, dia, hora, minuto, segundo;
} SensorData;

SensorData sensorData;

// Callback de envio ESP-NOW
void onSent(const uint8_t *macAddr, esp_now_send_status_t status)
{
  if (status == ESP_NOW_SEND_SUCCESS)
  {
    Serial.println("Enviado com sucesso");
    // esp_deep_sleep(60 * 1000000); // 1 minuto de sono profundo
  }
}

// Configuração ESP-NOW
void initEspNow()
{
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Erro ao inicializar ESP-NOW");
    ESP.restart();
  }
  else
  {
    Serial.println("ESP-NOW inicializado com sucesso");
  }

  esp_now_register_send_cb(onSent);
  // Adiciona receptor
  uint8_t peerAddress[] = {0xA0, 0xB7, 0x65, 0x6B, 0x50, 0xA8};
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.println("Inicializando...");

  for (unsigned int i = 0; i < sizeof(UBLOX_INIT); i++)
  {
    Serial2.write(pgm_read_byte(UBLOX_INIT + i));
    delay(5); // simulating a 38400baud pace (or less), otherwise commands are not accepted by the device.
  }
  Serial.println("GPS inicializado");

  // Inicializar sensores
  if (!bmp.begin())
  {
    Serial.println("Erro ao inicializar o BMP085");
    while (1)
      ;
  }

  initEspNow();
  Serial.println("Finalizando inicialização...");
}

void loop()
{
  // Ler GPS
  int gpsMessage = processGPS();
  if (gpsMessage == MT_NAV_POSLLH)
  {
    sensorData.latitude = ubxMessage.navPosllh.lat;
    sensorData.longitude = ubxMessage.navPosllh.lon;
  }
  else if (gpsMessage == MT_NAV_TIMEUTC)
  {
    sensorData.ano = ubxMessage.navTimeUTC.year;
    sensorData.mes = ubxMessage.navTimeUTC.month;
    sensorData.dia = ubxMessage.navTimeUTC.day;
    sensorData.hora = ubxMessage.navTimeUTC.hour;
    sensorData.minuto = ubxMessage.navTimeUTC.minute;
    sensorData.segundo = ubxMessage.navTimeUTC.second;
  }

  // Ler outros sensores
  sensorData.temperatura = bmp.readTemperature();
  sensorData.pressao = bmp.readPressure() / 101300.00;
  sensorData.chuva = analogRead(rainSensorPin);
  sensorData.luminosidade = int(100 - (analogRead(ldrPin) * (3.3 / 4096) * 65));
  sensorData.bateria = analogRead(batteryPin) * (3.3 / 4096);

  // Enviar dados via ESP-NOW
  esp_now_send(NULL, (uint8_t *)&sensorData, sizeof(sensorData));
  delay(100); // Aguardar antes de novo envio (em caso de erro)
}
