#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Configuração dos botões e do Buzzer
const int b1 = 2;
const int b2 = 3;
const int b3 = 4;
const int b4 = 5;
const int b5 = 6;
const int buzzer = 13;

// Variáveis
//5 segundos a mais para apresentar na aula
int tempoEstudo = 1505; // 25 minutos em segundos (1500)
int tempoDescanso = 305;  // 5 minutos em segundos (300)
int numRept = 2;
bool timersAtivo = false;
bool emEstudo = true;
bool fim = false;
bool repeticoes = false;

// Função para apagar a linha de uma coluna
void limparLinha(int linha){
  lcd.setCursor(0, linha); 
  lcd.print("                ");
  lcd.setCursor(0, linha);
}

// Função para o botão enviar apenas um sinal (tirando o bounce)
bool statusBotao(int pino){
  if (digitalRead(pino) == HIGH){
    delay(500);
    return true;
  }
  return false;
}
  
void setup(){
  // Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  
  // Define entrada e saída
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  
  lcd.setCursor(1, 0);
  lcd.print("Comecar Estudo");
  lcd.setCursor(1, 1);
  lcd.print("Pressione B1");  
}
 
void loop(){
 // Começa as configurações de tempo
 if (statusBotao(b1) || fim == true){
   abrirMenu();
 } 
 // Começa as configurações de repetições
 if (repeticoes == true){
   numRepeticoes();
 }  
 // Começa os timers de estudo e descanso
 if (timersAtivo == true){
   executarTimers();
 }
}

void abrirMenu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Avisos de");
  lcd.setCursor(0, 1);
  lcd.print("Configuracao");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("B3 / B5 soma");
  lcd.setCursor(0, 1);
  lcd.print("Estudo/Descanso");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("B2 / B4 diminui");
  lcd.setCursor(0, 1);
  lcd.print("Estudo/Descanso");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("B1");
  lcd.setCursor(0, 1);
  lcd.print("Confirma");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estudo: ");
  lcd.setCursor(9, 0);
  lcd.print(tempoEstudo / 60);
  lcd.print(" min  ");
  lcd.setCursor(0, 1);
  lcd.print("Descanso: ");
  lcd.setCursor(9, 1);
  lcd.print(tempoDescanso / 60);
  lcd.print(" min  ");
  while (true){
    // Acrescimo ou decréscimo dos tempos
    if (statusBotao(b3)){
      tempoEstudo += 300; // +5 minutos
      lcd.setCursor(9, 0);
      lcd.print(tempoEstudo / 60);
      lcd.print(" min  ");
    }
    else if (statusBotao(b2) && tempoEstudo > 0){
      tempoEstudo -= 300; // -5 minutos
      lcd.setCursor(9, 0);
      lcd.print(tempoEstudo / 60);
      lcd.print(" min  ");
    }
    if (statusBotao(b4) && tempoDescanso > 0){
      tempoDescanso -= 60;// -1 minutos
      lcd.setCursor(9, 1);
      lcd.print(tempoDescanso / 60);
      lcd.print(" min  ");
    }
    else if (statusBotao(b5)){
      tempoDescanso += 60; // +1 minutos
      lcd.setCursor(9, 1);
      lcd.print(tempoDescanso / 60);
      lcd.print(" min  ");
    }
    if (statusBotao(b1)){ // Confirmas as configurações
       lcd.clear();
       lcd.print("Config. Salva!");
       delay(1000);
       lcd.clear();
       repeticoes = true; // Começará as configurações de repetições
       break;
     }
  }
}

void numRepeticoes(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("B3 soma");
  lcd.setCursor(0, 1);
  lcd.print("B4 diminui");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Repeticoes: ");
  lcd.setCursor(0, 1);
  lcd.print(numRept);
  lcd.print(" vezes  ");
  while (true){
   if (statusBotao(b3)){
     numRept += 1;
     limparLinha(1);
     lcd.setCursor(0, 1);
     lcd.print(numRept);
     lcd.print(" vezes  ");
   }
   else if (statusBotao(b4) && numRept > 1){
     numRept -= 1;
     lcd.setCursor(0, 1);
     lcd.print(numRept);
     lcd.print(" vezes  ");
   }
   if (statusBotao(b1)){
     lcd.clear();
     lcd.print("Config. Salva!");
     delay(1000);
     lcd.clear();
     timersAtivo = true; // Começara os timers
     break;
   }
  }
}

void executarTimers(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estudo: ");
  lcd.print(tempoEstudo /60);
  lcd.print(" min");
  lcd.setCursor(0, 1);
  lcd.print("Descanso: ");
  lcd.print(tempoDescanso / 60);
  lcd.print(" min  ");
  delay(1000);
  lcd.clear();
  int tempEs = tempoEstudo; // Armazena o tempo de Estudo
  int tempDes = tempoDescanso; // Armazena o tempo de Descanso
  for (int i = numRept; i > 0; i--){ // Fará as repetições em base da escolha
   while (tempoEstudo > 0){
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Estudo: ");  
     if (tempoEstudo > 0){
       limparLinha(1);
       lcd.setCursor(0, 1);
       lcd.print(tempoEstudo / 60);
       lcd.print(" min ");
       lcd.print(tempoEstudo % 60);
       lcd.print(" sec ");
     }
    delay(1000); // Atraso de 1 segundo
    tempoEstudo--; // Retirar 1 segundo
   }
   lcd.clear();
   lcd.print("Estudo acabou!");
   for (int i = 0; i < 5; i++) {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
   }
   lcd.clear();
   while (tempoDescanso > 0) {
    lcd.setCursor(0, 0);
    lcd.print("Descanso: ");
    if (tempoDescanso > 0) {
       limparLinha(1);
       lcd.setCursor(0, 1);
       lcd.print(tempoDescanso / 60);
       lcd.print(" min ");
       lcd.print(tempoDescanso % 60);
       lcd.print(" sec ");
     }
    delay(1000); // Atraso de 1 segundo
    tempoDescanso--; // Retirar 1 segundo
   }
   lcd.clear();
   lcd.print("Descanso acabou!");
   for (int i = 0; i < 5; i++) {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
   }
  // Retorna os valores
  tempoEstudo = tempEs; 
  tempoDescanso = tempDes;
  }
  lcd.clear();
  lcd.print("Completo!");
  delay(5000);
  repeticoes = false;
  timersAtivo = false;
  fim = true;
}
 
  
  
  
