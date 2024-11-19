#include "wifi_espnow.h"
#include "config.h"

esp_now_peer_info_t peerInfo;

void inicializaWifi()
{
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Erro ao adicionar peer");
    return;
  }
}

bool enviaDados(const struct_message &data)
{
  return esp_now_send(broadcastAddress, (uint8_t *)&data, sizeof(data)) == ESP_OK;
}
