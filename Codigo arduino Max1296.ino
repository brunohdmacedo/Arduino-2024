#include <SPI.h>  // Biblioteca para comunicação SPI
#include <MAX1296.h>  // Biblioteca para o ADC MAX1296

// Defina os pinos do Arduino Nano para comunicação SPI
#define MAX1296_CS 10  // Pino de seleção do chip do MAX1296
#define LM35_PIN A0    // Pino de entrada analógica conectado ao LM35

MAX1296 adc(MAX1296_CS);  // Criação de uma instância do objeto do ADC

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial
  adc.begin();         // Inicia o ADC
}

void loop() {
  // Realiza uma leitura no canal do ADC conectado ao LM35
  int adcValue = adc.readChannel(LM35_PIN);
  
  // Converte o valor do ADC para temperatura (assumindo LM35 de 10mV/°C)
  float temperature = adcValue * 0.1;

  // Exibe a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000);  // Aguarda 1 segundo antes da próxima leitura
}
