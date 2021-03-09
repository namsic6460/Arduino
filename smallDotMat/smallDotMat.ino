#include "smallDot.h"

char pins[] = {12, 13, 14, 15, 16, 17, 18, 19, 4, 5, 6, 7, 8, 9, 10, 11};

void setup() {
  Serial.begin(9600);
  
  dotmatrix_init(pins);
}

void loop() {
  for(int i = 0; i < 8; i++) {
    dotmatrix_show_line(2, i);
    delay(500);
  }
}
