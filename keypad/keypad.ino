//#include "keymatrix.h"
//
////Row 1~4 - Col 1~4
//char pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
//
//void setup() {
//  Serial.begin(9600);
//  
//  keymatrixInit(pins);
//}
//
//void loop() {
//  String str = "";
//  
//  for(char i = 0; i < 4; i++) {
//    char input = keymatrixInputDelay(i);
//    str += (int) input;
//    str += ", ";
//  }
//
//  Serial.println(str);
//}


char ROW[]  = {2, 3, 4, 5};
char COLUMN[] = {6, 7, 8, 9};

void setup() {
  Serial.begin(9600);
  for(int i=0;i<4;i++) {
    pinMode(ROW[i], OUTPUT);
    pinMode(COLUMN[i], INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:


  String push = "";
  for(char i=0;i<4;i++) {
    digitalWrite(ROW[i], HIGH);

    for(char j=0;j<4;j++) {
      bool isPushed = digitalRead(COLUMN[j]);
      if(isPushed) {
        push = push + "1 ";
      }
      else{
        push = push + "0 ";
      }
    }
    push = push + " ";

    digitalWrite(ROW[i], LOW);
    delay(10);
  }
  Serial.println(push);

  delay(100);
  
}
