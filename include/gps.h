#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

// Definições de cabeçalhos UBX
const unsigned char UBX_HEADER[] = {0xB5, 0x62};
const unsigned char NAV_POSLLH_HEADER[] = {0x01, 0x02};
const unsigned char NAV_STATUS_HEADER[] = {0x01, 0x03};

// Tipos de mensagens UBX
enum _ubxMsgType
{
    MT_NONE,
    MT_NAV_POSLLH,
    MT_NAV_STATUS
};

// Estrutura de NAV-POSLLH
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

// Estrutura de NAV-STATUS
struct NAV_STATUS
{
    unsigned char cls;
    unsigned char id;
    unsigned short len;
    unsigned long iTOW;
    unsigned char gpsFix;
    char flags;
    char fixStat;
    char flags2;
    unsigned long ttff;
    unsigned long msss;
};

// União para representar mensagens UBX
union UBXMessage
{
    NAV_POSLLH navPosllh;
    NAV_STATUS navStatus;
};

// Declarações externas
extern UBXMessage ubxMessage;
extern const unsigned char UBX_HEADER[];
extern const unsigned char NAV_POSLLH_HEADER[];
extern const unsigned char NAV_STATUS_HEADER[];

// Declaração de funções
int processGPS();
void calcChecksum(unsigned char *CK);

#endif
