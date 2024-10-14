//------------------------------------(1)
//------------------------------------(Blynk Config)
#define BLYNK_TEMPLATE_ID "TMPL63kGHlqcy"
#define BLYNK_TEMPLATE_NAME "SmartCar Phurit San"
#define BLYNK_AUTH_TOKEN "nraqVAnErfvrP1YcZjrk4B1AeMfb76rl"

//------------------------------------(2)
//------------------------------------(lib)
#include <WiFi.h>              //esp32 for connect WIFI
#include <BlynkSimpleEsp32.h>  //esp32 for connecet Blynk

//#define ssid "TSIS_student"  //WIFIUSERNAME
//#define pass "wifi@student"            //PASSWORD

//------------------------------------(3)
#define ssid "PHURITTHARIPHA_2.4G"  //WIFIUSERNAME
#define pass "P22052549"            //PASSWORD

//KruPor's WiFi
//#define ssid "Por-AIS4GHomeWiFi"  //WIFIUSERNAME
//#define pass "por150444"          //PASSWORD

//------------------------------------(Blynk_Control)
int X = 128;
int Y = 128;
String Status = "Stop";

WidgetLED led_Forward(V11);
WidgetLED led_Backward(V12);
WidgetLED led_Left(V13);
WidgetLED led_Right(V14);
WidgetLED led_Stop(V15);

BLYNK_WRITE(V4) {
  X = param.asInt();
}
BLYNK_WRITE(V5) {
  Y = param.asInt();
}

//------------------------------------(setup)
void setup() {
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
}

//------------------------------------(loop)
void loop() {
  Blynk.run();

  if (Y >= 250) {
    forward();
  } else if (Y <= 10) {
    backward();
  } else if (X >= 250) {
    right();
  } else if (X <= 10) {
    left();
  } else if (X == 128 && Y == 128) {
    stop();
  }

  //monitor
  Serial.println(" X: " + String(X) + "," + " Y: " + String(Y) + " Status: " + Status);

  //Blynk Display
  Blynk.virtualWrite(V7, Status);

  delay(100);
}


//------------------------------------(New Func: Control)
void forward() {
  //Status
  Status = "Forward";
  //Blynk LED
  led_Forward.on();
  led_Backward.off();
  led_Left.off();
  led_Right.off();
  led_Stop.off();
  //OUTPUT
  digitalWrite(18, 1);
  digitalWrite(19, 0);
  digitalWrite(26, 1);
  digitalWrite(27, 0);
}
void backward() {
  //Status
  Status = "Backward";
  //Blynk LED
  led_Forward.off();
  led_Backward.on();
  led_Left.off();
  led_Right.off();
  led_Stop.off();
  //OUTPUT
  digitalWrite(18, 0);
  digitalWrite(19, 1);
  digitalWrite(26, 0);
  digitalWrite(27, 1);
}
void left() {
  //Status
  Status = "Left";
  //Blynk LED
  led_Forward.off();
  led_Backward.off();
  led_Left.on();
  led_Right.off();
  led_Stop.off();
  //OUTPUT
  digitalWrite(18, 1);
  digitalWrite(19, 0);
  digitalWrite(26, 0);
  digitalWrite(27, 1);
}
void right() {
  //Status
  Status = "Right";
  //Blynk LED
  led_Forward.off();
  led_Backward.off();
  led_Left.off();
  led_Right.on();
  led_Stop.off();
  //OUTPUT
  digitalWrite(18, 0);
  digitalWrite(19, 1);
  digitalWrite(26, 1);
  digitalWrite(27, 0);
}
void stop() {
  //Status
  Status = "Stop";
  //Blynk LED
  led_Forward.off();
  led_Backward.off();
  led_Left.off();
  led_Right.off();
  led_Stop.on();
  //OUTPUT
  digitalWrite(18, 0);
  digitalWrite(19, 0);
  digitalWrite(26, 0);
  digitalWrite(27, 0);
}
