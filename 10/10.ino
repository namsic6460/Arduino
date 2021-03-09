#define CLK 4
#define DATA 5
#define LATCH 6

#define ROW0 12

char dotData = 0x23;

void setup() {
  for(int i = 0; i < 3; i++)
    pinMode(4 + i, OUTPUT);

  for(int i = 0; i < 8; i++)
    pinMode(ROW0 + i, OUTPUT);

  for(int i = 0; i < 8; i++)
    digitalWrite(ROW0 + i, LOW);

  setColumn(dotData);
  digitalWrite(ROW0, HIGH);
}

void loop() {
  aetColumn(0x01);
  delay(1000);
  setCoulmn(0x00);
  delay(1000);
}

void setColumn(char dotData) {
  for(int i = 0; i < 8; i++) {
    if(dotData & (0x80 >> i))
      digitalWrite(DATA, LOW);
    else
      digitalWrite(DATA, HIGH);

      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
  }

  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}
