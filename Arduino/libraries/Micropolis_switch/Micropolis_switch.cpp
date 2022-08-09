
#include "Micropolis_switch.h"
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);



String st;
char* id = "default000";


// Date constructor
Micropolis_switch object(26, 27, id);


Micropolis_switch::Micropolis_switch(int vcc, int gnd, char* id_input)
{
    Set_volt(vcc,gnd);
    id = id_input;

}
// Date member function
void Micropolis_switch::Set_volt(int vcc0, int gnd0)
{
    vcc = vcc0;
    gnd = gnd0;
    status = "off";
    pinMode(vcc, OUTPUT);
    pinMode(gnd, OUTPUT);
    digitalWrite(this->vcc, LOW);
    digitalWrite(this->gnd, LOW);


}

void Micropolis_switch::switch_on()
{
 digitalWrite(this->vcc, HIGH);
 digitalWrite(this->gnd, LOW);
// status = "on";
 //st = "{id:" + String (id) + ",status:" + String (status) + "}";
// const char* str = st.c_str();
 //client.publish("Micropolis/switch",str);
 
}


void Micropolis_switch::switch_off()
{
 digitalWrite(this->vcc, LOW);
 digitalWrite(this->gnd, LOW);
 //status = "off";
// st = "{id:" + String(id) + ",status:" + String(status) + "}";
// const char* str = st.c_str();
// client.publish("Micropolis/switch", str);
}



void Micropolis_switch::set_mqtt_server(char *mqtt_server, int port)
{
   client.setServer(mqtt_server, port);
   object = *this;
   client.setCallback(callback);
   status = "off";
   st = "{id:" + String(id) + ",status:" + String(status) + "}";
   const char* str = st.c_str();
   client.publish("Micropolis/switch", str);
}

void Micropolis_switch::mqtt_publish (char *topic, char *message)
{
   client.publish(topic, message);
   
}

void Micropolis_switch::setup_wifi(char *ssid ,char *password ) {
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
    if (client.connect("Micropolis_switch")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("Micropolis/switch");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}





 void callback(char* topic, byte* message, unsigned int length ) {

  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  String on_message = String("{id:" + String(id) + ",status:on}");
  String off_message = String("{id:" + String(id) + ",status:off}");

  const char* str_on = on_message.c_str();
  const char* str_off = off_message.c_str();

  if (String(topic) == "Micropolis/switch") {
    if(String(messageTemp) == on_message) {
      object.switch_on();
    }
    if(String(messageTemp) == off_message) {
      object.switch_off();
    }

  }
}

void loop_client ()
{  if (!client.connected()) {
    reconnect();
  }
    client.loop();
}