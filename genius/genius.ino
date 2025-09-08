/*
  Projeto desenvolvido para o laboratório FnE (Física na Escola), DFI (Departamento de física), UFS (Universidade Federal de Sergipe).
  Desenvolvido por: Francisco Passos - Frank Steps
  Desenvolvido em: 07/09/2025

  Sob a supervisão de: Edvaldo Alves
  Outros participantes deste projeto:
    * V. S. Junior (Scarnera)

  (Pela última vez...)
  Modificado por: Francisco Passos
  Modificado em: 07/09/2025

  E-mails para contato do desenvolvedor deste projeto:
  E-mail pessoal:       franciscopassos.contato@gmail.com   
  E-mail acadêmico:     francisco.alves@dcomp.ufs.br           
  E-mail empresarial:   contato@franksteps.com.br    

  Materiais de apoio durante a programação deste código fonte:
    Playlist do professor josé de assis: https://www.youtube.com/watch?v=gYgGgox5Q4o&list=PLbEOwbQR9lqwq5E0DW3CvjfmF4FoIAW1f  
    Website onlinegbd compiler: https://learn.onlinegdb.com/c%2B%2B_array

  Para a mais fácil visualização técnica deste projeto é necessário ter como base os conhecimentos em:
      * tipos de vaeriáveis e suas aplicações
      * funções e chamadas de funções em C++  
      * vetores/arrays em C++ 
      * conhecimento básico em circuitos eletrônicos
      * lógica de programação

  - Detalhes importantes sobre o projeto - 
      * Os botões estão configurados como pull down
*/

//indicando os pinos digitais de cada componente

//leds
const int red = 2;
const int green = 3;
const int blue = 4;
const int yellow = 5;
const int level = 6;

//botões
const int botao_r = 8;
const int botao_g = 9;
const int botao_b = 10;
const int botao_y = 11;

// **************** Variáveis globais do software **************** //

//array -> coração do projeto (é uma lista de variáveis de um único tipo) Neste projeto é conveniente o uso de inteiros (int)
int sequence[32] = {};
int leds[4] = { 2, 3, 4, 5, 6 };
int buttons[4] = { 8, 9, 10, 11 };

//int tone[4] = {262, 294, 330, 349}; -> irei implementar assim que os primeiros testes forem feitos

//indicando que o jogo começa no round 0
int round = 0;

//variáveis responsáveis pela resposta do usuário/jogador
int step = 0;
int button_pressed = 0;

//indica se o jogo terminou ou não
bool gameOver = false;

// ****************    Manipulação do software  **************** //
// ****************  Configurações e as chamadas   **************** //

//configurações iniciais -> definindo saída, entrada, chamando funções para indicar sinalização, serial e etc
void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(level, OUTPUT);
  pinMode(botao_r, INPUT);
  pinMode(botao_g, INPUT);
  pinMode(botao_b, INPUT);
  pinMode(botao_y, INPUT);
  led_start_lose(3, 500);
}

//função de loop (não me fale mais nada!)
void loop() {
  //separando as ações em funções - cada uma será responsável por uma etapa do jogo
  nextRound();
  reprSequence();
  waitPlayer();

  //reiniciando as variáveis caso seja fim de jogo
  if (gameOver == true) {
    sequence[32] = {};
    round = 0;
    step = 0;
    gameOver = false;
  }

  delay(1000);
}

// ****************     Funções do projeto    **************** //
// ****************   chamadas anteriormente   **************** //


//(quantas vezes vai piscar, por quanto tempo os leds irão ficar naquele estado (aceso ou apagado)
void led_start_lose(int Tblink, int time) {
  for (int i = 0; i < Tblink; i++) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(level, HIGH);
    delay(time);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(level, LOW);
    delay(time);
  }
}

//função responsável por aplicar a próxima rodada ao jogo
nextRound() {
  //sorteia um número e o adiciona ao array (vetor/lista) sequence[32]{};
  int rand = random(4);
  sequence[round] = rand;
  round++; //round + 1 = round++

  //verificar como software está lidando com as variáveis
  serial.println(rand);
}

//função responsável por aplicar a sequência criada software
reprSequence() {
  //liga o led análogo à array de sequencia
  for (int i = 0; i < round; i++) {
    digitalWrite(leds[sequence[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequence[i]], LOW);
    delay(100);
  }
}

//função responsável por verificar o desempenho do player
//move_made = jogada efetuada/feita
void waitPlayer() {
  // Loop que aguarda e confere cada jogada do jogador em relação à sequência
  for (int i = 0; i < round; i++) {
    bool move_made = false; //mantêm o software parado até o jogador pressionar o botão
    while (!move_made) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(buttons[i]) == HIGH) {
          button_pressed = i;
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          move_made = true; //marca que o jogador pressionou o botão
          delay(1000);
        }
      }
    }
    //O software precisa verificar se o jogador acertou a jogada - por isso, ao olhar o pior dos casos:
    if (sequence[step] != button_pressed) {
      //finalizando o jogo...
      led_start_lose(3, 1000);
      gameOver = true; //perdeu, mané 🤣
      break; //quebra o funcionamento desta função e volta para o void loop 
    }
    step++; //step + 1 = step++
  }
  //reiniciamos o passo do jogador para o 0 para indicar uma nova fase - voltando para o loop.
  step = 0;
}

