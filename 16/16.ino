#include "adc.h"
#include "C:/Users/user/Documents/Arduino/etherShield_raw_data/etherShield/source_text/ether_link/Print.h"

void setup() {
  Serial.begin(9600);
  adc_init2(REF_AVCC, 0x07);

  Serial.println("init");
}

void loop() {
  unsigned short joystick_x = analog_read(AD_0);
  unsigned short joystick_y = analog_read(AD_1);

  Serial.print("x : ");
  Serial.print(joystick_x);
  Serial.print(",y : ");
  Serial.println(joystick_y);
}
