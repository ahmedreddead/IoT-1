
#define timeSeconds 5
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc.h"
#include "driver/rtc_io.h"

#define motionSensor_pin GPIO_NUM_27



// Set GPIOs for LED and PIR Motion Sensor
const int led = 23;
//const int motionSensor = 27;

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
    pinMode(motionSensor_pin, INPUT_PULLUP);
    // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
    // Set LED to LOW
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    startTimer = true;
    lastTrigger = millis();

    //rtc_gpio_init(pin);
    //rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY); \
    //rtc_gpio_pulldown_en(pin);
    //rtc_gpio_pullup_en(pin);
    //gpio_deep_sleep_hold_en();

    if (!bootCount)
    {
        Serial.println("restarting");
        bootCount++;
    }
    else {
        Serial.println("Motion detected");
    }
    setup_wifi(ssid, password);
    set_mqtt_server(mqtt_server, mqtt_port);
    reconnect();

}

void loop() {
    now = millis();
    // Turn off the LED after the number of seconds defined in the timeSeconds variable
    if (startTimer && (now - lastTrigger > (timeSeconds * 1000))) {
        digitalWrite(led, LOW);
        startTimer = false;
        if (bootCount)
        {
            mqtt_publish("Micropolis/motion_sensor", payload);
        }

        esp_sleep_enable_ext0_wakeup(motionSensor_pin, 1); //1 = High, 0 = Low
        //rtc_gpio_hold_en(pin); // enable hold for the RTC GPIO port
        gpio_hold_en(motionSensor_pin);
        gpio_deep_sleep_hold_en();
        Serial.println("Going to sleep now");
        delay(1000);
        esp_deep_sleep_start();
    }
}
