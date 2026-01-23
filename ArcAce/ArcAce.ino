/*
  Projeto desenvolvido para o laboratório FnE (Física na Escola), DFI (Departamento de física), UFS (Universidade Federal de Sergipe).
  Desenvolvido por: Francisco Passos - Frank Steps
  Desenvolvido em: 07/09/2025

  Sob a supervisão de: Edvaldo Alves
  Outros participantes deste projeto:
    * V. S. Junior (Scarnera) -> Vai fazer a parte mais chata 🙏🙏🙏🙏🙏🙏🙏🙏🙏

  Pela última vez:
  Modificado por: Francisco Passos
  Modificado em: 23/01/2026

  E-mails para contato do desenvolvedor deste projeto:
  E-mail pessoal:       franciscopassos.contato@gmail.com   
  E-mail acadêmico:     francisco.alves@dcomp.ufs.br           
  E-mail empresarial:   contato@franksteps.com.br    

  Materiais de apoio durante a programação deste código fonte:
    Playlist do professor josé de assis: https://www.youtube.com/watch?v=gYgGgox5Q4o&list=PLbEOwbQR9lqwq5E0DW3CvjfmF4FoIAW1f  
    Website onlinegdb compiler: https://learn.onlinegdb.com/c%2B%2B_array

  Para a mais fácil visualização técnica deste projeto é necessário ter como base os conhecimentos em:
      * lógica de programação
      * tipos de vaeriáveis e suas aplicações
      * funções e chamadas de funções em C++  
      * vetores/arrays em C++ 
      * conhecimento básico em circuitos eletrônicos

  - Detalhes importantes sobre o projeto - 

      * Frequência das notas:
        Dó - 262 Hz
        Ré - 294 Hz
        Mi - 330 Hz
        Fá - 349 Hz
        Sol - 392 Hz
        Lá - 440 Hz
        Si - 494 Hz
        #Dó - 528 Hz

   Detalhes: Estou fazendo testes com o joystick e entendendo o seu funcionamento. Assim que conveniente, irei implementá-lo a este 
   código. 
*/

// leds
const int red = 2;
const int green = 4;
const int blue = 5;
const int yellow = 3;

// buzzer passivo
const int buzzer = 6;

// joystick
const int xJoyPin = A0;
const int yJoyPin = A1;

// Botões do ArcAce 
const int play_button = 7;
const int stop_button = 9;

bool continue_game = false; 
bool stop_game = false; 

// **************** Variáveis globais do software **************** //

// array -> coração do projeto (é uma lista de variáveis de um único tipo) Neste projeto é conveniente o uso de inteiros (int)
int sequence[32] = {};
int leds[4] = { blue, red, green, yellow };
int tones[4] = { 262, 294, 330, 349 };

String dirJoyStick[4] = {"RIGHT", "LEFT", "DOWN", "UP"};

// indicando que o jogo começa no round 0
int Round = 0;

// indica se o jogo terminou ou não
bool gameOver = false;

// variáveis para o funcionamento do joystick
const int zonaPer = 170;

int xJoyValue;
int yJoyValue;


// ****************    Manipulação do software  **************** //
// ****************  Configurações e as chamadas   **************** //

// configurações iniciais -> definindo saída, entrada, chamando funções para indicar sinalização, serial e etc
void setup() {
  Serial.begin(9600);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);

  pinMode(buzzer, OUTPUT);
  
  pinMode(play_button, INPUT_PULLUP);
  pinMode(stop_button, INPUT_PULLUP);

  randomSeed(analogRead(A3));

  led_start_lose(3, 500);
}

// função de loop (não me fale mais nada!)
void loop() {
  if (!continue_game) {
    if (digitalRead(play_button) == LOW) {
      delay(50);
      if (digitalRead(play_button) == LOW) {
        continue_game = true;
      }
    }
    return;
  }

  nextRound();
  reprSequence();
  waitPlayer(); 

  // reiniciando as variáveis caso seja fim de jogo
  if (gameOver) {
    memset(sequence, 0, sizeof(sequence));
    Round = 0;
    gameOver = false;
  }

  delay(1000);
}


// ****************     Funções do projeto    **************** //
// ****************   chamadas anteriormente   **************** //


bool validMoveDetected(){
  if(xJoyValue < 512 - zonaPer || xJoyValue > 512 + zonaPer ||
     yJoyValue < 512 - zonaPer || yJoyValue > 512 + zonaPer  ){
    return true;
  } else {
    return false;
  }
}

int dirJoyID(){
  if(!validMoveDetected()) return -1;      // inválido 

  if(xJoyValue < 512 - zonaPer) return 0;  // blue     - direita
  if(xJoyValue > 512 + zonaPer) return 1;  // red      - esquerda
  if(yJoyValue < 512 - zonaPer) return 2;  // green    - baixo
  if(yJoyValue > 512 + zonaPer) return 3;  // yellow   - cima

  return -1; 
}


// (quantas vezes vai piscar, por quanto tempo os leds irão ficar naquele estado (aceso ou apagado)
void led_start_lose(int tBlink, int ledTime) {
  for (int i = 0; i < tBlink; i++) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(yellow, HIGH);
    delay(ledTime);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(yellow, LOW);
    delay(ledTime);
  }
}

// função responsável por aplicar a próxima rodada ao jogo
void nextRound() {
  if (Round >= 32) {
    gameOver = true;
    return;
  }

  // sorteia um número e o adiciona ao array (vetor/lista) sequence[32]{};
  int randValue = random(4);
  sequence[Round] = randValue;
  Round++; 

  // verificar como software está lidando com as variáveis
  Serial.println(randValue);
}

// função responsável por aplicar a sequência criada software
void reprSequence() {
  //liga o led análogo à array de sequencia
  for (int i = 0; i < Round; i++) {
    digitalWrite(leds[sequence[i]], HIGH);
    tone(buzzer, tones[sequence[i]]);
    delay(500);
    digitalWrite(leds[sequence[i]], LOW);
    noTone(buzzer);
    delay(100);
  }
}

// função responsável por verificar o desempenho do player
// move_made = jogada efetuada/feita
void waitPlayer() {
  int step = 0;
  int direction = 0;

  // Loop que aguarda e confere cada jogada do jogador em relação à sequência
  for (int i = 0; i < Round; i++) {
    bool move_made = false; 
    
    while (!move_made) {
      // caso o jogador desista da partida, o jogo acaba da mesma forma como se o jogador tivesse errado a sequência 
      if (digitalRead(stop_button) == LOW) {
        stop_game = true;
        move_made = true; 
      }

      xJoyValue = analogRead(xJoyPin);
      yJoyValue = analogRead(yJoyPin);

      direction = dirJoyID();

      // Se alguma direção válida foi detectada
      if (direction != -1) {

        // feedback visual e sonoro
        digitalWrite(leds[direction], HIGH);
        tone(buzzer, tones[direction]);
        delay(300);

        digitalWrite(leds[direction], LOW);
        noTone(buzzer);

        move_made = true;

        // aguarda o joystick voltar para o centro
        while (validMoveDetected()) {
          xJoyValue = analogRead(xJoyPin);
          yJoyValue = analogRead(yJoyPin);
          delay(10);
        }

        delay(300);
      }
    }

    // Verificação da jogada
    if ((sequence[step] != direction) || stop_game == true) {
      
      // finalizando o jogo... 🙏
      led_start_lose(3, 700);
      gameOver = true;  // perdeu, mané
      continue_game = false;
      stop_game = false;
      break;
    }
    
    step++;
  }

  // reiniciamos o passo do jogador para o 0 para indicar uma nova fase
  step = 0;
}
