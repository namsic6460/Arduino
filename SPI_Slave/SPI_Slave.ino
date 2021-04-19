#include <SPI.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
//  SPI.begin();
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);
  
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  Serial.begin(9600);
  lcd.begin();

  Serial.println("Started!");
}

unsigned long prevMilli = 0;
unsigned long currMilli;
String text = "";
boolean changed = false;

ISR(SPI_STC_vect) {
  currMilli = millis();
  if(currMilli - prevMilli >= 1000) {
    text = "";
    changed = true;
  }

  prevMilli = currMilli;
  char confirm = (char) SPDR;

  if(confirm != 10) {
    text += confirm;
  }
  
  Serial.print(confirm);
}

void loop() {
  if(changed) {
    lcd.clear();
  }
  
  lcd.setCursor(0, 0);
  lcd.print(text.substring(0, 16));
  lcd.setCursor(0, 1);
  lcd.print(text.substring(16, 32));
  
  delay(1000);
}
