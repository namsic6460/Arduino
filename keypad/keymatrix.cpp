#include "keymatrix.h"

#define ROW_START 0
#define COL_START 4-

char *keymatrixPin;

void keymatrixInit(char *pinNum) {
  keymatrixPin = pinNum;

  for(int i = 0; i < 4; i++) {
    pinMode(keymatrixPin[ROW_START + i], INPUT);    //ROW 1~4
    pinMode(keymatrixPin[COL_START + i], OUTPUT);   //Col 1~4
  }
}

char keymatrixInputDelay(char pinNum) {
  digitalWrite(keymatrixPin[COL_START + pinNum], HIGH);
  
  char input = digitalRead(keymatrixPin[ROW_START]);
  delay(10);
  
  digitalWrite(keymatrixPin[COL_START + pinNum], LOW);

  return input;
}
