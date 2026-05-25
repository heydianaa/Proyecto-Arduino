//#include <Servo.h>
//Servo miServo;

int boton1 = 2;  //modo
int boton2 = 3;  //alarma

int a = 4;
int b = 5;
int c = 17;
int d = 18;
int e = 19;
int f = 6;
int g = 7;

int potenciometro = 21;
int buzzer = 8;
int servo = 9;

int rojo = 16;
int azul = 14;
int verde = 15;


//Variables
int modo = 0;
int alarmaSilenciada = 0;

int estadoBoton1 = 0;
int ultimoEstadoBoton1 = 0;

int estadoBoton2 = 0;
int ultimoEstadoBoton2 = 0;

void setup() {

  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(potenciometro, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
}

void loop() {

  // ANTIREBOTE BOTON 1 - CAMBIO DE MODO
  estadoBoton1 = digitalRead(boton1);

  if (estadoBoton1 == HIGH && ultimoEstadoBoton1 == LOW) {

    modo = modo + 1;

    if (modo == 3) {
      modo = 0;
    }

    alarmaSilenciada = 0;
    delay(50);
  }

  ultimoEstadoBoton1 = estadoBoton1;

  //modo 0
  if (modo == 0) {

    //display 0
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);

    //RGB apagado
    digitalWrite(rojo, LOW);
    digitalWrite(azul, LOW);
    digitalWrite(verde, LOW);

    digitalWrite(buzzer, LOW);
  }

  //modo 1
  if (modo == 1) {

    //display 1
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);

    int lectura = analogRead(potenciometro);
    int lpm = map(lectura, 0, 1023, 0, 200);

    digitalWrite(buzzer, LOW);

    if (lpm < 60) {
      //amarillo - BRADICARDIA
      digitalWrite(rojo, LOW);
      digitalWrite(verde, LOW);
      digitalWrite(azul, HIGH);
    }

    else if (lpm >= 60 && lpm <= 100) {
      //verde - NORMAL
      digitalWrite(rojo, LOW);
      digitalWrite(verde, HIGH);
      digitalWrite(azul, LOW);
    }

    else if (lpm > 100 && lpm <= 150) {
      //rojo - TAQUICARDIA
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);
    }

    else if (lpm > 150) {
      //rojo parpadeante - TAQUICARDIA SEVERA
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);
      delay(200);

      digitalWrite(rojo, LOW);
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);
      delay(200);
    }
  }

  //modo 2
  if (modo == 2) {

    //display 2
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);

    int lectura = analogRead(potenciometro);
    int temperatura = map(lectura, 0, 1023, 20, 45);

    // ANTIREBOTE BOTON 2 - APAGAR ALARMA
    estadoBoton2 = digitalRead(boton2);

    if (estadoBoton2 == HIGH && ultimoEstadoBoton2 == LOW) {
      alarmaSilenciada = 1;
      digitalWrite(buzzer, LOW);
      delay(50);
    }

    ultimoEstadoBoton2 = estadoBoton2;

    //hipotermia
    if (temperatura < 35) {
      //morado
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, LOW);
      digitalWrite(azul, HIGH);

      if (alarmaSilenciada == 0) {
        digitalWrite(buzzer, HIGH);
      } else {
        digitalWrite(buzzer, LOW);
      }
    }

    //normal
    else if (temperatura >= 35 && temperatura <= 37) {
      //cyan
      digitalWrite(rojo, LOW);
      digitalWrite(verde, HIGH);
      digitalWrite(azul, HIGH);

      digitalWrite(buzzer, LOW);
      alarmaSilenciada = 0;
    }

    //febricula
    else if (temperatura > 37 && temperatura <= 38) {
      //amarillo
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(azul, LOW);

      digitalWrite(buzzer, LOW);
      alarmaSilenciada = 0;
    }

    //fiebre
    else if (temperatura > 38 && temperatura <= 39) {
      //anaranjado / rojo
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, LOW);
      digitalWrite(azul, LOW);

      digitalWrite(buzzer, LOW);
      alarmaSilenciada = 0;
    }

    //fiebre alta
    else if (temperatura > 39) {
      //blanco
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(azul, HIGH);

      if (alarmaSilenciada == 0) {
        digitalWrite(buzzer, HIGH);
      } else {
        digitalWrite(buzzer, LOW);
      }
    }
  }
}
