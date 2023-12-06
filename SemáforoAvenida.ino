#include <Arduino.h>

// Semáforo para coches y peatones ARDUINO
int carRed1 = 2 ;
int carYellow1 = 3;
int carGreen1 = 4;

int carRed2 = 5 ;
int carYellow2 = 6;
int carGreen2 = 7;

int peaRed1 = 8;
int peaGreen1 = 9;

int peaRed2 = 10;
int peaGreen2 = 11;

int button1 = 12;
int button2 = 23;
int button3 = 22;
int button4 = 24;

int TiempoCruce = 5000;
const int pinBuzzer = 30; //Constante que contiene el número del pin de Arduino
unsigned long TiempoCambio1 = 0;
unsigned long TiempoCambio2 = 0;

#line 26 "C:\\Users\\jdgar\\Documents\\Arduino\\sketch_nov30a\\sketch_nov30a.ino"
void setup();
#line 50 "C:\\Users\\jdgar\\Documents\\Arduino\\sketch_nov30a\\sketch_nov30a.ino"
void loop();
#line 95 "C:\\Users\\jdgar\\Documents\\Arduino\\sketch_nov30a\\sketch_nov30a.ino"
void cambioLuz(int semaforo);
#line 26 "C:\\Users\\jdgar\\Documents\\Arduino\\sketch_nov30a\\sketch_nov30a.ino"
void setup(){
  pinMode(carRed1, OUTPUT);
  pinMode(carYellow1, OUTPUT);
  pinMode(carGreen1, OUTPUT);
  pinMode(peaRed1, OUTPUT);
  pinMode(peaGreen1, OUTPUT);

  pinMode(carRed2, OUTPUT);
  pinMode(carYellow2, OUTPUT);
  pinMode(carGreen2, OUTPUT);
  pinMode(peaRed2, OUTPUT);
  pinMode(peaGreen2, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(pinBuzzer, OUTPUT);

  digitalWrite(carGreen1, HIGH);
  digitalWrite(peaRed1, HIGH);

  digitalWrite(carGreen2, HIGH);
  digitalWrite(peaRed2, HIGH);
}

void loop() {
  int estado1 = digitalRead(button1);
  int estado2 = digitalRead(button2);
  int estado3 = digitalRead(button3);
  int estado4 = digitalRead(button4);

//solo cambia el semáforo 1
  if ((estado1 || estado3)== HIGH && (millis() - TiempoCambio1) > 5000 ){
    delay(2000);
    for (int x=0; x<10; x++) {
      digitalWrite(carGreen1, HIGH);
      delay(250);
      digitalWrite(carGreen1, LOW);
      delay(250);
    }
    cambioLuz(1);
  }
//solo cambia el semáforo 2
  if ((estado2 || estado4) == HIGH && (millis() - TiempoCambio2) > 5000 ){
    delay(2000);
    for (int x=0; x<10; x++) {
      digitalWrite(carGreen2, HIGH);
      delay(250);
      digitalWrite(carGreen2, LOW);
      delay(250);
    }
    cambioLuz(2);
  }
//cambiar los dos al tiempo
  if ( ((estado1 || estado3)== HIGH && (millis() - TiempoCambio1) > 5000 ) && ((estado2 || estado4) == HIGH && (millis() - TiempoCambio2) > 5000 )) {
    delay(2000);
    for (int x=0; x<10; x++) {
      digitalWrite(carGreen1, HIGH);
      digitalWrite(carGreen2, HIGH);
      delay(250);
      digitalWrite(carGreen1, LOW);
      digitalWrite(carGreen2, LOW);
      delay(250);
    }
    cambioLuz(1);
    cambioLuz(2);
  }
  
}

void cambioLuz(int semaforo) {
  if (semaforo == 1) {
    digitalWrite(carGreen1,LOW);
    digitalWrite(carYellow1, HIGH);
    delay(2000);
    digitalWrite(carYellow1, LOW);
    digitalWrite(carRed1, HIGH);
    delay(1000);
    digitalWrite(peaRed1, LOW);
    digitalWrite(peaGreen1, HIGH);
    delay(TiempoCruce);
    for (int x=0; x<10; x++) {
      digitalWrite(peaGreen1, HIGH);
      tone(pinBuzzer, 1000, 500);
      delay(250);
      digitalWrite(peaGreen1, LOW);
      noTone(pinBuzzer);
      delay(250);
    }
    digitalWrite(peaRed1, HIGH);
    delay(500);
    digitalWrite(carYellow1, HIGH);
    digitalWrite(carRed1, LOW);
    delay(1000);
    digitalWrite(carGreen1, HIGH);
    digitalWrite(carYellow1, LOW);
    TiempoCambio1 = millis();
  } else if (semaforo == 2) {
    digitalWrite(carGreen2,LOW);
    digitalWrite(carYellow2, HIGH);
    delay(2000);
    digitalWrite(carYellow2, LOW);
    digitalWrite(carRed2, HIGH);
    delay(1000);
    digitalWrite(peaRed2, LOW);
    digitalWrite(peaGreen2, HIGH);
    delay(TiempoCruce);
    for (int x=0; x<10; x++) {
      digitalWrite(peaGreen2, HIGH);
      tone(pinBuzzer, 1000, 500);
      delay(250);
      digitalWrite(peaGreen2, LOW);
      noTone(pinBuzzer);
      delay(250);
    }
    digitalWrite(peaRed2, HIGH);
    delay(500);
    digitalWrite(carYellow2, HIGH);
    digitalWrite(carRed2, LOW);
    delay(1000);
    digitalWrite(carGreen2, HIGH);
    digitalWrite(carYellow2, LOW);
    TiempoCambio2 = millis();
  }
}

