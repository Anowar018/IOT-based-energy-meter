#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "ACS712.h"
char watt[5];
ACS712 sensor(ACS712_30A, A5);
unsigned long last_time =0;
unsigned long current_time =0;
float Wh;
float bill=3;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);    
void setup() {
  Serial.begin(115200);
  lcd.begin(20,4);
  sensor.calibrate();
  lcd.setCursor(0,0);
   lcd.print("IOT Based");
   lcd.setCursor(0,1);
   lcd.print("  Energy Meter  ");
    delay(1000);
    lcd.clear();
  sensor.calibrate();
}

void loop() {
   Wh = EEPROM.read('watt');
  float V = 230;
  float I = sensor.getCurrentAC();
// Serial.println(I);
   float B=Wh*bill;
  float P = V * I;
  last_time = current_time;
  current_time = millis();    
  Wh = Wh+  P *(( current_time -last_time) /3600000.0); 
   dtostrf(Wh, 4, 2, watt);        
Serial.write(watt);
  delay(10000);
  Serial.print("Voltage: ");
  Serial.print(V);
  Serial.println(" Volts");
  Serial.print("Current: ");
   Serial.print(I);
   Serial.println("Amp");
  Serial.print("Power: ");         
Serial.write(watt);
Serial.println("Watt");
EEPROM.write(address, watt); 
lcd.clear();
 lcd.setCursor(0,0);
lcd.print("Energy: ");
lcd.write(watt);
lcd.print(" wh ");
lcd.setCursor(0,1);
   lcd.print("Power: ");
  lcd.print(P);
  lcd.print(" watt ");
  delay(2000);
  lcd.setCursor(0,2);
   lcd.print("Current: ");
   lcd.print(I);
   lcd.print(" Amp ");
   lcd.setCursor(0,3);
   lcd.print("Bill: ");
   lcd.print(B);
   lcd.print(" Tk ");
   
   delay(5000);

}

 
