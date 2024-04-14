/*******************************************************************************************************
------------------------------------Autor : Bruno Henrique D. Macedo---------------------------------
------------------------------------date : 13/04/2024------------------------------------------------
------------------------------------função do programa: verificar a temperatura de um lm 35
*******************************************************************************************************/

#define ADCPIN A3                             	// Pino de leitura do sensor
float temperatura = 0;                        	// Variável para leitura e impressão na tela inicia com valor ZERO
 
void setup()
{
  analogReference(INTERNAL);                  	// Utiliza referência interna do UNO de 1,1Vcc
  Serial.begin(9600);                         	// Inicializa a comunicação serial
}
 
void loop()
{
  temperatura = analogAvg(ADCPIN);            	// Leitura do sensor pela função
  temperatura = temperatura * 1100 / (1024 * 10); // Conversão de volts para graus celsius
  Serial.print(temperatura);                	// Imprime a leitura no monitor serial
  Serial.print(" \xB0");                   	    // exibe simbolo de grau Celcius
  Serial.println("C"); 
  delay(1000);                                	//Espera 1 segundo para nova leitura
}
 
int analogAvg(int sensorPin){                 	// Função para amostragem do sensor
  int medidas = 0;
  int amostras = 20;
  for (int n = 0; n < amostras; n++){
    medidas += analogRead(sensorPin);
    delay(10);                                	// Melhorar as leituras analógicas
  }
  return medidas / amostras;                  	// Retorna a amostragem
}