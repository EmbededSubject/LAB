#include <Adafruit_PCF8574.h>
/* Example for 1 output LED that is connected from power to the GPIO expander pin #7
 * Note the LEDs must be connected with the CATHODES to the expander, to SINK current!
 * The PCF8574 cannot SOURCE current!
 */

// #define PCF8574_Address 0x20

// Adafruit_PCF8574 pcf;
// void setup() {
//   Serial.begin(9600);
//   Serial.println("Adafruit PCF8574 LED blink test");
//   if (!pcf.begin(PCF8574_Address, &Wire)) {
//     Serial.println("Couldn't find PCF8574");
//   }
//   // pcf.pinMode(7, OUTPUT);
// }
// void loop() {
//   if(pcf.digitalRead(0) == LOW){
//     pcf.digitalWrite(7, HIGH);  // turn LED off by turning off sinking transistor
//   }else{
//     pcf.digitalWrite(7, LOW);  // turn LED on by sinking current to ground
//   }
// }

// #include <Adafruit_I2CDevice.h>

// #define PCF8574_Address 0x20

// Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(PCF8574_Address);
// uint8_t buffer[32];

// void setup() {

//   Serial.begin(9600);
//   Serial.println("I2C address detection test");
//   if (!i2c_dev.begin()) {
//     Serial.print("Did not find device at 0x");
//     Serial.println(i2c_dev.address(), HEX);
//     while (1);
//   }
//   Serial.print("Device found on address 0x");
//   Serial.println(i2c_dev.address(), HEX);

//   // Config PCF8574
//   buffer[0]=0;               // config all pins to output
//   i2c_dev.write(buffer,1);   // send the config to PCF8574

// }
// void loop() {
//   // buffer[0]=0b10000000;   // set bit 7 to high
//   // i2c_dev.write(buffer,1);  // turn off LED
//   // delay(1000);

//   // buffer[0]=0b00000000;   // set bit 7 to low
//   // i2c_dev.write(buffer,1);  // turn on LED
//   // delay(1000);
//   i2c_dev.read(buffer,1);
//   Serial.println(buffer[0]);
//   if(buffer[0]&0b0000001){
//     buffer[0] = 0b00000000;   // set bit 7 to low
//     i2c_dev.write(buffer,1);
//   }else{
//     buffer[0]= 0b10000000;   // set bit 7 to high
//     i2c_dev.write(buffer,1);
//   }
// }


// #include <RTClib.h>

// RTC_DS1307 rtc;

// char daysOfWeek[7][12] = {
//   "Sunday",
//   "Monday",
//   "Tuesday",
//   "Wednesday",
//   "Thursday",
//   "Friday",
//   "Saturday"
// };

// void setup () {
//   Serial.begin(9600);
//   if (! rtc.begin()) {
//     Serial.println("RTC module is NOT found");
//     Serial.flush();
//     while (1);
//   }
//   // automatically sets the RTC to the date & time on PC this sketch was compiled
//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   // manually sets the RTC with an explicit date & time, for example to set
//   // January 21, 2021 at 3am you would call:
//   // rtc.adjust(DateTime(2021, 1, 21, 3, 0, 0));
// }

// void loop () {
//   DateTime now = rtc.now();
//   Serial.print("ESP32 RTC Date Time: ");
//   Serial.print(now.year(), DEC);
//   Serial.print('/');
//   Serial.print(now.month(), DEC);
//   Serial.print('/');
//   Serial.print(now.day(), DEC);
//   Serial.print(" (");
//   Serial.print(daysOfWeek[now.dayOfTheWeek()]);
//   Serial.print(") ");
//   Serial.print(now.hour(), DEC);
//   Serial.print(':');
//   Serial.print(now.minute(), DEC);
//   Serial.print(':');
//   Serial.println(now.second(), DEC);

//   delay(1000); // delay 1 seconds
// }

// #include <LCD_I2C.h>

// LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

// void setup()
// {
//     lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
//                  // this stop the library(LCD_I2C) from calling Wire.begin()
//     lcd.backlight();
// }

// void loop()
// {
//     lcd.print("     Hello"); // You can make spaces using well... spaces
//     lcd.setCursor(5, 1); // Or setting the cursor in the desired position.
//     lcd.print("World!");
//     // delay(500);

//     // Flashing the backlight
//     // for (int i = 0; i < 5; ++i)
//     // {
//     //     lcd.backlight();
//     //     delay(50);
//     //     lcd.noBacklight();
//     //     delay(50);
//     // }

//     // lcd.backlight();
//     // lcd.clear();
//     // delay(500);
// }

#include <RTClib.h>
// #include <LCD_I2C.h>


// RTC_DS1307 rtc;
// LCD_I2C lcd(0x27, 16, 2);


// char daysOfWeek[7][12] = {
//   "Sunday",
//   "Monday",
//   "Tuesday",
//   "Wednesday",
//   "Thursday",
//   "Friday",
//   "Saturday"
// };

// void setup () {
//   Serial.begin(9600);
//   if (! rtc.begin()) {
//     Serial.println("RTC module is NOT found");
//     Serial.flush();
//     while (1);
//   }
//   // automatically sets the RTC to the date & time on PC this sketch was compiled
//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   // manually sets the RTC with an explicit date & time, for example to set
//   // January 21, 2021 at 3am you would call:
//   // rtc.adjust(DateTime(2021, 1, 21, 3, 0, 0));
//   lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
// //                  // this stop the library(LCD_I2C) from calling Wire.begin()
//   lcd.backlight();
// }

// void loop () {
//   DateTime now = rtc.now();
//   lcd.clear();
//   lcd.print(now.year(), DEC);
//   lcd.print('/');
//   lcd.print(now.month(), DEC);
//   lcd.print('/');
//   lcd.print(now.day(), DEC);
//   lcd.setCursor(0, 1);
//   lcd.print(now.hour(), DEC);
//   lcd.print(':');
//   lcd.print(now.minute(), DEC);
//   lcd.print(':');
//   lcd.print(now.second(), DEC);

//   delay(1000); // delay 1 seconds
// }

#include <Adafruit_I2CDevice.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); 

#define I2C_ADDRESS 0x68
Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(I2C_ADDRESS);


void setup() {
  // while (!Serial) { delay(10); }
  Serial.begin(115200);
  Serial.println("I2C device read and write test");

  lcd.begin();
  lcd.backlight();
  i2c_dev.begin();

}

void loop() {
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
  Serial.println();

  // read a register by writing first, then reading
  // buffer[0] = 0x0C;  // we'll reuse the same buffer
  // i2c_dev.write_then_read(buffer, 1, buffer, 2, false);
  // Serial.print("Write then Read: ");
  // for (uint8_t i=0; i<2; i++) {
  //   Serial.print("0x"); Serial.print(buffer[i], BIN); Serial.print(", ");
  // }

  lcd.print((buffer[6]>>0x04)*0x0A);
  lcd.print(buffer[6],HEX);
  lcd.print("/");
  lcd.print(buffer[5], HEX);
  lcd.print("/");
  lcd.print(buffer[4], HEX);
  lcd.setCursor(0, 1);
  lcd.print(buffer[2], HEX);
  lcd.print(":");
  lcd.print(buffer[1], HEX);
  lcd.print(":");
  lcd.print(buffer[0], HEX);

  delay(1000);
  lcd.clear();
}