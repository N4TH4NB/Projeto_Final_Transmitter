#include "sensors.h"

// Instâncias dos sensores
Adafruit_MLX90614 Sensor_temp = Adafruit_MLX90614();
Adafruit_BMP085 Sensor_baro = Adafruit_BMP085();

// Variável para calcular média da tensão
unsigned long ultimoMillisMediaTensao = 0;

void inicializaSensores()
{
  if (!Sensor_temp.begin())
  {
    Serial.println("Erro ao inicializar o sensor de temperatura.");
    // while (1);
  }
  if (!Sensor_baro.begin())
  {
    Serial.println("Erro ao inicializar o sensor barométrico.");
    // while (1);
  }
}

float mediaTensao(int pino)
{
  float soma = 0;
  int leiturasFeitas = 0;

  while (leiturasFeitas < 20)
  {
    if (millis() - ultimoMillisMediaTensao >= 2)
    {
      soma += analogRead(pino);
      leiturasFeitas++;
      ultimoMillisMediaTensao = millis();
    }
  }
  soma /= 20;
  soma *= (3.3 / 4096); // Conversão para tensão
  return soma;
}

float Sensor_lum()
{
  float tensao = mediaTensao(LDR);
  return 100 - ((tensao - 0.22) * 45);
}

float Tensao_fonte()
{
  float tensao = mediaTensao(FONTE);
  return tensao * 10.91; // Ajuste conforme o divisor de tensão usado
}

int Sensor_chuva()
{
  return analogRead(RAIN);
}

struct_message coletaDados()
{
  struct_message data;
  data.temp = Sensor_baro.readTemperature();
  data.press = Sensor_baro.readPressure();
  data.alt = Sensor_baro.readAltitude();
  data.pressMar = Sensor_baro.readSealevelPressure();
  data.lum = Sensor_lum();
  data.tensao = Tensao_fonte();
  data.chuva = Sensor_chuva();
  return data;
}
