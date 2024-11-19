#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

// Estrutura para armazenar dados GPS
struct NAV_POSLLH
{
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;
  long lon;
  long lat;
  long height;
  long hMSL;
  unsigned long hAcc;
  unsigned long vAcc;
};

extern NAV_POSLLH navPosllh;
extern const unsigned char UBX_HEADER[];
extern const char UBLOX_INIT[];
extern const char UBLOX_OFF[];

void configuraGPS(const char *UBLOX);
bool processGPS();
void calcChecksum(unsigned char *CK);

#endif
