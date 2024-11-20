#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Definições de pinos
#define LDR 32
#define RAIN 34
#define FONTE 35

// Fatores e constantes
#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 5

// Endereço para ESP-NOW
const uint8_t broadcastAddress[] = {0xA0, 0xB7, 0x65, 0x6B, 0x50, 0xA8};

#endif
