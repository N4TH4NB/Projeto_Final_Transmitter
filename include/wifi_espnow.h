#ifndef WIFI_ESPNOW_H
#define WIFI_ESPNOW_H

#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message
{
  float temp = 0.0;
  float press = 0.0;
  float alt = 0.0;
  int lum = 0;
  float tensao = 0.0;
  int chuva = 0;
  long lon = 0;
  long lat = 0;
  unsigned short ano = 0;
  unsigned char mes = 0;
  unsigned char dia = 0;
  unsigned char hora = 0;
  unsigned char minuto = 0;
  unsigned char segundo = 0;
} struct_message;

void inicializaWifi();
bool enviaDados(const struct_message &data);

#endif
