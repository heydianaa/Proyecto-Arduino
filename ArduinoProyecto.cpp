#include <Servo.h>
Servo miServo;

// PINES 

// Botones
const int boton1 = 2;
const int boton2 = 3;

// Display
const int a = 4;
const int b = 5;
const int c = A3;
const int d = A4;
const int e = A5;
const int f = 6;
const int g = 7;

// Componentes
const int buzzer = 8;
const int rojo = 9;
const int verde = 10;
const int azul = 11;
const int servo = 12;

// Potenciómetro
const int potenciometro = A7;

// VARIABLES 

int modo = 0;

int estadoBoton1 = 0;
int ultimoEstadoBoton1 = 0;

int estadoBoton2 = 0;
int ultimoEstadoBoton2 = 0;

int alarmaSilenciada = 0;

void setup() {

  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);

  miServo.attach(servo);

  miServo.write(0);
}

void loop() {

  
  // BOTON CAMBIO MODO
  
  estadoBoton1 = digitalRead(boton1);

  if (estadoBoton1 == HIGH && ultimoEstadoBoton1 == LOW) {

    modo++;

    if (modo > 2) {
      modo = 0;
    }

    alarmaSilenciada = 0;

    delay(60);
  }

  ultimoEstadoBoton1 = estadoBoton1;

 
  // MODO 0
 

  if (modo == 0) {

    mostrar0();

    setColor(LOW, LOW, LOW);

    digitalWrite(buzzer, LOW);

    miServo.write(0);

    delay(20);
  }

  // MODO 1
 

  else if (modo == 1) {

    mostrar1();

    int lectura = analogRead(potenciometro);

    int lpm = map(lectura, 0, 1023, 0, 200);

    
    int angulo = map(lectura, 0, 1023, 0, 180);

    miServo.write(angulo);

    delay(15);

    digitalWrite(buzzer, LOW);

    // BRADICARDIA
    if (lpm < 60) {

      // amarillo
      setColor(HIGH, HIGH, LOW);
    }

    // NORMAL
    else if (lpm <= 100) {

      // verde
      setColor(LOW, HIGH, LOW);
    }

    // TAQUICARDIA
    else if (lpm <= 150) {

      // rojo
      setColor(HIGH, LOW, LOW);
    }

    // TAQUICARDIA SEVERA
    else {

      // rojo parpadeando rapido
      setColor(HIGH, LOW, LOW);

      delay(25);

      setColor(LOW, LOW, LOW);

      delay(25);
    }

    delay(20);
  }

 
  // MODO 2


  else if (modo == 2) {

    mostrar2();

    int lectura = analogRead(potenciometro);

    int temperatura = map(lectura, 0, 1023, 20, 45);

    
    // BOTON ALARMA
   

    estadoBoton2 = digitalRead(boton2);

    if (estadoBoton2 == HIGH && ultimoEstadoBoton2 == LOW) {

      alarmaSilenciada = 1;

      digitalWrite(buzzer, LOW);

      delay(60);
    }

    ultimoEstadoBoton2 = estadoBoton2;

    // HIPOTERMIA
    if (temperatura < 35) {

      // morado
      setColor(HIGH, LOW, HIGH);

      miServo.write(0);

      if (alarmaSilenciada == 0) {
        digitalWrite(buzzer, HIGH);
      }
    }

    // NORMAL
    else if (temperatura <= 37) {

      // cyan
      setColor(LOW, HIGH, HIGH);

      miServo.write(45);

      digitalWrite(buzzer, LOW);

      alarmaSilenciada = 0;
    }

    // FEBRICULA
    else if (temperatura <= 38) {

      // amarillo
      setColor(HIGH, HIGH, LOW);

      miServo.write(90);

      digitalWrite(buzzer, LOW);

      alarmaSilenciada = 0;
    }

    // FIEBRE
    else if (temperatura <= 39) {

      // rojo
      setColor(HIGH, LOW, LOW);

      miServo.write(135);

      digitalWrite(buzzer, LOW);

      alarmaSilenciada = 0;
    }

    // FIEBRE ALTA
    else {

      // blanco
      setColor(HIGH, HIGH, HIGH);

      miServo.write(180);

      if (alarmaSilenciada == 0) {
        digitalWrite(buzzer, HIGH);
      }
    }

    delay(20);
  }
}


// FUNCION RGB


void setColor(int r, int v, int aColor) {

  digitalWrite(rojo, r);
  digitalWrite(verde, v);
  digitalWrite(azul, aColor);
}


// DISPLAY 0


void mostrar0() {

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}


// DISPLAY 1


void mostrar1() {

  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}


// DISPLAY 2

void mostrar2() {

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
