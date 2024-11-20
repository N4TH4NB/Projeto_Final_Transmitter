#ifndef SENSORS_H
#define SENSORS_H

#include <SPI.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_BMP085.h>
#include "config.h"
#include "wifi_espnow.h"

// Inicialização dos sensores
void inicializaSensores();

// Coleta dados de todos os sensores
struct_message coletaDados();

// Conversões para sensores analógicos
float mediaTensao(int pino);
float Sensor_lum();
float Tensao_fonte();
int Sensor_chuva();
void Sensor_temp_print();
void Sensor_baro_print();

#endif
