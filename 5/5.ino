int count = 0;
unsigned long time_value[50] = {};
unsigned int diff_time[33] = {};
unsigned char number_arr[32] = {};
int cnt = 0;
int remember_value = 0;
unsigned char remocon_num[2][8] = {
  { 0,1,1,0,1,0,0,0 },
  { 0,0,1,1,0,0,0,0 }
};

void myISR(){
  time_value[count] = micros();

  if(count > 0){ 
    diff_time[count] = time_value[count] - time_value[count -1];

    if(diff_time[count] > 13000 && diff_time[count] < 14000){
      count = 1;
    }
    if(diff_time[count] > 11000 && diff_time[count] < 12000){
      Serial.println(remember_value);
      count = 0;
    }
    
  }
  count ++;
  if(count == 34){
    count = 0;
    
    for(int i = 0; i < 33; i++){
      diff_time[i] = time_value[i+1]-time_value[i];
    }
    
    for(int i = 0; i < 33; i++){
      if(i == 0) continue;
      if(diff_time[i] > 1000 && diff_time[i] < 1500) {
        number_arr[i-1] = 0;
      }
      else if(diff_time[i] > 2000 && diff_time[i] < 2500){
        number_arr[i-1] = 1;
      }
    }
    
    for(int j =0; j < 2; j++){
      for(int i = 16 ; i < 24; i++){
       if(number_arr[i] == remocon_num[j][i-16]) {
        cnt++;
       }
        if(cnt == 8) {
          remember_value = j;
          Serial.println("Is " + String(remember_value));
        }
      }
      cnt = 0;
    }
    
  }
}

void setup() {
  Serial.begin(9600);
  attachInterrupt(1,myISR, FALLING); // 0 - 2, 1 - 3
}

void loop() {

}
