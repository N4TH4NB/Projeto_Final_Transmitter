#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

// Definições de cabeçalhos UBX
const unsigned char UBX_HEADER[] = {0xB5, 0x62};
const unsigned char NAV_POSLLH_HEADER[] = {0x01, 0x02};
const unsigned char NAV_STATUS_HEADER[] = {0x01, 0x03};
const unsigned char NAV_TIMEUTC_HEADER[] = {0x01, 0x21};

const unsigned char UBLOX_INIT[] PROGMEM = {
    // Disable NMEA
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x24, // GxGGA off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B, // GxGLL off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32, // GxGSA off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39, // GxGSV off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40, // GxRMC off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x47, // GxVTG off

    // Disable UBX
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xDC, // NAV-PVT off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0xB9, // NAV-POSLLH off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0xC0, // NAV-STATUS off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x92, // NAV-TIMEUTC off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xFB, // NAV-SVINFO off

    // Enable UBX
    // 0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x18, 0xE1, // NAV-PVT on
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x13, 0xBE, // NAV-POSLLH on
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x14, 0xC5, // NAV-STATUS on
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x21, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x32, 0x97, // NAV-TIMEUTC on
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x30, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, // NAV-SVINFO on

    // Rate
    // 0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12, //(10Hz)
    // 0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x01, 0x00, 0xDE, 0x6A, //(5Hz)
    0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x01, 0x00, 0x01, 0x39, //(1Hz)

    // 0xB5, 0x62, 0x06, 0x23, 0x28, 0x00, 0x00, 0x00, 0x4C, 0x66, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, // AssistNow Autonomous on
    // 0x03, 0x10, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 0x00, 0x01, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x6A,

    // 0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // load Almanac and AssistNow Autonomous data from eeprom
    // 0x02, 0x20, 0x17, 0x55, 0x16,
    0xB5, 0x62, 0x06, 0x11, 0x02, 0x00, 0x08, 0x01, 0x22, 0x92, //Power Save Mode
};

const unsigned char UBLOX_OFF[] PROGMEM = {
    // Desligar GPS até mudança no RX
    0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4D, 0x3B};

const unsigned char UBLOX_SAVE[] PROGMEM = {
    // Supostamente salva na EEPROM kekw
    0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00,
    0x00, 0x00, 0x17, 0x55, 0x9E};

// Tipos de mensagens UBX
enum _ubxMsgType
{
    MT_NONE,
    MT_NAV_POSLLH,
    MT_NAV_STATUS,
    MT_NAV_TIMEUTC
};

// Estrutura de NAV-POSLLH
struct NAV_POSLLH
{
    unsigned char cls;
    unsigned char id;
    unsigned short len;
    unsigned long iTOW; // GPS time of week of the navigation epoch (ms)
    long lon;           // Longitude (deg)
    long lat;           // Latitude (deg)
    long height;        // Height above Ellipsoid (mm)
    long hMSL;          // Height above mean sea level (mm)
    unsigned long hAcc; // Horizontal Accuracy Estimate (mm)
    unsigned long vAcc; // Vertical Accuracy Estimate (mm)
};

// Estrutura de NAV-STATUS
struct NAV_STATUS
{
    unsigned char cls;
    unsigned char id;
    unsigned short len;
    unsigned long iTOW; // GPS time of week of the navigation epoch (ms)
    unsigned char gpsFix;
    char flags; // Fix Status Flags
    char fixStat;
    char flags2; // Fix Status Flags
    unsigned long ttff;
    unsigned long msss;
};

struct NAV_TIMEUTC
{
    unsigned char cls;
    unsigned char id;
    unsigned short len;
    unsigned long iTOW;   // GPS time of week of the navigation epoch (ms)
    unsigned long tAcc;   // Time accuracy estimate (UTC) (ns)
    long nano;            // Fraction of second, range -1e9 .. 1e9 (UTC) (ns)
    unsigned short year;  // Year (UTC)
    unsigned char month;  // Month, range 1..12 (UTC)
    unsigned char day;    // Day of month, range 1..31 (UTC)
    unsigned char hour;   // Hour of day, range 0..23 (UTC)
    unsigned char minute; // Minute of hour, range 0..59 (UTC)
    unsigned char second; // Seconds of minute, range 0..60 (UTC)
    char valid;           // Validity Flags (see graphic below)
};

// União para representar mensagens UBX
union UBXMessage
{
    NAV_POSLLH navPosllh;
    NAV_STATUS navStatus;
    NAV_TIMEUTC navTimeUTC;
};

// Declarações externas
extern UBXMessage ubxMessage;
extern const unsigned char UBX_HEADER[];
extern const unsigned char NAV_POSLLH_HEADER[];
extern const unsigned char NAV_STATUS_HEADER[];
extern const unsigned char NAV_TIMEUTC_HEADER[];

// Declaração de funções
int processGPS();
void calcChecksum(unsigned char *CK);

#endif
