/*******************************************************************************************************
------------------------------------Autor : Bruno Henrique D. Macedo---------------------------------
------------------------------------date : 13/04/2024------------------------------------------------
------------------------------------função do programa: Sensor de Temperatura NTC 10K
*******************************************************************************************************/

#include <Thermistor.h> //INCLUSÃO DA BIBLIOTECA

Thermistor temp(2); //VARIÁVEL DO TIPO THERMISTOR, INDICANDO O PINO ANALÓGICO (A2) EM QUE O SENSOR ESTÁ CONECTADO
void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
void loop() {
  int temperature = temp.getTemp(); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(temperature); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  Serial.println("*C"); //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(1000); //INTERVALO DE 1 SEGUNDO
}