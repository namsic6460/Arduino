#define INPUT1 2
#define INPUT2 3
#define INPUT3 4
#define INPUT4 5
#define OUTPUT1 8
#define OUTPUT2 9

char INPUT_LIST[4] = {INPUT1, INPUT2, INPUT3, INPUT4};
char OUTPUT_LIST[2] = {OUTPUT1, OUTPUT2};
char values[8];

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 4; i++) {
    pinMode(INPUT_LIST[i], INPUT);
    
    for(int j = 0; j < 2; j++ ) {
      char index = i + (j * 2);
      
      values[index] = 0;
      pinMode(OUTPUT_LIST[index], OUTPUT);
    }
  }
}

void loop() {
  for(char i = 0; i < 2; i++) {
    digitalWrite(OUTPUT_LIST[1 - i], LOW);
    digitalWrite(OUTPUT_LIST[i], HIGH);

    for(char j = 0; j < 4; j++) {
      char readNum = digitalRead(INPUT_LIST[j]);
      char index = j + (i * 4);

      if(values[index] != readNum) {
        values[index] = readNum;

        if(values[index]) {
          Serial.print("DOWN ");
          Serial.println(index + 1);
        }

        else {
          Serial.print("UP ");
          Serial.println(index + 1);
        }
      }
    }
  }

  delay(5);
}
