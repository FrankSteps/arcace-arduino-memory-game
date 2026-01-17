/*
 Programa desenvolvido para fazer os testes inciais com o joystick para o projeto do Arc Ace para aprender 
 como o mesmo pode ser aplicado no funcionamento do Arc Ace.

 Desenvolvedor:    Francisco Passos
 Desenvolvido por: 28/11/2025

 modificado em: 17/01/2026
 
 Estado deste código de teste: Pronto para ser aplicado ao código principal
*/

const int xJoyPin = A0;
const int yJoyPin = A1;
const int zonaPer = 100;

int xJoyValue;
int yJoyValue;

String dirJoyStick[4] = {"LEFT", "RIGHT", "UP", "DOWN"};
  

bool validMoveDetected(){
  if(xJoyValue < 512 - zonaPer || xJoyValue > 512 + zonaPer ||
     yJoyValue < 512 - zonaPer || yJoyValue > 512 + zonaPer  ){
    return true;
  } else {
    return false;
  }
}

int dirJoyID(){
  if(!validMoveDetected()) return -1;

  if(xJoyValue < 512 - zonaPer) return 0;
  if(xJoyValue > 512 + zonaPer) return 1;
  if(yJoyValue < 512 - zonaPer) return 2;
  if(yJoyValue > 512 + zonaPer) return 3;

  // unidentified
  return -1; 
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  xJoyValue = analogRead(xJoyPin);
  yJoyValue = analogRead(yJoyPin);

  int dir = dirJoyID();

  if (dir != -1){
    Serial.println(dirJoyStick[dir]);
  }
    
  delay(100);
}
