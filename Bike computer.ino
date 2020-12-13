#include <LiquidCrystal.h>
#include <EEPROM.h>

unsigned long lastTime = 0;
float speed = 0;
float wheelLength = 2.04;
float totalKm = EEPROM.get(0, totalKm);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, sens, FALLING);
  
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Hello, Dima");
  delay(5000);
  lcd.clear();
}

void sens(){
  if(millis() - lastTime > 99 ){
    speed = wheelLength / ((float)(millis() - lastTime) / 1000) * 3.6;
    lastTime = millis();
    totalKm = totalKm + wheelLength; 
  }
  
}

void loop() {
  delay(500);
  
  EEPROM.put(0, totalKm);
  
  lcd.setCursor(5, 0);
  lcd.print(speed, 0);
  lcd.setCursor(8, 0);
  lcd.print("km/h");
  lcd.setCursor(0, 1);
  lcd.print("t:");
  lcd.setCursor(2, 1);
  lcd.print(totalKm / 1000, 3);
  lcd.print("    ");
  
  if((millis() - lastTime) > 2000){
    speed = 0;
    lcd.setCursor(6, 0);
    lcd.print(" ");
  }
}
