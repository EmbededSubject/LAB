// Exmaple of using the MQTT library for ESP32 
// Library by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt
// Modified by Arnan Sipitakiat


#include <WiFi.h>
#include <MQTT.h>
#include <Adafruit_I2CDevice.h>
#include <LCD_I2C.h>

#define PIN2 18
#define PIN7 19

LCD_I2C lcd(0x27, 16, 2);

#define I2C_ADDRESS 0x68
Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(I2C_ADDRESS);


const char ssid[] = "@JumboPlusIoT";
const char pass[] = "dogdog02";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="group002/motor";
const char mqtt_client_id[]="arduino_group_2"; // must change this string to a unique value
int MQTT_PORT=1883;

String Status = "Status";
int counter=0;
bool on = false;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id)) {  
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe(mqtt_topic);
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  Serial.println();
  if(payload == "forward"){
      Status = payload;
      digitalWrite(PIN2, LOW);
      digitalWrite(PIN7, HIGH);
    }
    if(payload == "backward"){
      Status = payload;
      lcd.print("Backward");
      digitalWrite(PIN2, HIGH);
      digitalWrite(PIN7, LOW);
    }
    if(payload == "off"){
      Status = payload;
      digitalWrite(PIN2, LOW);
      digitalWrite(PIN7, LOW);
    }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN7, OUTPUT);
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN7, HIGH);

  Serial.println("I2C device read and write test");

  lcd.begin();
  // lcd.backlight();
  i2c_dev.begin();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);
  uint8_t buffer[32];
  for (uint8_t i=0; i<8; i++) {
    buffer[i] = 0;
  }
  // Try to read 32 bytes
  i2c_dev.write_then_read(buffer, 1, buffer, 8);
  // Serial.print("Read: ");
  for (uint8_t i=0; i<8; i++) {
    Serial.print("0x"); 
    Serial.print(buffer[i], HEX); 
    Serial.println("");
  }
  // lcd.print((buffer[6]>>0x04)*0x0A);
  lcd.print(buffer[6],HEX);
  lcd.print("/");
  lcd.print(buffer[5], HEX);
  lcd.print("/");
  lcd.print(buffer[4], HEX);
  lcd.print("/");
  if(buffer[2] < 10){
    lcd.print("0");
  }
  lcd.print(buffer[2], HEX);
  lcd.print(":");
  if(buffer[1] < 10){
    lcd.print("0");
  }
  lcd.print(buffer[1], HEX);
  lcd.print(":");
  if(buffer[0] < 10){
    lcd.print("0");
  }
  lcd.print(buffer[0], HEX);
  lcd.setCursor(0, 1);
  client.onMessage(messageReceived);
  lcd.print(Status);
  delay(1000);
  lcd.clear();
}