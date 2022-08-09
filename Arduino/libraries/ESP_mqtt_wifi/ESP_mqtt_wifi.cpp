
#include "ESP_mqtt_wifi.h"

#include <WiFi.h>
#include <PubSubClient.h>


WiFiClient espClient;
PubSubClient client(espClient);

int vcc , gnd ;

PubSubClient get_mqtt_object()
{
  return client;
}

void set_mqtt_server (char *mqtt_server, int port)
{
   client.setServer(mqtt_server, 1883);
}

void mqtt_publish (char *topic, const char *message)
{
   client.publish(topic, message);
}

void setup_wifi(char *ssid ,char *password ) {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  Serial.printf("pass the begin");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("sensor")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("sensor_test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}





