#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>

// Definições para o LCD com PCF8574T
#define I2C_ADDR_LCD 0x27 // Endereço do display LCD

// Definições para o sensor de corrente ACS712
#define ACS712_PIN A0

// Definições para o sensor de temperatura LM35
#define LM35_PIN A1

// Definições para o termopar tipo K
#define THERMOCOUPLE_PIN A2

// Definições para o relé
#define RELAY_PIN 4

// Variáveis para o controle de temperatura
double setpoint = 4.0;  // Temperatura desejada
double histerese = 1.0; // Histerese de controle
double input, output, temperature;
PID pid(&input, &output, &setpoint, 1, 1, 1, DIRECT); // Parâmetros do PID

// Configuração do LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  
  lcd.begin(16, 2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
  lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)

  // Inicialização do sensor de corrente
  pinMode(ACS712_PIN, INPUT);

  // Inicialização do sensor de temperatura LM35
  pinMode(LM35_PIN, INPUT);

  // Inicialização do termopar tipo K
  pinMode(THERMOCOUPLE_PIN, INPUT);

  // Inicialização do relé
  pinMode(RELAY_PIN, OUTPUT);

  // Inicialização do PID
  pid.SetMode(AUTOMATIC);
}

void loop() {
  // Leitura dos sensores
  double current = readCurrent();
  double temperatureLM35 = readTemperatureLM35();
  double temperatureThermocouple = readTemperatureThermocouple();

  // Atualização do PID
  input = temperatureThermocouple;
  pid.Compute();

  // Controle do relé
  if (output > 0) {
    digitalWrite(RELAY_PIN, HIGH); // Liga o relé
  } else {
    digitalWrite(RELAY_PIN, LOW); // Desliga o relé
  }

  // Exibir informações no LCD
  lcd.clear();
  lcd.setCursor(0, 0); //SETA A POSIÇÃO DO CURSOR
  lcd.print(" BILIVOLTs 2.0 "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("----------------"); //SEQUÊNCIA DE ESPAÇOS
  delay(2000); //INTERVALO DE 2 SEGUNDOS
  lcd.setCursor(0, 0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("TEMP IN: "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print(temperatureThermocouple);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Corrente: ");
  lcd.print(current);
  lcd.print(" A");
  delay(2000); //INTERVALO DE 2 SEGUNDOS
  lcd.setCursor(0, 0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("TEMP FORA: "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print(temperatureLM35);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Corrente: ");
  lcd.print(current);
  lcd.print(" A");
  delay(2000); //INTERVALO DE 2 SEGUNDOS
  lcd.setCursor(0, 0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("                "); //SEQUÊNCIA DE ESPAÇOS
  lcd.setCursor(0, 0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("   GRUPO BFR!  "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(0, 1);
  lcd.print("  2024  "); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("                "); //SEQUÊNCIA DE ESPAÇOS
  delay(3000); // Aguarda 1 segundo antes de atualizar o LCD

  // Envio dos dados pela porta serial
  Serial.print("Temperatura Thermocouple: ");
  Serial.print(temperatureThermocouple);
  Serial.print(" C, Corrente: ");
  Serial.print(current);
  Serial.print(" A, Temperatura LM35: ");
  Serial.print(temperatureLM35);
  Serial.println(" C");
  delay(2000); // Aguarda 2 segundos antes de enviar o próximo conjunto de dados

}

// Função para ler a corrente do sensor ACS712
double readCurrent() {
  int sensorValue = analogRead(ACS712_PIN);
  double current = (sensorValue - 512) / 102.3; // Ajuste para converter a leitura em amperes
  return current;
}

// Função para ler a temperatura do sensor LM35
double readTemperatureLM35() {
  int sensorValue = analogRead(LM35_PIN);
  double temperature = (sensorValue * 5.0) / 1023.0 * 100.0; // Ajuste para converter a leitura em graus Celsius
  return temperature;
}

// Função para ler a temperatura do termopar tipo K
double readTemperatureThermocouple() {
  int sensorValue = analogRead(THERMOCOUPLE_PIN);
  
  // Convertendo a leitura analógica para tensão (assumindo que o resistor é de 10kΩ)
  double voltage = sensorValue * (5.0 / 1023.0); // Tensão máxima é de 5V
  
  // Supondo uma relação linear entre tensão e temperatura (para fins de exemplo)
  // Você precisará calibrar esta relação com base nas características reais do seu resistor
  // Esta é apenas uma aproximação simplificada
  double temperature = map(voltage, 0, 5, 25, 200); // Mapeia a tensão para um intervalo aproximado de temperatura
  
  return temperature;
}
