// Print Hello World
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);  // start serial communication
  
// }void loop() {
//   // put your main code here, to run repeatedly:
//   Serial.println("Hello World!");
//   delay(1000);  // wait 1000 ms
// }

// LED Blinking
// void setup() {
//   // initialize digital pin LED_BUILTIN as an output.
//   pinMode(23, OUTPUT);
// }// the loop function runs over and over again forever
// void loop() {
//   digitalWrite(23, HIGH);   // turn the LED on 
//   delay(1000);             // wait for a second
//   digitalWrite(23, LOW);    // turn the LED off 
//   delay(1000);             // wait for a second
// }

#define LED1    23
#define LED2    16
#define BUTTON  32
int count = 0;

void setup() {
  pinMode(BUTTON, INPUT); // set arduino pin to input mode
  pinMode(LED1, OUTPUT);  // set arduino pin to output mode
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
}void loop() {
  if(digitalRead(BUTTON)==LOW) { 
    digitalWrite(LED1, HIGH);
    count++;
    Serial.println(count);
    while(digitalRead(BUTTON)==LOW){
      delay(1000);
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,HIGH);
      delay(1000);
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
    };
  }
  if(digitalRead(BUTTON)==HIGH){
    digitalWrite(LED1,LOW);
  }
}