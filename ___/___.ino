void setup() {
}

void loop() {
  analog.Write(9, map(analogRead(A0), 0,1023,0,255));
}
