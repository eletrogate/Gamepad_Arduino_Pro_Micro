/*
 * Gamepad com o Arduino Pro Micro
 * Eletrogate 2020   //   Arduino versao 1.8.12
 */

#include <Joystick.h>

#define Joystick_GND  21 // Setando o pino 21 como o GND do nódulo Joystick
#define Joystick_VCC  20 // Setando o pino 20 como o Vcc do nódulo Joystick
#define Joystick_VRX  A1 // Setando os pinos abaixo cada um com sua função
#define Joystick_VRY  A0
#define Joystick_SW   15
#define Button_B      5
#define Button_Y      4
#define Button_A      10
#define Button_X      16
#define Button_Start  3
#define Button_Select 2

// Criando um objeto do tipo Joystick, onde simulará um gamepad.
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  11, 0,                  // Quantidade de botões, Numero de Hat Switch
  true, true, false,     // Eixos X e Y no joystick, mas não o eixo Z
  false, false, false,   // Sem Rx, Ry, ou Rz
  false, false,          // Sem rudder ou throttle
  false, false, false);  // Sem acelerador, freio, ou direção
  
void setup() {
  Serial.begin(9600);
  pinMode(Joystick_GND, OUTPUT); // Setendo Joystick_GND como saída, já que ele deverá jogar o valor 0V para o módulo.
  pinMode(Joystick_VCC, OUTPUT); // Setendo Joystick_VCC como saída, já que ele deverá jogar o valor 5V para o módulo.
  pinMode(Joystick_VRX, INPUT); // Setando como entrada porque este pino deverá ler o valor do joystick
  pinMode(Joystick_VRY, INPUT); // Setando como entrada porque este pino deverá ler o valor do joystick
  pinMode(Joystick_SW , INPUT_PULLUP); // Todos os botões abaixo estão setados como INPUT_PULLUP, dispensando resistores.
  pinMode(Button_B , INPUT_PULLUP);
  pinMode(Button_Y , INPUT_PULLUP);
  pinMode(Button_A , INPUT_PULLUP);
  pinMode(Button_X , INPUT_PULLUP);
  pinMode(Button_Start , INPUT_PULLUP);
  pinMode(Button_Select , INPUT_PULLUP);
  digitalWrite(Joystick_VCC, HIGH);// Setendo o valor de 5V no VCC do Joystick
  digitalWrite(Joystick_GND, LOW); //Setendo o valor de GND no GND do Joystick
  
  Joystick.begin();
  Joystick.setXAxisRange(-127, 127); // Definindo os limites dos eixos do gamepad. Deixe esse valor padrão
  Joystick.setYAxisRange(-127, 127);
  
}

void loop() {
  //Setando os valores dos eixos e butões
  Joystick.setXAxis(map(analogRead(Joystick_VRY),0,1023,-127,127)); // Utilizando a função Map para que o sinal original de 0 1023 seja adequado a -127 a 127
  Joystick.setYAxis(map(analogRead(Joystick_VRX),0,1023,127,-127)); // Utilizando a função Map como no exemplo anterior, mas utilizando a vantagem da inversão
  Joystick.setButton(0, !digitalRead(Button_X)); // Como estamos usando INPUT_PULLUP, o valor precisa ser invertido.
  Joystick.setButton(1, !digitalRead(Button_A));
  Joystick.setButton(2, !digitalRead(Button_B));
  Joystick.setButton(3, !digitalRead(Button_Y));
  Joystick.setButton(9, !digitalRead(Button_Start));
  Joystick.setButton(8, !digitalRead(Button_Select));
  Joystick.setButton(10, !digitalRead(Joystick_SW));
  delay(10); // Um pequeno delay na ordem de fração do nosso movimento dos dedos.
}