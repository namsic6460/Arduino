#define ROW_0 12
#define COL_0 4

unsigned char parking[7][8] = {
  {0x00, 0x38, 0x44, 0x4C, 0x54, 0x64, 0x44, 0x38},
  {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38},
  {0x00, 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x08},
  {0x00, 0x7C, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38},
  {0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38}
};

int count = 0;
int dot_num = 0;
int shift_count = 0;

void setup()
{
  for(int i = 0; i < 16; i++)
  {
    pinMode(COL_0+i, OUTPUT);
  }
}

void loop()
{
  for(int j = 0; j < 8; j ++)
  {
    // 1. all row off
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(ROW_0+i, LOW);
    }

    // 2. 첫번째 줄 값
    for(int i = 0; i < 8; i++)
    {
      if(parking[0][j] & (0x80 >> i))
      {
        digitalWrite(COL_0+i, LOW);
      }
      else
      {
        digitalWrite(COL_0+i, HIGH);
      }
    }

    // 3. 첫 번째 줄 power on
    digitalWrite(ROW_0 + j, HIGH);

    delay(1);
  }

  count++;
  if(count == 30)
  {
    count = 0;

    for(int i = 0; i < 8; i++)
    {
      for(int k = 0; k < 5; k++) 
      {
        parking[k][i] = parking[k][i] >> 1;
        if(parking[k+1][i] & 0x01) 
          parking[k][i] |= 0x80;
      }
      //parking[k+1][i] = parking[k+1][i] >> 1;
    }
  }
    

  shift_count++;
  if(shift_count == 8)
  {
    shift_count = 0;
    dot_num++;
    if (dot_num == 10) dot_num = 0;
  }
}
