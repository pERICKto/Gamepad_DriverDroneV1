#include <LiquidCrystal_I2C.h> // Se o seu display for I2C (com a plaquinha adaptadora atrás)
#include <Joystick.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// Configuração do Gamepad: 10 Botões, 0 Hat Switch, Apenas Eixo X ativado
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  10, 0,                  
  true, false, false,     
  false, false, false, 
  false, false, 
  false, false, false);

// Pinos dos botões e alavancas
int cima = 1; 
int baixo = 11;
int esquerda = 0;
int direita = 4;
int sonar = 5;

// MUDOU PARA A PORTA ANALÓGICA A2 (Protegendo o barramento I2C do pino 2)
int chave = A2; 

const int brilho = 13;
int alav_1 = 6;
int alav_2 = 7;

bool ligou = true;

// Pinos do Encoder Rotativo (CLK e DT)
const int pinCLK = 8;
const int pinDT = 9;
int ultimoEstadoCLK; 

// Pino do potenciômetro (Knobzinho / Vel)
const int freq = A1; 

// -------------------------------------------------------------
// Variáveis para o controle de tempo do encoder sem delay
unsigned long tempoApertoBotao8 = 0;
unsigned long tempoApertoBotao9 = 0;
const int duracaoPulso = 20; 
// -------------------------------------------------------------

void setup() {
  Joystick.setXAxisRange(0, 1023);
  lcd.init();                      
  lcd.backlight();
  
  pinMode(cima, INPUT_PULLUP);
  pinMode(baixo, INPUT_PULLUP);
  pinMode(esquerda, INPUT_PULLUP);
  pinMode(direita, INPUT_PULLUP);
  pinMode(sonar, INPUT_PULLUP);
  pinMode(alav_1, INPUT_PULLUP);
  pinMode(alav_2, INPUT_PULLUP);
  pinMode(brilho, OUTPUT);
  pinMode(chave, INPUT_PULLUP); 

  pinMode(pinCLK, INPUT_PULLUP);
  pinMode(pinDT, INPUT_PULLUP);

  ultimoEstadoCLK = digitalRead(pinCLK);

  // Animação de inicialização da máquina
  analogWrite(brilho, 10);
  delay(750);
  analogWrite(brilho,100);
  delay(100);
  analogWrite(brilho, 50);
  delay(50);
  analogWrite(brilho,170);
  delay(50);
  analogWrite(brilho, 20);
  delay(50);
  analogWrite(brilho,170);
  delay(50);
  analogWrite(brilho, 20);
  delay(50);
  analogWrite(brilho,170);
  delay(50);
  analogWrite(brilho, 50);
  delay(50);
  analogWrite(brilho,170);
  delay(50);
  analogWrite(brilho, 20);
  delay(50);
  analogWrite(brilho,170);
  delay(50);
  analogWrite(brilho, 20);
  delay(50);
  analogWrite(brilho,170);
  delay(100);
  analogWrite(brilho, 20);
  delay(1250);
  analogWrite(brilho, 200);
  
  lcd.setCursor(0,0); 
  lcd.print("b"); delay(500);
  lcd.print("e"); delay(75);
  lcd.print("m"); delay(75);
  lcd.print("-"); delay(75);
  lcd.print("v"); delay(75);
  lcd.print("i"); delay(75);
  lcd.print("n"); delay(75);
  lcd.print("d"); delay(75);
  lcd.print("a"); delay(75);
  lcd.print("!");

  lcd.setCursor(0,1);
  lcd.print("V"); delay(75);
  lcd.print("e"); delay(75);
  lcd.print("r"); delay(75);
  lcd.print("o"); delay(75);
  lcd.print("n"); delay(75);
  lcd.print("i"); delay(75);
  lcd.print("c"); delay(75);
  lcd.print("a"); delay(75);
  lcd.print("  "); delay(75);
  lcd.print(":)"); delay(4000);

  Joystick.begin();
}

void loop() {
  
  // ================== ENCODER ==================
  int estadoAtualCLK = digitalRead(pinCLK);

  if (estadoAtualCLK != ultimoEstadoCLK && estadoAtualCLK == LOW) {
    if (digitalRead(pinDT) != estadoAtualCLK) {
      Joystick.setButton(7, 1);
      tempoApertoBotao8 = millis(); 
    } else {
      Joystick.setButton(8, 1);
      tempoApertoBotao9 = millis(); 
    }
  }
  
  ultimoEstadoCLK = estadoAtualCLK;

  if (tempoApertoBotao8 > 0 && (millis() - tempoApertoBotao8 >= duracaoPulso)) {
    Joystick.setButton(7, 0);
    tempoApertoBotao8 = 0;
  }

  if (tempoApertoBotao9 > 0 && (millis() - tempoApertoBotao9 >= duracaoPulso)) {
    Joystick.setButton(8, 0);
    tempoApertoBotao9 = 0;
  }

  // Eixo do potenciômetro
  Joystick.setXAxis(analogRead(freq));

  // ================== VALIDADOR DA CHAVE ==================
  
  // Se a chave for removida (HIGH)
  if (digitalRead(chave) == HIGH) {
    if (ligou == true) { 
      lcd.clear();
      analogWrite(brilho, 10);
      lcd.setCursor(0,0);
      lcd.print("p"); delay(75);
      lcd.print("o"); delay(75);
      lcd.print("r"); delay(75);
      lcd.print("-"); delay(75);
      lcd.print("f"); delay(75);
      lcd.print("a"); delay(75);
      lcd.print("v"); delay(75);
      lcd.print("o"); delay(75);
      lcd.print("r"); delay(75);

      lcd.setCursor(0,1);
      lcd.print("i"); delay(75);
      lcd.print("n"); delay(75);
      lcd.print("s"); delay(75);
      lcd.print("e"); delay(75);
      lcd.print("r"); delay(75);
      lcd.print("i"); delay(75);
      lcd.print("r"); delay(75);
      lcd.print("-"); delay(75);
      lcd.print("c"); delay(75);
      lcd.print("h"); delay(75);
      lcd.print("a"); delay(75);
      lcd.print("v"); delay(75);
      lcd.print("e"); delay(3000);
      
      ligou = false; 
    }
  }
  
  // Se a chave for inserida (LOW)
  else if (digitalRead(chave) == LOW) {
    if (ligou == false) { 
      lcd.clear();
      analogWrite(brilho, 200); 
      lcd.setCursor(0,0);
      lcd.print("o"); delay(75);
      lcd.print("p"); delay(75);
      lcd.print("e"); delay(75);
      lcd.print("r"); delay(75);
      lcd.print("a"); delay(75);
      lcd.print("c"); delay(75);
      lcd.print("i"); delay(75);
      lcd.print("o"); delay(75);
      lcd.print("n"); delay(75);
      lcd.print("a"); delay(75);
      lcd.print("l"); delay(75);
      
      ligou = true; 
    }
  }

  // ================== LEITURA DOS BOTÕES ==================
  if (ligou == true) {
    Joystick.setButton(0, !digitalRead(cima));
    Joystick.setButton(1, !digitalRead(baixo));
    Joystick.setButton(2, !digitalRead(esquerda));
    Joystick.setButton(3, !digitalRead(direita));
    Joystick.setButton(4, !digitalRead(sonar));
    Joystick.setButton(5, !digitalRead(alav_1));
    Joystick.setButton(6, !digitalRead(alav_2));
  } else {
    Joystick.setButton(0, 0);
    Joystick.setButton(1, 0);
    Joystick.setButton(2, 0);
    Joystick.setButton(3, 0);
    Joystick.setButton(4, 0);
    Joystick.setButton(5, 0);
    Joystick.setButton(6, 0);
  }
}