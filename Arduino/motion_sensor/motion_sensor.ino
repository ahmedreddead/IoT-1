
#define timeSeconds 5

// Set GPIOs for LED and PIR Motion Sensor
const int led = 23;
const int motionSensor = 27;

char* state = "off";
// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
RTC_DATA_ATTR int bootCount = 0;


#include "ESP_mqtt_wifi.h"
char* ssid = "MICROPOLIS";
char* password = "Micropolis@212";
char* mqtt_server = "10.20.0.31";
int mqtt_port = 1883;

char* sensor_id = "Mo45123";

String MQTT_message = String("{id:" + String(sensor_id) + ",status: Motion Detected}");
const char* payload = MQTT_message.c_str();

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  // Set LED to LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
  if (! bootCount)
  {
    Serial.println("restarting");
    bootCount++;
    }
  else {
    Serial.println("Motion detected");
    }
    setup_wifi(ssid, password);
    set_mqtt_server (mqtt_server, mqtt_port);
    reconnect();
  
}

void loop() {
    now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    digitalWrite(led, LOW);
    startTimer = false;
    if (bootCount)
    {
         mqtt_publish("Micropolis/motion_sensor",payload); 
    }
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_27,1); //1 = High, 0 = Low
    Serial.println("Going to sleep now");
    delay(1000);
    esp_deep_sleep_start();
}
}
