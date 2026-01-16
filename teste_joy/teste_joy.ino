/*
 Programa desenvolvido para fazer os testes inciais com o joystick para o projeto do Arc Ace para aprender 
 como o mesmo pode ser aplicado no funcionamento do Arc Ace.

 Desenvolvedor:    Francisco Passos
 Desenvolvido por: 28/11/2025

 modificado em: 16/01/2026
*/

const int xJoyPin = A0;
const int yJoyPin = A1;
const int zonaPer = 100;

String saveDirUser(int mapX, int mapY){
  if(mapX ==  0 && mapY ==  1) return "UP";
  if(mapX ==  0 && mapY == -1) return "DOWN";
  if(mapX ==  1 && mapY ==  0) return "LEFT";
  if(mapX == -1 && mapY ==  0) return "RIGHT";

  return "...";
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  int xJoyValue = analogRead(xJoyPin);
  int yJoyValue = analogRead(yJoyPin);

  int xMapValue = 0;
  int yMapValue = 0;

  if (xJoyValue < 512 - zonaPer){
    xMapValue = -1; 
  } else if (xJoyValue > 512 + zonaPer) {
    xMapValue =  1; 
  }

  if (yJoyValue < 512 - zonaPer){
    yMapValue = -1; 
  } else if (yJoyValue > 512 + zonaPer) {
    yMapValue =  1; 
  }

  Serial.print("X: "); Serial.println(xMapValue);
  Serial.print("Y: "); Serial.println(yMapValue);

  Serial.println(saveDirUser(xMapValue, yMapValue));

  delay(100);
}
