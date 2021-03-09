void setup() {
  Serial.begin(9600);
  
  TCCR2A = 0x02;
  TCCR2B = 0x02;
  TCNT2 = 0;
  OCR2A = 80;
  TIMSK2 = 0x02;
  
  pinMode(13, OUTPUT);
}

void loop() {

}

int count = 0;
int checkNum = 100;
SIGNAL(TIMER2_COMPA_vect)
{
  count++;

  if(count == checkNum) {
    digitalWrite(13, HIGH);
    checkNum--;

    checkNum = checkNum == 0 ? 100 : checkNum;
  }
  
  if(count == 100) {
    count = 0;
    digitalWrite(13, LOW);
  }
}
