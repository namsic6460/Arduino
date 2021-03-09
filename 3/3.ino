#define INPUT1 2
#define INPUT2 3
#define INPUT3 4
#define INPUT4 5
#define OUTPUT1 8
#define OUTPUT2 9
#define OUTPUT3 10
#define OUTPUT4 11

char INPUT_LIST[4] = {INPUT1, INPUT2, INPUT3, INPUT4};
char OUTPUT_LIST[4] = {OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4};
char values[4][4];
char characters[4][4] = {'1', '2', '3', 'A',
                         '4', '5', '6', 'B',
                         '7', '8', '9', 'C',
                         '*', '0', '#', 'D'};

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 4; i++) {
    pinMode(OUTPUT_LIST[i], OUTPUT);
    pinMode(INPUT_LIST[i], INPUT);

    for(int j = 0; j < 4; j++)
      values[i][j] = 0;
  }
}

void loop() {
  for(char i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i != j)
        digitalWrite(OUTPUT_LIST[j], LOW);
      else
        digitalWrite(OUTPUT_LIST[j], HIGH);
    }

    for(char j = 0; j < 4; j++) {
      char readNum = digitalRead(INPUT_LIST[j]);

      if(values[i][j] != readNum) {
        values[i][j] = readNum;

        if(readNum)
          printLocation(1, j, i);
        else
          printLocation(0, j, i);
      }
    }
  }

  delay(5);
}

void printLocation(int data, int i, int j) {
  if(data) {
    Serial.print("DOWN [");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(j);
  }

  else {
    Serial.print("UP [");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(j);
  }

  Serial.print(" - ");
  Serial.print(characters[i][j]);
  Serial.println("]");
}
