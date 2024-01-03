// Exmaple of using the MQTT library for ESP32 
// Library by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt
// Modified by Arnan Sipitakiat


#include <WiFi.h>
#include <MQTT.h>

#define PIN2 23
#define PIN7 22

const char ssid[] = "@JumboPlusIoT";
const char pass[] = "dogdog02";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="group002/motor";
const char mqtt_client_id[]="arduino_group_2"; // must change this string to a unique value
int MQTT_PORT=1883;

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
  if(payload == "forward"){
      digitalWrite(PIN2, LOW);
      digitalWrite(PIN7, HIGH);
    }
    if(payload == "backward"){
      digitalWrite(PIN2, HIGH);
      digitalWrite(PIN7, LOW);
    }
    if(payload == "off"){
      digitalWrite(PIN2, LOW);
      digitalWrite(PIN7, LOW);
    }
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN7, OUTPUT);
  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN7, HIGH);
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  // not that we don't use delay() because we need to keep calling the client.loop()
  // to keep the connection alive
  // if (millis() - lastMillis > 2000) {
  //   lastMillis = millis();
    client.onMessage(messageReceived);
  // }
}