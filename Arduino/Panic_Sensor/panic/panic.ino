
// Set GPIOs for LED and PIR Motion Sensor
const int Push_button = 4;


RTC_DATA_ATTR int bootCount = 0;


#include "ESP_mqtt_wifi.h"
char* ssid = "MICROPOLIS";
char* password = "Micropolis@212";
char* mqtt_server = "10.20.0.31";
int mqtt_port = 1883;


void setup() {

  Serial.begin(115200);
  pinMode(Push_button, INPUT_PULLUP);  
  setup_wifi(ssid, password);
  set_mqtt_server (mqtt_server, mqtt_port);
  reconnect();

  if (! bootCount) {
    bootCount++;
    Serial.println("booting ............");
    }
  else{
    mqtt_publish("Micropolis/panic_sensor", "Alarm_ON"); 
    }
    
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4,1); 
    Serial.println("Going to sleep now");
    delay(1000);
    esp_deep_sleep_start();
    
  
}

void loop() {

}
