#define RS 14
#define RW 15
#define E 16
#define DB0 4
#define DB4 8

unsigned long fallingTime[40];

int receiveIdx = 0;
int diffTime[33];
int remoconData[32];

char repeatFlag = 0;
char maxFlag = 0;
char dataReceived = 0;
char remData;
char dataHex;
//char number[10][8] = {
//  {0,1,1,0,1,0,0,0},
//  {0,0,1,1,0,0,0,0},
//  {0,0,0,1,1,0,0,0},
//  {0,1,1,1,1,0,1,0},
//  {0,0,0,1,0,0,0,0},
//  {0,0,1,1,1,0,0,0},
//  {0,1,0,1,1,0,1,0},
//  {0,1,0,0,0,0,1,0},
//  {0,1,0,0,1,0,1,0},
//  {0,1,0,1,0,0,1,0}
//};

unsigned char data[10] = {0x68, 0x30, 0x18, 0x7a, 0x10, 0x38, 0x5a, 0x42, 0x4a, 0x52};

void remoconISR() {
  fallingTime[receiveIdx] = micros();

  if(receiveIdx > 0) {
    if(fallingTime[receiveIdx] - fallingTime[receiveIdx - 1] > 13000 &&
        fallingTime[receiveIdx] - fallingTime[receiveIdx - 1] < 14000) {
      receiveIdx = 1;
      repeatFlag = 0;
      dataReceived = 0;
    }

    else if(fallingTime[receiveIdx] - fallingTime[receiveIdx - 1] > 11000 &&
        fallingTime[receiveIdx] - fallingTime[receiveIdx - 1] < 12000) {
      receiveIdx = 0;
      repeatFlag = 1;
      dataReceived = 1;
    }
    
    diffTime[receiveIdx - 1] = fallingTime[receiveIdx] - fallingTime[receiveIdx - 1];
  }

  if(++receiveIdx == 34) {
    receiveIdx = 0;
    maxFlag = 1;
  }
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

void setup() {
  Serial.begin(9600);
  
  attachInterrupt(1, remoconISR, FALLING);

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
 if(maxFlag == 1) {
  maxFlag = 0;

  int term;
  for(char i = 1; i < 33; i++) {
    if(diffTime[i] > 1000 && diffTime[i] < 1500)
      remoconData[i - 1] = 0;
    else if(diffTime[i] > 2000 && diffTime[i] < 2500)
      remoconData[i - 1] = 1;
  }

  dataHex = 0x00;
  for(char i = 16; i < 24; i++) {
    if(remoconData[i] == 1)
      dataHex |= 0x01 << (23 - i);
  }

  for(int i = 0; i < 10; i++) {
    if(dataHex == data[i]) {
      char tempData = i + 0x30;
      Serial.println(tempData);
      lcdSetInst4(0x80);
      lcdSetData4(tempData);
      remData = tempData;
    }
  }
 }

 if(repeatFlag == 1 && dataReceived == 1) {
  repeatFlag = 0;
  dataReceived = 0;
  Serial.println(remData);
 }
}
