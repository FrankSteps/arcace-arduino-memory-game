/*
 Programa desenvolvido para fazer os testes inciais com o joystick para o projeto do Arc Ace para aprender 
 como o mesmo pode ser aplicado no funcionamento do Arc Ace.

 Desenvolvedor:    Francisco Passos
 Desenvolvido por: 28/11/2025

 modificado em: 14/01/2026
*/

const int xJoyPin = A0;
const int yJoyPin = A1;
      int vectJoy[];

void setup(){
  Serial.begin(9600);
}

void loop(){
  int xJoyValue = digitalRead(xJoyPin);
  int yJoyValue = digitalRead(yJoyPin);

  int xMapValue = map(xJoyValue, 0, 1024, -10, 10); 
  int yMapValue = map(yJoyValue, 0, 1024, -10, 10);

  Serial.print("X: "); Serial.println(xMapValue);
  Serial.print("Y: "); Serial.println(yMapValue);

  delay(100);
}
