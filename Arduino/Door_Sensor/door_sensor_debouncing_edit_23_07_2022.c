

#include <WiFi.h>
#include <PubSubClient.h>


#define DOOR_SENSOR_PIN 4
#define Hall_Sensor 35

RTC_DATA_ATTR int bootCount = 0;
float doorState,MagniticField;

const char* ssid = "MICROPOLIS";
const char* password = "Micropolis@212";
const char* mqtt_server = "10.20.0.230";

char* msgTopic = "Micropolis/door_sensor/";


const char* sensor_id = "do55411"


String open_message = String("{id:" + String(id) + ",status:opened}");
String closed_message = String("{id:" + String(id) + ",status:closed}");

const char* str_open = on_message.c_str();
const char* str_close = off_message.c_str();



WiFiClient espClient;
PubSubClient client(espClient);

char* last_state = "Non";

int normal_counter = 0;
int high_counter = 0;
int low_counter = 0;

 
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(DOOR_SENSOR_PIN , INPUT_PULLUP);

}

void setup_wifi() {
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
    if (client.connect("door_sensor")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  else {

  normal_counter++ ;
  doorState = digitalRead(DOOR_SENSOR_PIN);
  MagniticField = hallRead();
  Serial.println(doorState);
  if (doorState == HIGH) {
    Serial.println("the door is open ");
    high_counter++ ;
    
    if (last_state != "open")
{
    client.publish(msgTopic, "id = 1, status = opened");
    client.publish(msgTopic, str_open);
    last_state = "open"; 
}

    
    } else {
    Serial.println("the door is close ");
    low_counter++ ;
    if (last_state != "close")
{
    client.publish(msgTopic, "id = 1 , status = closed"); 
    client.publish(msgTopic, str_close);
    last_state = "close"; 

    
}
    
    }

  if (normal_counter == 30)
  {
    if (high_counter == normal_counter && low_counter == 0 ) 
    {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4,0); //1 = High, 0 = Low
    Serial.println("Going to sleep now");
    delay(1000);
    esp_deep_sleep_start();
      }

    else if ( low_counter == normal_counter && high_counter == 0 )
    {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4,1); //1 = High, 0 = Low
    Serial.println("Going to sleep now");
    delay(1000);
    esp_deep_sleep_start();
      
      }

    else 

    {
      normal_counter = 0;
      high_counter = 0;
      low_counter = 0;
      
      }
    
    }
  //client.loop();


}
delay(1000);
}
