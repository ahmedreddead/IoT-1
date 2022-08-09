

// Set GPIOs for H-bridge 
const int vcc = 26;
const int gnd = 27;

// M1 POSITIVE 

RTC_DATA_ATTR int bootCount = 0;


#include "Micropolis_switch.h"

char* sensor_id = "1C";


char* ssid = "MICROPOLIS";
char* password = "Micropolis@212";
char* mqtt_server = "10.20.0.31";
int mqtt_port = 1883;

Micropolis_switch switch_object(vcc,gnd,sensor_id);

void setup() {
    Serial.begin(115200);
    switch_object.setup_wifi(ssid, password);
    switch_object.set_mqtt_server (mqtt_server, mqtt_port);
    reconnect();
    switch_object.mqtt_publish("Micropolis/switch", "online");
    switch_object.switch_on();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  loop_client();

}
