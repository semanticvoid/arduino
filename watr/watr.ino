// #################
//   project watr 
// #################

#include <EEPROM.h>
#include <LiquidCrystal.h>

#define PIN 10
#define VOLINCR 1
#define FLASHINTERVAL 100

union {
  int i;
  float f;
} vol;

// lcd
LiquidCrystal lcd(12,13,0,1,2,3,4,5,6,7,8);

void setup() {
  lcd.begin(16,2);
  
  // display title
  lcd.setCursor(2,0);
  lcd.print("Project Watr");
  
  //Serial.begin(9600);
  pinMode(PIN, INPUT);
  digitalWrite(PIN, LOW);
  fetchVol();
  //Serial.print("reading saved vol ... ");
  //Serial.print(vol.f);
}

void loop() {
  int state = digitalRead(PIN);
  if(state == 1) {
    incr();
    //storeVol();
    lcd.setCursor(4,1);
    lcd.print(vol.f);
    lcd.print(" mL");
  }
  // flash
    if(((int)vol.f) > 0 && ((int)vol.f) % FLASHINTERVAL == 0) {
      for(int i=0; i<2; i++) {
        lcd.noDisplay();
        digitalWrite(PIN, HIGH);
        delay(200);
        lcd.display();
        digitalWrite(PIN, LOW);
        delay(200);
      }
      delay(200);
    } else {
      delay(1000);
    }
}

// function to read vol from EEPROM
float fetchVol() {
  //byte high = EEPROM.read(0);
  //byte low = EEPROM.read(1);
  //vol.i = (high << 8) + low;
  return vol.f;
}

// function to store vol to EEPROM
void storeVol() {
  EEPROM.write(0, highByte(vol.i));
  EEPROM.write(1, lowByte(vol.i));
}

// increment vol
void incr() {
  vol.f = fetchVol() + VOLINCR;
}
