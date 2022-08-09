const int smokeSensor = 27;

char* state = "off";

RTC_DATA_ATTR int bootCount = 0;


void setup() {
  Serial.begin(115200);
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(smokeSensor, INPUT_PULLUP);

}

void loop() {
  
  int analogSensor = analogRead(smokeSensor);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  delay(500);

}
