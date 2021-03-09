#include "smallDot.h"

// row 8 / column 8
char *dot_pin;

void dotmatrix_init(char *pin_num) {
  dot_pin = pin_num;
  
  for(char i=0;i<16;i++)
    pinMode(dot_pin[i], OUTPUT);

  for(char i=8;i<16;i++)
    digitalWrite(dot_pin[i], HIGH);  
}

void dotmatrix_show_line(char data, char line) {
  // all row off
  for(char i=8;i<16;i++)
    digitalWrite(dot_pin[i], HIGH);

  char comp_num = 0x80 >> line;
  for(char i=0;i<8;i++)
    digitalWrite(dot_pin[i], data & comp_num);
  
  digitalWrite(dot_pin[8 + line], LOW);
}

void dotmatrix_show_delay(char *dot_picture, int duty) {
  for(char i=0;i<8;i++) {
    dotmatrix_show_line(dot_picture[i], i);
    delay(duty);
  }
}

unsigned long p_millis_dotmatrix;
unsigned char dotmatrix_prev_row;
void dotmatrix_show_pwm(char *dot_picture, int duty, unsigned long c_millis) {
  if(c_millis - p_millis_dotmatrix > duty) {
    p_millis_dotmatrix = c_millis;
    
    // prev row off
    digitalWrite(dot_pin[8 + dotmatrix_prev_row], HIGH);
    
    // move to now row
    dotmatrix_prev_row = (dotmatrix_prev_row + 1) % 8;
    
    // write now row
    char comp_num = 0x80 >> dotmatrix_prev_row;
    
    for(int i=0;i<8;i++) {
      /*digitalWrite(dot_pin[i], 
        dot_picture[dotmatrix_prev_row] & (0x80 >> i)
      );
      */
      digitalWrite(dot_pin[i], dot_picture[i] & comp_num);
    }
    
    // now row on
    digitalWrite(dot_pin[8 + dotmatrix_prev_row], LOW);
  }
}
