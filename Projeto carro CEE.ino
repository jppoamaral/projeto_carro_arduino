// Define os pinos de utilização do Driver L298.
const int motorA1  = 9;    // Pin  5 of L293.
const int motorA2  = 3;    // Pin  6 of L293.
const int motorB1  = 11;   // Pin 10 of L293.
const int motorB2  = 10;   // Pin 9 of L293.

const int buzzer = 12 ;   // Define o Pino 12 como pino do Buzzer.

const int BTState = 2;    // Define o Pino 2 como o pino de comunicação do Bluetooth.
//luzes do carro
const int luzFrente = 6; // Define o Pino 6 como o pino dos farois.
const int luzFrenteDireita = A4; // Define o pino A4 como o pino do Led que esta na frente direita.
const int luzFrenteEsquerda = A3; // Define o pino A3 como o pino do led que esta na frente esquerda.
const int luzAtrasDireita = A1; // Define o pino A1 como o pino do led que esta na traseira direita.
const int luzAtrasEsquerda = A2; // Define o Pino A2 como o pino do LED que esta na traseira esquerda.
const int luzVerde = A5; // Define o Pino A5 como o pino do LED do Pisca-Alerta.

// Variáveis Úteis
int state_rec;
int vSpeed = 200;   // Define velocidade padrão 0 < x < 255.
char state;

void setup() {
  // portas de entrada e saída.
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(BTState, INPUT);
  pinMode(luzFrente, OUTPUT);
  pinMode(luzFrenteDireita, OUTPUT);
  pinMode(luzFrenteEsquerda, OUTPUT);
  pinMode(luzAtrasDireita, OUTPUT);
  pinMode(luzAtrasEsquerda, OUTPUT);
  pinMode(luzVerde, OUTPUT);
  

  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
}

void loop() {
  // Para o carro quando a conexão com Bluetooth é perdida ou desconectada.
  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }

  // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //   Serial.println(vSpeed);
  }

  // Altera a velocidade de acordo com valores especificados.
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '1') {
    vSpeed = 10;
  }
  else if (state == '2') {
    vSpeed = 20;
  }
  else if (state == '3') {
    vSpeed = 30;
  }
  else if (state == '4') {
    vSpeed = 40;
  }
  else if (state == '5') {
    vSpeed = 50;
  }
  else if (state == '6') {
    vSpeed = 60;
  }
  else if (state == '7') {
    vSpeed = 70;
  }
  else if (state == '8') {
    vSpeed = 80;
  }
  else if (state == '9') {
    vSpeed = 90;
  }
  else if (state == 'q') {
    vSpeed = 100;
  }

  if (state != 'S') {
    Serial.print(state);
  }


  if (state == 'F') { // Frente. desliga todos os LEDs.
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
    digitalWrite(luzFrenteEsquerda, LOW);
    digitalWrite(luzAtrasEsquerda, LOW);
    digitalWrite(luzFrenteDireita, LOW);
    digitalWrite(luzAtrasDireita, LOW);
  }
  else if (state == 'B') { // carro se movimenta para trás. liga os LEDs traseiros.
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
    analogWrite(motorA2, vSpeed);
    digitalWrite(luzAtrasDireita, HIGH);
    digitalWrite(luzAtrasEsquerda, HIGH);
    digitalWrite(luzFrenteEsquerda, LOW);
    digitalWrite(luzFrenteDireita, LOW);
   
  }
 
  else if (state == 'L') {   // esquerda. liga os LEDs da esquerda e desliga os da direita.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
    digitalWrite(luzFrenteEsquerda, HIGH);
    digitalWrite(luzAtrasEsquerda, HIGH);
    digitalWrite(luzFrenteDireita, LOW);
    digitalWrite(luzAtrasDireita, LOW);
  }

  else if (state == 'R') {   // direita. liga os LEDs da direita e desliga os da esquerda.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
    digitalWrite(luzFrenteDireita, HIGH);
    digitalWrite(luzAtrasDireita, HIGH);
    digitalWrite(luzFrenteEsquerda,LOW);
    digitalWrite(luzAtrasEsquerda, LOW);
  }
    else if (state == 'G') {  // Frente Esquerda. liga os LEDs da esquerda e desliga os da direita.
    analogWrite(motorA1, 100); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);    
    analogWrite(motorB2, 0);
    digitalWrite(luzFrenteEsquerda, HIGH);
    digitalWrite(luzAtrasEsquerda, HIGH);
    digitalWrite(luzFrenteDireita, LOW);
    digitalWrite(luzAtrasDireita, LOW);
  }

 
    else if (state == 'I') {   // Frente Direita. liga os LEDs da direita e desliga os da esquerda.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 100);      
    analogWrite(motorB2, 0);
    digitalWrite(luzFrenteDireita, HIGH);
    digitalWrite(luzAtrasDireita, HIGH);
    digitalWrite(luzFrenteEsquerda,LOW);
    digitalWrite(luzAtrasEsquerda, LOW);
  }

   else if (state == 'H') {  // Trás Esquerda. liga os LEDs trazeiros e o LED frontal Esquerdo.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 0); 
    analogWrite(motorB2, vSpeed);
    digitalWrite(luzFrenteEsquerda, HIGH);
    digitalWrite(luzAtrasEsquerda, HIGH);
    digitalWrite(luzAtrasDireita, HIGH);
    digitalWrite(luzFrenteDireita, LOW);
  }
  
  else if (state == 'J') {  // Trás Direital; liga os Led trazeiros e o da Led frontal direito.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0);   
    analogWrite(motorB2, 100);
    digitalWrite(luzFrenteDireita, HIGH);
    digitalWrite(luzAtrasDireita, HIGH);
    digitalWrite(luzAtrasEsquerda, HIGH);
    digitalWrite(luzFrenteEsquerda,LOW);
  }


  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }


  else if (state == 'V') { // aciona a buzina.
    tone(buzzer, 1000);
    state = 'n';
  }
  else if (state == 'v') {
    noTone(buzzer);
  }
  else if (state == 'W') { // Aciona os farois brancos frontais.
    digitalWrite(luzFrente, HIGH);
  }
  else if (state == 'w') { // Desliga os farois.
    digitalWrite(luzFrente, LOW);
  }

  else if (state == 'U') { // Aciona as luzes trazeiras .
    digitalWrite(luzAtrasDireita, HIGH);
    digitalWrite(luzAtrasEsquerda, HIGH);
  }
  else if (state == 'u') { // Ativa o Pisca-Alerta do carro.
    digitalWrite(luzAtrasDireita, LOW);
    digitalWrite(luzAtrasEsquerda, LOW);
  }
  else if (state == 'X') { // Desativa o Pisca-Alerta.
    digitalWrite(luzVerde, HIGH);
    delay(500);
    digitalWrite(luzVerde, LOW);
    delay(500);
  }

}
