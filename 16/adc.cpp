#include "adc.h"

void adc_init1(char ref) {
  if(ref == REF_AREF) {
    ADMUX = 0x00;
  }

  else {
    ADMUX = 0x01;
  }

  ADCSRA = 0x87;
}

void adc_init2(char ref, char pre_scale) {
  if(ref == REF_AREF)
    ADMUX = 0x00;
  else
    ADMUX = 0x40;

  ADCSRA = 0x87 | pre_scale;
}

unsigned short analog_read(char channel) {
  ADMUX &= ~0x0f;
  ADMUX |= channel;

  ADCSRA |= 0x40;

  while(!(ADCSRA & 0x10));
  return ADC;
}
