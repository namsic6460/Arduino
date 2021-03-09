#define D0 11
#define D1 10
#define D2 9
#define D3 8
#define D4 7
#define D5 6
#define D6 5
#define D7 4

#define RS 14
#define RW 15
#define E 16

int DList[8] = {D0, D1, D2, D3, D4, D5, D6, D7};
//int DList[8] = {D7, D6, D5, D4, D3, D2, D1, D0};

void instruction(String hex) {
  // transform
  Serial.print("input : ");
  Serial.println(hex);
  int bin[8] = { 0, };

  int number, index;
  for(int i = 0; i < 2; i++) {
    char c = hex.charAt(i);
    
    if(c >= 'A' && c <= 'F')
      number = c - 55;
    else
      number = c - 48;

    for(int j = 0; j < 4; j++) {
      index = (i + 1) * 4 - 1 - j;
      bin[index] = number % 2;
      number /= 2;

      if(number == 0)
        break;
    }
  }

  //instruction
  digitalWrite(RS, LOW);
  //digitalWrite(RW, LOW);

  Serial.print(hex);
  Serial.print(" ");
  for(int i = 0; i < 8; i++) {
    if(bin[i]) {
      digitalWrite(DList[i], HIGH);
      Serial.print("HIGH ");
    }
    else {
      digitalWrite(DList[i], LOW);
      Serial.print("LOW ");
    }
  }
  Serial.println("");

  //enable
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  //digitalWrite(RW, HIGH);
  digitalWrite(RS, HIGH);

  delayMicroseconds(50);
}

void initLCD() {
  digitalWrite(RW, LOW);
  
  Serial.println("A");
  instruction("30");
  Serial.println("B");
  instruction("30");
  Serial.println("C");
  instruction("30");
  Serial.println("D");
  
  instruction("38");
  Serial.println("E");
  instruction("06");
  Serial.println("F");
  instruction("0C");
  Serial.println("G");
  instruction("80");
  Serial.println("H");

  instruction("01");
  delay(10);
}

void setup() {
  Serial.begin(9600);
  
  for(int i = 0; i < 8; i++)
    pinMode(DList[i], OUTPUT);
  for(int i = 0; i < 3; i++)
    pinMode(i + 14, OUTPUT);

  initLCD();
}

void loop() {
  
  //data 0x31
  digitalWrite(RS, HIGH);
  digitalWrite(RW, LOW);

  //0x31
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
  
  //enable
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  digitalWrite(RW, HIGH);
  digitalWrite(RS, HIGH);

  delayMicroseconds(50);
  delay(1000);
  
}
