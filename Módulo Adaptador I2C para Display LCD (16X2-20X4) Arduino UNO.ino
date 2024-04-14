#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES
 
void setup(){
 lcd.begin (16,2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
 lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)
}
 
void loop(){
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("       A        "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("MASTERWALKERSHOP"); //IMPRIME O TEXTO NO DISPLAY LCD
  delay(2000); //INTERVALO DE 2 SEGUNDOS
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("  SE PREOCUPA   "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("   COM O SEU    "); //IMPRIME O TEXTO NO DISPLAY LCD
  delay(2000); //INTERVALO DE 2 SEGUNDOS
  lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("                "); //SEQUÊNCIA DE ESPAÇOS
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("  APRENDIZADO!  "); //IMPRIME O TEXTO NO DISPLAY LCD
  delay(2000); //INTERVALO DE 2 SEGUNDOS
}