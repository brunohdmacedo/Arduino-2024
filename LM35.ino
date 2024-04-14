/*******************************************************************************************************
------------------------------------Autor : Bruno Henrique D. Macedo---------------------------------
------------------------------------date : 13/04/2024------------------------------------------------
------------------------------------função do programa: verificar a temperatura de um lm 35
*******************************************************************************************************/
 
#define pin_lm35 A0 //Pino o qual o sensor está conectado
 
void setup() {
Serial.begin(9600); // Inicia a comunicação com
pinMode(pin_lm35, INPUT); // Define o sensor como uma entrada de sinal
}
 
void loop() {
float valor_analog_lm35 = float(analogRead(pin_lm35)); // Obtém o valor analógico que varia de 0 a 1023
float tensao = (valor_analog_lm35 * 5) / 1023; // Vamos converter esse valor para tensão elétrica
float temperatura = tensao / 0.010; // dividimos a tensão por 0.010 que representa os 10 mV
 
Serial.print("A temperatura eh ");
Serial.println(temperatura); // Mostra na serial a temperatura do sensor
 
delay(1000); // aguarda 1 segundo
}