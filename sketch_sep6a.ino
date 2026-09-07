#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
6, 0, // 6 Botões, 0 Hat Switch
true, true, true, // Eixos X, Y e Z LIGADOS
false, false, false, // Sem rotação
false, false, // Sem rudder / throttle
false, false, false); // Sem aceleração / freio

int cima = 1;
int baixo = 3;
int esquerda = 2;
int direita = 4;
int sonar = 5;

int alav_1 = 6;
int alav_2 = 7;
int enc_1 = 8;
int enc_2 = 9;
//10 alav
//11 alav
//12 alav

//knobizin
const int freq = A1; //vel
void setup() {

Joystick.setXAxisRange(0, 1023);

pinMode(cima, INPUT_PULLUP);
pinMode(baixo, INPUT_PULLUP);
pinMode(esquerda, INPUT_PULLUP);
pinMode(direita, INPUT_PULLUP);
pinMode(sonar, INPUT_PULLUP);

pinMode(alav_1, INPUT_PULLUP);
pinMode(alav_2, INPUT_PULLUP);
pinMode(enc_1, INPUT_PULLUP);
pinMode(enc_2, INPUT_PULLUP);

Joystick.begin();
}

void loop() {
// Leitura dos botões
if (digitalRead(cima) == LOW) Joystick.setButton(1, 1);
else Joystick.setButton(1, 0);

if (digitalRead(baixo) == LOW) Joystick.setButton(3, 1);
else Joystick.setButton(3, 0);

if (digitalRead(esquerda) == LOW) Joystick.setButton(2, 1);
else Joystick.setButton(2, 0);

if (digitalRead(direita) == LOW) Joystick.setButton(4, 1);
else Joystick.setButton(4, 0);

if (digitalRead(sonar) == LOW) Joystick.setButton(5, 1);
else Joystick.setButton(5, 0);

// Leitura dos 3 potenciômetros nos eixos X, Y e Z
Joystick.setXAxis(analogRead(freq));

delay(10);
}