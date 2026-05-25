Sistema de Monitoreo con Arduino

El proyecto se realizó con Arduino utilizando un servomotor, display de 7 segmentos, LED RGB, buzzer y potenciometro para simular un sistema básico de monitoreo biomédico.

**Funcionamiento**
El sistema cuenta con 3 modos de operación controlados mediante botones.

_Modo 0 - Reposo_
- El displau muestra el número 0.
- El servomotor permanece en 0°.
- LEDs y Buzzer apagados.

_Modo 1 - Frecuencia Cardíaca_
 - El display muestra el modo 1.
 - El potenciómetro simula las pulsaciones por minuto (LPM).
 - El servomotor cambia de ángulo dependiendeo del valor leído.
 - El LED RGV cambia de color según el estado:
    - Amarillo - Bradicardia
    - Verde - Normal
    - Rojo - Taquicardia
    - Rojo parpadeante - Taquicardia severa

_Modo 2 - Temperatura Corporal_
 - El display muestra el número 2.
 - El potenciómetro simula la temperatura corporal.
 - El LED RGB indica el estado térmico:
    - Morado - Hipotermia
    - Cyan - Normal
    - Amarillo - Febrícula
    - Naranja - Fiebre
    - Blanco - Fiebre alta
  - El buzzer funciona como alarma en estados críticos.

**Librerías**
Se utilizó la libreria <Servo.h>
