#include "config.h"
#include "gps.h"
#include "wifi_espnow.h"
#include "sensors.h"

RTC_DATA_ATTR int bootCount = 0;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  for (unsigned int i = 0; i < sizeof(UBLOX_INIT); i++)
  {
    Serial2.write(pgm_read_byte(UBLOX_INIT + i));
    delay(5); // simulating a 38400baud pace (or less), otherwise commands are not accepted by the device.
  }

  delay(1000);
  inicializaWifi();
  inicializaSensores();

  bootCount++;
  Serial.println("Boot number: " + String(bootCount));

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("ESP32 definido para dormir por " + String(TIME_TO_SLEEP) + " segundos");
  delay(4000);
}

void loop()
{
  //struct_message myData;

  //myData = coletaDados();

  int msgType = processGPS();
  if (msgType == MT_NAV_POSLLH)
  {
    Serial.print("iTOW:");
    Serial.print(ubxMessage.navPosllh.iTOW);
    Serial.print(" lat/lon: ");
    Serial.print(ubxMessage.navPosllh.lat / 10000000.0f, 12);
    Serial.print(",");
    Serial.print(ubxMessage.navPosllh.lon / 10000000.0f, 12);
    Serial.print(" hAcc: ");
    Serial.print(ubxMessage.navPosllh.hAcc / 1000.0f);
    Serial.println();
  }
  else if (msgType == MT_NAV_STATUS)
  {
    Serial.print("gpsFix:");
    Serial.print(ubxMessage.navStatus.gpsFix);
    Serial.println();
  }
  else if (msgType == MT_NAV_TIMEUTC)
  {
    Serial.print("Hora: ");
    Serial.print(ubxMessage.navTimeUTC.hour);
    Serial.print(":");
    Serial.print(ubxMessage.navTimeUTC.minute);
    Serial.print(":");
    Serial.print(ubxMessage.navTimeUTC.second);
    Serial.print("\tDia: ");
    Serial.print(ubxMessage.navTimeUTC.day);
    Serial.print("/");
    Serial.print(ubxMessage.navTimeUTC.month);
    Serial.print("/");
    Serial.print(ubxMessage.navTimeUTC.year);
    Serial.println();
  }
  // Sensor_temp_print();
  // Sensor_baro_print();
  // Sensor_chuva_print();
  /*if (enviaDados(myData))
  {
    Serial.println("Dados enviados com sucesso");
  }
  else
  {
    Serial.println("Erro ao enviar dados");
  }*/

  delay(100);
  //   Serial.println("a mimir");
  //   esp_deep_sleep_start();
}
