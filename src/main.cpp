#include "config.h"
#include "gps.h"
#include "wifi_espnow.h"
#include "sensors.h"

RTC_DATA_ATTR int bootCount = 0;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);

  delay(1000);

  inicializaWifi();
  inicializaSensores();
  configuraGPS(UBLOX_INIT);

  Serial.println("GPS configurado");

  bootCount++;
  Serial.println("Boot number: " + String(bootCount));

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("ESP32 definido para dormir por " + String(TIME_TO_SLEEP) + " segundos");
  delay(4000);
}

void loop()
{
  struct_message myData;
  if (processGPS())
  {
    myData = coletaDados();
    myData.lon = navPosllh.lon;
    myData.lat = navPosllh.lat;
    myData.hora = navPosllh.iTOW;
  }
  else
  {
    Serial.println("Deu erro nessa bagaça");
  }

  if (enviaDados(myData))
  {
    Serial.println("Dados enviados com sucesso");
    configuraGPS(UBLOX_OFF);
    Serial.println("GPS desligado");
  }
  else
  {
    Serial.println("Erro ao enviar dados");
  }

  delay(5000);
  Serial.println("a mimir");
  esp_deep_sleep_start();
}
