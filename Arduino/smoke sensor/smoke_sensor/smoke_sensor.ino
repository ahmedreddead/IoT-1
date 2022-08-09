
#define timeSeconds 5

// Set GPIOs for LED and PIR Motion Sensor
const int led = 23;
const int smokeSensor = 27;

char* state = "off";

RTC_DATA_ATTR int bootCount = 0;


#include "ESP_mqtt_wifi.h"
char* ssid = "MICROPOLIS";
char* password = "Micropolis@212";
char* mqtt_server = "10.20.0.31";
int mqtt_port = 1883;

char* sensor_id = "smok45123";

String MQTT_message = String("{id:" + String(sensor_id) + ",status: Smoke Detected}");
const char* payload = MQTT_message.c_str();

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(smokeSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  // Set LED to LOW
  setup_wifi(ssid, password);
  set_mqtt_server (mqtt_server, mqtt_port);
  reconnect();

  if (! bootCount)
  {
    Serial.println("restarting");
    bootCount++;
    }
  else {
    Serial.println("smoke detected");
    mqtt_publish("Micropolis/Smoke_sensor",payload); 
    }
    
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_27,1); //1 = High, 0 = Low
  Serial.println("Going to sleep now");
  esp_deep_sleep_start();

  
}

void loop() {

}
