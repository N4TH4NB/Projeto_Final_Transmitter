#ifndef WIFI_ESPNOW_H
#define WIFI_ESPNOW_H

#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message
{
  float temp;
  float press;
  float alt;
  float pressMar;
  int lum;
  float tensao;
  int chuva;
  long lon;
  long lat;
  char data[20];
} struct_message;

void inicializaWifi();
bool enviaDados(const struct_message &data);

#endif
