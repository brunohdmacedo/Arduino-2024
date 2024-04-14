/*******************************************************************************************************
------------------------------------Autor : Bruno Henrique D. Macedo---------------------------------
------------------------------------date : 13/04/2024------------------------------------------------
------------------------------------função do programa: Termômetro Digital Display I2C 20x4 + Kit Termopar Tipo K.
*******************************************************************************************************/



// Carrega as bibliotecas necessárias.
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "max6675.h"

int pinSO  = 8; // Atribui o pino 8 como SO
int pinCS  = 9; // Atribui o pino 9 como CS
int pinSCK = 10; // Atribui o pino 10 como SCK

// Cria uma instância da biblioteca MAX6675.
MAX6675 termoclanek(pinSCK, pinCS, pinSO);

// Define o endereço utilizado pelo Adaptador I2C.
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
//Inicializa o LCD e o backlight.
lcd.init();
lcd.backlight();
}

void loop() {
// Lê a temperatura to termopar em ºC
float teplotaC = termoclanek.readCelsius();

// Imprime os valores correspondentes à temperatura.
lcd.setCursor(0, 0);
lcd.print("Temp. em Celsius:");
lcd.setCursor(14, 1);
lcd.print(teplotaC);
lcd.setCursor(0, 2);
lcd.print("Temp. em Fahrenheit:");
lcd.setCursor(14, 3);
lcd.print(termoclanek.readFahrenheit());  // Converte para ºF.

// Delay (tempo) para a próxima leitura.
delay(1000);
}