#define RS 14
#define RW 15
#define E 16
#define DB0 4
#define DB4 8

void setup() {
  Serial.begin(9600);

  for(char i = 0; i < 4; i++) {
    pinMode(8 + i, OUTPUT);
    if(i < 3)
      pinMode(14 + i, OUTPUT);
  }

  digitalWrite(RS, HIGH);
  digitalWrite(RW, LOW);

  lcdInit();
}

void loop() {
  lcdSetData4(0x31);
  delay(1000);
}

void lcdInit() {
  lcdSetInst8(0x30);
  lcdSetInst8(0x30);
  lcdSetInst8(0x30);
  lcdSetInst8(0x28);

  lcdSetInst4(0x28);
  lcdSetInst4(0x06);
  lcdSetInst4(0x0c);
  lcdSetInst4(0x80);
  lcdSetInst4(0x01);

  delay(10);
}

void lcdSetInst8(char inst) {
  digitalWrite(RS, LOW);

  for(int i = 0; i < 8; i++) {
    if(inst & (0x01 << i))
      digitalWrite(DB0 + i, HIGH);
    else
      digitalWrite(DB0 + i, LOW); 
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(RS, HIGH);

  delayMicroseconds(50);
}

void lcdSetInst4(char inst) {
  lcdSetInst4Temp((inst >> 4) & 0x0f);
  lcdSetInst4Temp(inst & 0x0f);
}

void lcdSetInst4Temp(char inst) {
  digitalWrite(RS, LOW);

  for(int i = 0; i < 4; i++) {
    if(inst & (0x01 << i))
      digitalWrite(DB4 + i, HIGH);
    else
      digitalWrite(DB4 + i, LOW); 
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(RS, HIGH);
  
  delayMicroseconds(50);
}

void lcdSetData4(char data) {
  lcdSetData4Temp((data >> 4) & 0x0f);
  lcdSetData4Temp(data & 0x0f);
}

void lcdSetData4Temp(char data) {
  for(int i = 0; i < 4; i++) {
    if(data & (0x01 << i))
      digitalWrite(DB4 + i, HIGH);
    else
      digitalWrite(DB4 + i, LOW); 
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
  
  delayMicroseconds(50);
}
