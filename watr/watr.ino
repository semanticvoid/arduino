// #################
//   project watr 
// #################

#include <EEPROM.h>

#define PIN 8
#define VOLINCR 0.1

union {
  int i;
  float f;
} vol;

void setup() {
  Serial.begin(9600);
  pinMode(PIN, INPUT);
  digitalWrite(PIN, LOW);
  fetchVol();
  Serial.print("reading saved vol ... ");
  Serial.print(vol.f);
}

void loop() {
  int state = digitalRead(PIN);
  if(state == 1) {
    incr();
    //storeVol();
    Serial.println(vol.f);
  }
  delay(1000);
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

