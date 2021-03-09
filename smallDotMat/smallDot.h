#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include "Arduino.h"

void dotmatrix_init(char *pin_num);

void dotmatrix_show_line(char data, char line);
void dotmatrix_show_delay(char *dot_picture, int duty);
void dotmatrix_show_pwm(char *dot_picture, int duty, unsigned long c_millis);

#endif
