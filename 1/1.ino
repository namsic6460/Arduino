#define INPUT_ROW1 2
#define INPUT_ROW2 3
#define OUTPUT_COLUMN_1 8
#define OUTPUT_COLUMN_2 9
#define OUTPUT_COLUMN_3 10
#define OUTPUT_COLUMN_4 11

char OUTPUT_LIST[4] = {OUTPUT_COLUMN_1, OUTPUT_COLUMN_2, OUTPUT_COLUMN_3, OUTPUT_COLUMN_4};
char values[8];

void setup() {
  Serial.begin(9600);

  pinMode(INPUT_ROW1, INPUT);
  pinMode(INPUT_ROW2, INPUT);
  
  for(int i = 0; i < 4; i++) {
    values[i] = 0;
    pinMode(OUTPUT_LIST[i], OUTPUT);
  }
}

void loop() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i != j)
        digitalWrite(OUTPUT_LIST[j], LOW);
      else
        digitalWrite(OUTPUT_LIST[j], HIGH);
    }

    int readNum[2] = {digitalRead(INPUT_ROW1), digitalRead(INPUT_ROW2)};

    for(int j = 0; j < 2; j++) {
      int index = i + (j * 4);
      
      if(values[index] != readNum[j]) {
        values[index] = readNum[j];

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
    
    delay(5);
  }
}
