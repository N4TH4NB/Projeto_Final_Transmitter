#include "config.h"
#include "gps.h"
#include "wifi_espnow.h"
#include "sensors.h"

RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR long lon, lat;

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
  delay(2000);
}

void loop()
{

  struct_message myData;
  if (processGPS())
  {
    if (bootCount == 1 && ubxMessage.navStatus.gpsFix < 2)
    {
      // while (1)
      //   ;
    }
    else if (ubxMessage.navStatus.gpsFix > 1)
    {
      lon = ubxMessage.navPosllh.lon;
      lat = ubxMessage.navPosllh.lat;
    }

    if (ubxMessage.navTimeUTC.year > 2020 && ubxMessage.navTimeUTC.year < 2050)
    {
      myData.ano = ubxMessage.navTimeUTC.year;
      myData.mes = ubxMessage.navTimeUTC.day;
      myData.dia = ubxMessage.navTimeUTC.month;
      myData.hora = ubxMessage.navTimeUTC.hour;
      myData.minuto = ubxMessage.navTimeUTC.minute;
      myData.segundo = ubxMessage.navTimeUTC.second;
    }
  }
  myData.lon = lon;
  myData.lat = lat;
  myData = coletaDados();
  if (enviaDados(myData))
  {
    Serial.println("Dados enviados com sucesso");
  }
  else
  {
    Serial.println("Erro ao enviar dados");
  }

  //    Serial.println("a mimir");
  //    esp_deep_sleep_start();

  /*while (Serial.available() > 0)
  {
    Serial2.write(Serial.read());
  }

  while (Serial2.available() > 0)
  {
    Serial.write(Serial2.read());
  }*/
}
