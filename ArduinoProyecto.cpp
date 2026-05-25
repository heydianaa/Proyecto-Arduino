#include <Servo.h>
Servo miServo;

const int boton1 = 2; 
const int boton2 = 16;

// Display
const int a = 4;
const int b = 5;
const int c = 17;
const int d = 18;
const int e = 15;
const int f = 6;
const int g = 7;

// Componentes
const int potenciometro = A5;
const int buzzer = 8;
const int servo = 3;

// RGB
const int rojo = 9;
const int verde = 10;
const int azul = 11;

//variables

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

  // boton modo

  estadoBoton1 = digitalRead(boton1);

  if (estadoBoton1 == HIGH && ultimoEstadoBoton1 == LOW) {

    modo++;

    if (modo > 2) {
      modo = 0;
    }

    alarmaSilenciada = 0;

    delay(50);
  }

  ultimoEstadoBoton1 = estadoBoton1;

  //modo 0

  if (modo == 0) {

    mostrar0();

    setColor(0, 0, 0);

    digitalWrite(buzzer, LOW);

    miServo.write(0);
  }

  //modo 1

  else if (modo == 1) {

    mostrar1();

    int lectura = analogRead(potenciometro);

    int lpm = map(lectura, 0, 1023, 0, 200);

    int angulo = map(lpm, 0, 200, 0, 180);

    miServo.write(angulo);

    digitalWrite(buzzer, LOW);

    // Bradicardia
    if (lpm < 60) {

      // Amarillo
      setColor(255, 255, 0);
    }

    // Normal
    else if (lpm <= 100) {

      // Verde
      setColor(0, 255, 0);
    }

    // Taquicardia
    else if (lpm <= 150) {

      // Rojo
      setColor(255, 0, 0);
    }

    // Taquicardia severa
    else {

      setColor(255, 0, 0);
      delay(200);

      setColor(0, 0, 0);
      delay(200);
    }
  }

  //modo 2

  else if (modo == 2) {

    mostrar2();

    int lectura = analogRead(potenciometro);

    int temperatura = map(lectura, 0, 1023, 20, 45);

    // alarma

    estadoBoton2 = digitalRead(boton2);

    if (estadoBoton2 == HIGH && ultimoEstadoBoton2 == LOW) {

      alarmaSilenciada = 1;

      digitalWrite(buzzer, LOW);

      delay(50);
    }

    ultimoEstadoBoton2 = estadoBoton2;

    // Hipotermia
    if (temperatura < 35) {

      // Morado
      setColor(255, 0, 255);

      miServo.write(0);

      if (alarmaSilenciada == 0) {
        digitalWrite(buzzer, HIGH);
      }
    }

    // Normal
    else if (temperatura <= 37) {

      // Cyan
      setColor(0, 255, 255);

      miServo.write(45);

      digitalWrite(buzzer, LOW);

      alarmaSilenciada = 0;
    }

    // Febricula
    else if (temperatura <= 38) {

      // Amarillo
      setColor(255, 255, 0);

      miServo.write(90);

      digitalWrite(buzzer, LOW);

      alarmaSilenciada = 0;
    }

    // Fiebre
    else if (temperatura <= 39) {

      // Naranja
      setColor(255, 120, 0);

      miServo.write(135);

      digitalWrite(buzzer, LOW);

      alarmaSilenciada = 0;
    }

    // Fiebre alta
    else {

      // Blanco
      setColor(255, 255, 255);

      miServo.write(180);

      if (alarmaSilenciada == 0) {
        digitalWrite(buzzer, HIGH);
      }
    }
  }
}

//LED RGB

void setColor(int red, int green, int blue) {

  analogWrite(rojo, red);
  analogWrite(verde, green);
  analogWrite(azul, blue);
}

//#0

void mostrar0() {

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

//#1

void mostrar1() {

  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

//#2

void mostrar2() {

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
