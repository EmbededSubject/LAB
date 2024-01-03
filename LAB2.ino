//Written By Nikodem Bartnik - nikodembartnik.pl
#define STEPPER_PIN_1 19
#define STEPPER_PIN_2 18
#define STEPPER_PIN_3 5
#define STEPPER_PIN_4 17
int step_number = 0;
void setup() {
pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);

}

void loop() {

  OneStep(true);
  delay(2);
  // delay(5000);
  // OneStep(true);
  // delay(2);
  // delay(5000);
}


void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
}
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
}
  }
step_number++;
  if(step_number > 6){
    step_number = 0;
  }
}
// #define PIN1
// #define PIN2 23
// #define PIN7 22
// #define BUTTON 25
// #define LED 17
// bool toggle = false;

// void setup() {
//   pinMode(PIN2, OUTPUT);
//   pinMode(PIN7, OUTPUT);
//   pinMode(BUTTON, INPUT);
//   pinMode(LED, OUTPUT);

//   digitalWrite(PIN2, HIGH);
//   digitalWrite(PIN7, HIGH);
// }

// void loop() {
//   if (digitalRead(BUTTON) == LOW && toggle == false) {
//     digitalWrite(LED, HIGH);
//     toggle = true;
//     digitalWrite(PIN2, HIGH);
//     digitalWrite(PIN7, LOW);
//   }
//   if (digitalRead(BUTTON) == LOW && toggle == true) {
//     digitalWrite(LED, LOW);
//     toggle = false;
//     digitalWrite(PIN2, LOW);
//     digitalWrite(PIN7, HIGH);
//   }
// }