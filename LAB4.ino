#define LDR 35
#define LED 22
int LDR_Value=0;
int static_variable = 3400;
int static_variable2 = 3250;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  LDR_Value = analogRead(LDR);

  Serial.print("Variable_1:");
  Serial.print(LDR_Value);
  Serial.print(",");
  Serial.print("Variable_2:");
  Serial.println(static_variable);
  Serial.print(",");
  Serial.print("Variable_3:");
  Serial.println(static_variable2);
  if(LDR_Value > static_variable){
    digitalWrite(LED,HIGH);
  }
  if(LDR_Value < static_variable2){
    digitalWrite(LED,LOW);
  }
  delay(20);
}