#define G4 1275

#define TRIG 3
#define ECHO 4
#define BUZZER 5

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
}

int delayTime = 1;
float distance = 0;
unsigned long preMicros = 0;
unsigned long curMicros;

void loop() {
  curMicros = micros();
  
  if(curMicros - preMicros >= 10000) {
    digitalWrite(TRIG, LOW);
    digitalWrite(ECHO, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
  
    distance = ((340.0f * pulseIn(ECHO, HIGH)) / 10000) / 2;
    Serial.println(distance);
    preMicros = curMicros;
  }

  if(distance <= 50) {
    for(int i = 0; i < 100; i++) {
      digitalWrite(BUZZER, HIGH);
      delayMicroseconds(G4);
      digitalWrite(BUZZER, LOW);
      delayMicroseconds(G4);
    }

    if(distance <= 10)
      delayTime = 1;
    else if(distance <= 20)
      delayTime = 100;
    else if(distance <= 30)
      delayTime = 500;
    else
      delayTime = 1000;
    
    delay(delayTime / 2);
  }
}
