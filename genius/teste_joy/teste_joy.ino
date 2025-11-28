/*
  Programa desenvolvido para fazer os testes iniciais com o joystick para 
  o projeto Arc Ace para aprender como pode ser aplicado seu funcionamento

  Desenvolvedor:     Francisco Passos
  Desenvolvido em:   28/11/2025

  Modificado em:     28/11/2025
*/

const int xJoyPin = A0;
const int yJoyPin = A1;
      int vecJoyType[];

void setup(){
  Serial.begin(9600); 
}

void loop(){
  int xJoyValue = digitalRead(xJoyPin);
  int yJoyValue = digitalRead(yJoyPin);

  int xMappedValue = map(xJoyValue, 0, 1024, -100, 100);
  int yMappedValue = map(yJoyValue, 0, 1024, -100, 100); 

  /*
    criar uma espécie de condicional que permita distinguir baixo, cima, direita e esquerda apartir dos valores de x e y
    essa condicional deve ir salvando os valores no vetor string
  */

  Serial.print("X: ");
  Serial.println(xMappedValue);
  Serial.print("Y: ");
  Serial.println(yMappedValue);
  //mostrar o tipo de direção de acordo com os valores de x e y

  delay(100);
}
