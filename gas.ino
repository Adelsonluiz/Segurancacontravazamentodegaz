//sensor de gás inteligente
#include <LiquidCrystal.h> // incluindo a bliblioteca do lcd display 16x2
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte exau = 2;  //exaustor
byte azul = 3;  //led azul
byte verm = 5;  // led vermelho
byte buz = 6; //Buzzer
byte valv = 7; //Eletro Válvula

byte aux_a = 1;
byte aux_b = 0;//modo automatico

byte menu = 0;
byte set = 25;
int salto = 0;
int sbaixo = 0;
int valor = 0;//leitura do teclado R2R
int pot;//sensor de temperatura
byte Grau[8] = {B01100, B10010, B10010, B01100, B00000, B00000, B00000, B00000}; //º
void setup()
{

  lcd.begin(16, 2);
  pinMode(exau, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verm, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(valv, OUTPUT);

  lcd.createChar(1, Grau);

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Deteccao de gas ");
  delay(2000);
  lcd.clear();

  tela0(); //sensor
  tela1(); //

}

void loop()
{
  //////////////////////////
  valor = analogRead(A1);/// leitura do telcado R2R, 613 BT1, 511 BT2, 340 BT3
  Serial.print(valor);//////
  Serial.print(" ");//////// Monitor serial
  delay(250);///////////////
  ////////////////////////////

  pot = analogRead(A0);
  pot = map(pot, 0, 1023, 0, 101);

  cargas();

  if ( menu == 0)
  {
    tela0();
    aux_b = 0;//modo automatico
  }

  if (valor > 500 && valor < 520 && menu == 0)
  {
    aux_a =  1;
    menu = 1;
    tela2();
    aux_b = 1;//modo manual
    while (valor > 500 && valor < 520) {
      delay(500);
      valor = 0;
    }
  }
  if (valor > 600 && valor < 620 && menu == 1 && aux_a == 1)
  {
    aux_a = 2;
    tela3();
    aux_b = 1;//modo manual
    while (valor > 600 && valor < 620) {
      delay(500);
      valor = 0;
    }

  }
  if (valor > 600 && valor < 620 && menu == 1 && aux_a == 2)
  {
    aux_a = 3;
    tela4();
    aux_b = 1;//modo manual
    while (valor > 600 && valor < 620) {
      delay(500);
      valor = 0;
    }
  }
  if (valor > 330 && valor < 350 && menu == 1 && aux_a == 2)//bt1<
  {
    aux_a = 1;
    tela2();
    aux_b = 1;//modo manual
  }
  if (valor > 300 && valor < 350 && menu == 1 && aux_a == 3)
  {
    aux_a = 2;
    tela3();
    aux_b = 1;//modo manual

  }
  if (valor > 500 && valor < 520 && menu == 1 && aux_a == 1)
  {
    menu = 1;
    tela5();
    aux_b = 1;//modo manual
    while (valor > 500 && valor < 520) {
      delay(500);
      valor = 0;
    }
    tela2();
    aux_b = 1;//modo manual
  }
  if (valor > 500 && valor < 520 && menu == 1 && aux_a == 2)
  {
    aux_a = 1;
    menu = 1;
    tela6();
    tela2();
    aux_b = 1;//modo manual
    while (valor > 500 && valor < 520) {
      delay(150);
      valor = 0;
    }
  }
  if (valor > 500 && valor < 520 && menu == 1 && aux_a == 3)
  {
    aux_a = 1;
    menu = 0;
    tela7();
    aux_b = 1;//modo manual
    tela1();
    while (valor > 500 && valor < 520) {
      delay(50);
      valor = 0;
    }
  }

}


////////////////////////TELAS/////////////////////////////
void tela0()
{

  lcd.setCursor(0, 0);
  lcd.print("gas:");
  lcd.print(pot);
  lcd.print("%");
  lcd.print(" AUTO          ");
}
void tela1()
{
  lcd.setCursor(0, 1);
  lcd.print(" >MODO MANUAL<  ");
}
void tela2()
{
  lcd.setCursor(0, 0);
  lcd.print(">Fechar         ");
  lcd.setCursor(8, 0);
  lcd.print(" Abrir          ");
  lcd.setCursor(0, 1);
  lcd.print(" Voltar         ");
}
void tela3()
{
  lcd.setCursor(0, 0);
  lcd.print(" Fechar         ");
  lcd.setCursor(8, 0);
  lcd.print(">Abrir          ");
  lcd.setCursor(0, 1);
  lcd.print(" Voltar         ");
}
void tela4()
{
  lcd.setCursor(0, 0);
  lcd.print(" Fechar         ");
  lcd.setCursor(8, 0);
  lcd.print(" Abrir          ");
  lcd.setCursor(0, 1);
  lcd.print(">Voltar         ");

}
void tela5()
{
  cargas_v0();//fecha a valvula em modo manual
  lcd.setCursor(0, 0);//escrever na coluna 0 e na linha 0
  lcd.print("Valvula Fechada ");
  lcd.setCursor(0, 1);//escrever na coluna 0 e na linha 1
  lcd.print("Com Sucesso     ");
  delay(500);
  for (int i = 1; i <= 4; i++)
  {
    lcd.setCursor(10 + i, 1); //escrever na coluna 10 e na linha 1
    lcd.print(".");
    delay(500);
  }
}
void tela6()
{
  cargas_v1();//abre a valvula em modo manual
  lcd.setCursor(0, 0);//escrever na coluna 0 e na linha 0
  lcd.print("Valvula Aberta  ");
  lcd.setCursor(0, 1);//escrever na coluna 0 e na linha 1
  lcd.print("Com Sucesso     ");
  delay(500);
  for (int i = 1; i <= 4; i++)
  {
    lcd.setCursor(10 + i, 1); //escrever na coluna 10 e na linha 1
    lcd.print(".");
    delay(500);
  }
}
void tela7()
{
  lcd.setCursor(0, 0);//escrever na coluna 0 e na linha 0
  lcd.print("Voltando        ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(500);
  for (int i = 0; i <= 5; i++)
  {
    lcd.setCursor(9 + i, 0); //escrever na coluna 13 e na linha 1
    lcd.print("<");
    delay(500);
  }
}
/////////////////// LEDS ///////////////////////////////////////////
void cargas()//modo automatico
{
  if (pot >= 0 && pot < 2 && aux_b == 0)
  {
    digitalWrite(azul, 1);
    digitalWrite(exau, 0);
    digitalWrite(verm, 0);
    digitalWrite(buz, 0);
    digitalWrite(valv, 1);
  }

  if (pot >= 2  && aux_b == 0)
  {
    digitalWrite(azul, 0);
    digitalWrite(exau, 1);
    digitalWrite(verm, 1);
    digitalWrite(buz, 1);
    digitalWrite(valv, 0);
  }
}
/////////////////// LEDS ///////////////////////////////////////////
void cargas_v0()//modo manual - fechar valvula
{
  digitalWrite(azul, 0);
  digitalWrite(exau, 0);
  digitalWrite(verm, 0);
  digitalWrite(buz, 0);
  digitalWrite(valv, 0);
}
/////////////////// LEDS ///////////////////////////////////////////
void cargas_v1()//modo manual - abrir valvula
{
  digitalWrite(azul, 0);
  digitalWrite(exau, 0);
  digitalWrite(verm, 0);
  digitalWrite(buz, 0);
  digitalWrite(valv, 1);
}
