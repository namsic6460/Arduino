#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int num = 0;
const byte ROWS = 4;    // 행(rows) 개수
const byte COLS = 4;    // 열(columns) 개수

char key;
boolean flag;
char str[30] = "";

int arr[4] = { 10, 11, 12, 13 };
char keys[ROWS][COLS] =
{
  { 65, 69, 73, 68 },
  { 66, 70, 71, 72 },
  { 67, 74, 75, 76 },
  { 68, 78, 79, 80 }
};

byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  lcd.init();
  lcd.backlight();
  for(int i = 0; i < 4; i++)
    pinMode(arr[i], OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  key = keypad.getKey();
  flag = true;

  if(key)
    Serial.println(key);

  switch(key)
  {
    case 65:
      strcpy("OSULLOC_Tea Museaum");
      num = 1;
      break;
    case 66:
      strcpy("Camellia Hill");
      num = 1;
      break;
    case 67:
      strcpy("Cheonjeyeon_falls");
      num = 1;
      break;
    case 68:
      strcpy("Yongmeoli shore");
      num = 1;
      break;
    case 69:
      strcpy("Mt.Hanlla");
      num = 2;
      break;
    case 70:
      strcpy("Chonjiyeon_falls");
      num = 2;
      break;
    case 71:
      strcpy("soesokkak");
      num = 2;
      break;
    case 72:
      strcpy("JeJu Korean_Folk Village");
      num = 2;
      break;
    case 73:
      strcpy("Handeok Beach");
      num = 3;
      break;
    default:
      flag = false;
      break;
  }

  if(flag) {
    lcd.clear();
    digitalWrite(arr[0], HIGH);
    printLCD();
  }

  if(num)
    Serial.println(num);
  
  switch(num)
  {
    case 1:
      digitalWrite(arr[0], HIGH);
      for(int i = 1; i < 4; i++)
        digitalWrite(arr[i], LOW);
      break;
    default:
      for(int i = 0; i < 4; i++)
        digitalWrite(arr[i], LOW);
      break;
  }
}

void printLCD(){
  int cursor = 0;
  
  for(int i = 0; str[i] != 0; i++){
    if(str[i] == '_') {
      lcd.setCursor(0, ++cursor);
      continue;
    }
    lcd.print(str[i]);
  }
}

void strcpy(char[] string){
  for(int i = 0; i < string.length(); i++){
    str[i] = string[i];
  }
  str[string.length()] = 0;
}
