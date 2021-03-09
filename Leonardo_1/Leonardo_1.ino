#include "Keyboard.h"

void setup() {
  Keyboard.begin();
}

void loop() {
  Keyboard.write(0x32);
  delay(1000);
}
