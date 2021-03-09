#include "uart.h"

void setup() {
  Serial.begin(9600);
  uart_init(9600);
}

char buf[50];
int a = 0;
void loop() {
  printh("hello : %d\n", a++);
  uart_tx_string(buf);
  
  delay(1000);
}
