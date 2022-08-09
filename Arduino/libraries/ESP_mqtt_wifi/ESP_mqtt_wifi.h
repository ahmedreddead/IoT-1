#ifndef ESP_mqtt_wifi_H
#define ESP_mqtt_wifi_H

#include <PubSubClient.h>

#include <WiFi.h>

PubSubClient get_mqtt_object();

void setup_wifi(char *ssid ,char *password );

void set_mqtt_server (char *mqtt_server,int port);

void reconnect();

void mqtt_publish (char *topic, const char *message);






#endif
