#define C4 1911
#define CS4 1803
#define D4 1702
#define DS4 1607
#define E4 1516
#define F4 1431
#define FS4 1351
#define G4 1275
#define GS4 1203
#define A4 1136
#define AS4 1072
#define B4 1012
#define C3 955
#define CS4 901
#define D3 851
#define CS4 803
#define E3 758
#define F3 715
#define CS4 675
#define G3 637
#define CS4 601
#define A3 568
#define CS4 536
#define B3 506
#define S 0
#define P -1
#define LEN 136

//double NOTE[8][12] = {
//  {30578.047408, 28861.861359, 27241.943876, 25712.955987, 24253.948543, 22907.670634, 21621.948873, 20408.413164, 19262.997708, 18181.818182, 17161.342360, 16198.161833},
//  {15289.023704, 14430.909854, 13620.971938, 12856.494522, 12134.906179, 11453.822198, 10810.974436, 10204.196170, 9631.480301, 9090.909091, 8580.678543, 8099.080916},
//  {7644.511852, 7215.460134, 6810.485969, 6428.243129, 6067.453089, 5726.914379, 5405.487218, 5102.100688, 4815.742470, 4545.454545, 4290.337431, 4049.538818},
//  {3822.255926, 3607.730067, 3405.242985, 3214.121565, 3033.726545, 2863.457189, 2702.743609, 2551.050344, 2407.870655, 2272.727273, 2145.168715, 2024.769819},
//  {1911.128328, 1803.864708, 1702.621782, 1607.060782, 1516.863502, 1431.728390, 1351.371805, 1275.525009, 1203.935327, 1136.363636, 1072.584473, 1012.384910},
//  {955.564347, 901.932029, 851.310891, 803.530391, 758.431866, 715.864195, 675.685720, 637.762423, 601.967591, 568.181818, 536.292236, 506.192506},
//  {477.781945, 450.966218, 425.655446, 286.613762, 379.215933, 357.932097, 337.842974, 318.881313, 300.983796, 284.090909, 268.146118, 253.096253},
//  {238.891030, 225.483109, 212.827723, 200.882598, 189.607931, 178.966049, 168.921458, 159.440631, 150.491920, 142.045455, 134.073059, 126.548110}
//};

//int bell[32] = {G4, G4, A4, A4, G4, G4, E4, E4, G4, G4, E4, E4, D4, D4, D4, D4, G4, G4, A4, A4, G4, G4, E4, E4, G4, E4, D4, E4, C4, C4, C4, C4};
int canon[136] = {G3, G3, E3, F3, G3, G3, E3, F3, G3, B4, A4, B4, C3, D3, E3, F3, E3, E3, C3, D3, E3, E3, E4, F4, G4, A4, G4, F4, G4, C3, B4, C3,
                 A4, A4, C3, B4, A4, A4, G4, F4, G4, F4, E4, F4, G4, A4, B4, C3, A4, A4, C3, B4, C3, C3, B4, C3, B4, A4, B4, C3, D3, E3, F3, G3,
                 E3, E3, C3, D3, E3, E3, D3, C3, D3, B4, C3, D3, E3, D3, C3, B4, C3, C3, A4, B4, C3, C3, C4, D4, E4, F4, E4, D4, E4, C3, B4, C3,
                 A4, A4, C3, B4, A4, A4, G4, F4, G4, F4, E4, F4, G4, A4, B4, C3, A4, A4, C3, B4, C3, C3, B4, A4, B4, C3, D3, C3, B4, C3, A4, B4,
                 C3, C3, C3, C3, C3, C3, C3, C3
//};
//int houl[LEN] = {D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, D4, S,             //13
//                G4, G4, G4, G4, G4, G4, G4, G4, G4, G4, G4, G4, S               //13
//                AS4, AS4, AS4, AS4, AS4, AS4, AS4, AS4, AS4, AS4, AS4, AS4, S   //13
                
};
void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

void loop() {
//  for (int k = 4; k <= 5; k++) {
//    for (int i = 0; i < 12; i++) {
//      for (int j = 0; j < 500000 / NOTE[k][i]; j++) {
//        digitalWrite(3, HIGH);
//        delayMicroseconds(NOTE[k][i]);
//        digitalWrite(3, LOW);
//        delayMicroseconds(NOTE[k][i]);
//      }
//    }
//  }

//    //BELL
//    for(int i = 0; i < LEN; i++) {
//      for (int j = 0; j < 250000 / bell[i]; j++) {
//        digitalWrite(3, HIGH);
//        delayMicroseconds(bell[i]);
//        digitalWrite(3, LOW);
//        delayMicroseconds(bell[i]);
//      }
//    }

    //CANON
    for(int i = 0; i < LEN; i++) {
      for (int j = 0; j < 125000 / canon[i]; j++) {
        digitalWrite(5, HIGH);
        delayMicroseconds(canon[i]);
        digitalWrite(5, LOW);
        delayMicroseconds(canon[i]);
      }
    }

//  //HOUL
//  for(int i = 0; i < LEN; i++) {
//    for (int j = 0; j < 125000 / houl[i]; j++) {.
//      if(houl[i] == S) {
//        
//      }
//
//      else if(houl[i] == P) {
//        
//      }
//
//      else {
//        digitalWrite(3, HIGH);.
//        delayMicroseconds(houl[i]);
//        digitalWrite(3, LOW);
//        delayMicroseconds(houl[i]);
//      }
//    }
//  }
}
