#ifndef Micropolis_Siren_H
#define Micropolis_Siren_H

#include <PubSubClient.h>
#include <WiFi.h>




class Micropolis_Siren
{
private:
    int vcc;
    int gnd;
    char* status;



public:
    Micropolis_Siren(int vcc, int gnd, char* id_input);

    void Set_volt(int vcc, int gnd);
    int getVcc() { return vcc; }
    int getGnd() { return gnd; }

    void siren_on();
    void siren_off();


    void set_mqtt_server(char *mqtt_server, int port);
    void mqtt_publish (char *topic, char *message);
    void setup_wifi(char *ssid ,char *password );

    

};
void reconnect();
 void callback(char* topic, byte* message, unsigned int length  );
 void loop_client ();


#endif
