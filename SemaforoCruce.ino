#include "SevSeg.h"

struct Semaforo {
  int r;
  int a;
  int v;
  int rp;
  int vp;
  int bp;
};

const int periodoS = 20000;
unsigned long tInicio = 0;
unsigned long lastPause= 0;
volatile int bandera = 0;
long unsigned int lastBtnState = 1;

struct Semaforo s1 = {16,17,5,18,19,2};
// struct Semaforo s2 = {14,27,26,33,25,15};

SevSeg sevseg;

void setup() {
  byte numDigits = 4;
  bool resistorsOnSegments = 0;
  byte digitPins[] = {21, 23, 4, 22}; //D1, D2, D3, D4
  byte segmentPins[] = {13, 14, 27, 26, 25, 12, 33, 32};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  pinMode(s1.r, OUTPUT);
  pinMode(s1.a, OUTPUT);
  pinMode(s1.v, OUTPUT);
  pinMode(s1.rp, OUTPUT);
  pinMode(s1.vp, OUTPUT);
  pinMode(s1.bp, INPUT);
  attachInterrupt(digitalPinToInterrupt(s1.bp), prioridad, RISING);
  
  Serial.begin(9600);
  inicial();
}

void loop() {
  // for (int32_t i = 0; i<100; i++) {
    sevseg.setNumber(3641);
  //   sevseg.refreshDisplay();
  //   delay(500);
  // }
  // activarSemaforosenCruz();
  // activarSemaforosenCruz();

  activarSemaforoLineal();
}

void inicial(){
  digitalWrite(s1.r, HIGH);
  // digitalWrite(s2.r, HIGH);
  digitalWrite(s1.rp, HIGH);
  // digitalWrite(s2.rp, HIGH);
  delay(5000);
}

void activarSemaforosenCruz(){
  digitalWrite(s1.a, HIGH);
  // digitalWrite(s2.r, HIGH);
  delay(2000);
  digitalWrite(s1.r, LOW);
  digitalWrite(s1.a, LOW);
  digitalWrite(s1.v, HIGH);
  // digitalWrite(s2.rp, LOW);
  // digitalWrite(s2.vp, HIGH);
  if(digitalRead(s1.bp) == LOW) prioridad();
  delay(5000);
  // blink(s2.vp, s2.rp);
  blink(s1.v, s1.a);
  digitalWrite(s1.a, LOW);
  digitalWrite(s1.r, HIGH);
  if(digitalRead(s1.bp) == LOW) prioridad();
  delay(2000);
}

void blink(int led1, int led2){
  tInicio = millis();
  while(millis() - tInicio < 3000){
    digitalWrite(led1, digitalRead(led1)==HIGH? LOW: HIGH);
    delay(500);
  }
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(2000);
}

void prioridad(){
  bandera = 1;
}
void prioridad2(){
  bandera = 1;
}

void activarSemaforoLineal(){
  if(bandera && millis() - lastPause > 18000){
    lastPause = millis();
    detachInterrupt(digitalPinToInterrupt(s1.bp));
    pausarSemaforos();
    
    attachInterrupt(digitalPinToInterrupt(s1.bp), prioridad, CHANGE);
    lastPause = millis();
    bandera = 0;
    lastBtnState = 1;
  }else{
    if(lastBtnState == 1){
      digitalWrite(s1.a, HIGH);
      // digitalWrite(s2.a, HIGH);
      delay(1000);
      digitalWrite(s1.r, LOW);
      digitalWrite(s1.a, LOW);
      // digitalWrite(s2.r, LOW);
      // digitalWrite(s2.a, LOW);
      digitalWrite(s1.v, HIGH);
      // digitalWrite(s2.v, HIGH);
      lastBtnState = 0;
    }
  }
}

void pausarSemaforos(){
  blink2();
  activarCronometro();

}

void blink2(){
  tInicio = millis();
  while(millis() - tInicio < 4000){
    digitalWrite(s1.v, digitalRead(s1.v)==HIGH? LOW: HIGH);
    // digitalWrite(s2.v, digitalRead(s2.v)==HIGH? LOW: HIGH);
    delay(500);
  }
  digitalWrite(s1.v, LOW);
  // digitalWrite(s2.v, LOW);
  digitalWrite(s1.a, HIGH);
  // digitalWrite(s2.a, HIGH);
  delay(2000);
  digitalWrite(s1.a, LOW);
  // digitalWrite(s2.a, LOW);
  digitalWrite(s1.r, HIGH);
  // digitalWrite(s2.r, HIGH);
  delay(1000);
  digitalWrite(s1.rp, LOW);
  // digitalWrite(s2.rp, LOW);
  digitalWrite(s1.vp, HIGH);
  // digitalWrite(s2.vp, HIGH);
  delay(4000);
}

void activarCronometro(){
  tInicio = millis();
  for (int i= 9; i > 0; i--) {
    //representar(i); // 7Segmentos4digitos
  }
  // while(millis() - tInicio < 10000){
  //   // 7-seg
  // }
  blink2P();
  delay(2000);
}

void blink2P(){
  tInicio = millis();
  while(millis() - tInicio < 6000){
    digitalWrite(s1.vp, digitalRead(s1.vp)==HIGH? LOW: HIGH);
    // digitalWrite(s2.vp, digitalRead(s2.vp)==HIGH? LOW: HIGH);
    delay(500);
  }
  digitalWrite(s1.vp, LOW);
  // digitalWrite(s2.vp, LOW);
  digitalWrite(s1.rp, HIGH);
  // digitalWrite(s2.rp, HIGH);
}
