/*******************************************************************************************************
------------------------------------Autor : Bruno Henrique D. Macedo---------------------------------
------------------------------------date : 13/04/2024------------------------------------------------
------------------------------------função do programa: Leitura de Termopar tipo K com MAX6675
*******************************************************************************************************/

#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

const int SO = 2;         // MISO - Master Input, Slave Output - Para MAX6675
const int SCLK = 3;       // SCLK - Serial Clock line - Para MAX6675
const int CS1 = A3;       // CS1 - Chip Select 1 - Para MAX6675
const int CS2 = A2;       // CS2 - Chip Select 2 - Para MAX6675
const int chipSelect = 10;// CS do cartão de memória
double sensor1 = 0;       // Variável para o sensor 1
double sensor2 = 0;       // Variável para o sensor 2

// MOSI - pin 11 no Arduino
// MISO - pin 12 no Arduino
// CLK - pin 13 no Arduino
// CS -  pin 10 no Arduino

// Declaração dos pinos do LCD - RS, E, D4, D5, D6, D7, D8,
LiquidCrystal lcd(9, 8, 4, 5, 6, 7);

// Declara dataFile como arquivo para salvar no SD
File dataFile;

// Gera um simbolo de graus
uint8_t degree[8]  = {140, 146, 146, 140, 128, 128, 128, 128};

// Protótipo de funções
byte SPIRead(void);
double readThermocouple(int ChipSelect);
void storeSD();

void setup() {
  Serial.begin(9600);
  // Declaração do modo como as portas irão operar
  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(SO, INPUT);
  digitalWrite(CS1, HIGH);
  digitalWrite(CS2, HIGH);

  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(1000);

  // Confere se o cartão está presente e operante
  if (!SD.begin(chipSelect)) {
    lcd.setCursor(0, 0);
    lcd.print("Falha no cartao ");
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Cartao OK       ");
  delay(500);
}

void loop() {
  lcd.clear();                        // Limpa o display

  // Linha 0, coluna 0
  lcd.setCursor(0, 0);
  lcd.print("Sensor1: ");
  sensor1 = readThermocouple(CS1);
  lcd.print(sensor1, 1);
  lcd.write((byte)0);
  lcd.print("C");

  // Linha 1, coluna 0
  lcd.setCursor(0, 1);
  lcd.print("Sensor2: ");
  sensor2 = readThermocouple(CS2);
  lcd.print(sensor2, 1);
  lcd.write((byte)0);
  lcd.print("C");

  storeSD();        // Função que faz o armazenamento das leituras no SD
  delay(10000);     // Aguarda 10 Segundos para uma nova leitura e armazenamento no cartão
}

/**************************************************************************************/
// Função para armazenamento dos dados de leitura feitos anteriormente
/**************************************************************************************/
void storeSD() {
  // Formata os dados para serem salvos no Cartão SD a cada 1 segundo
  String dataString = "";               // Declara uma string para salvar os dados no SD
  dataString += "Sensor1: ";
  dataString += String(sensor1);       // Valor da leitura do sensor 1
  dataString += " °C ";
  dataString += "Sensor2: ";
  dataString += String(sensor2);       // Valor da leitura do sensor 2
  dataString += " °C";

  // Abre o arquivo, escreve e o fecha novamente
  dataFile = SD.open("datalog.txt", FILE_WRITE);

  // Se o arquivo esta presente, escreve no mesmo
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  // Se o arquivo não abrir, indica no display
  else {
    lcd.setCursor(0, 0);
    lcd.print("Falha ao abrir  ");
    lcd.setCursor(0, 1);
    lcd.print("o arquivo no SD ");
  }
}

/**************************************************************************************/
// Função para leitura dos dados de temperatura provindos do MAX6675
/**************************************************************************************/
double readThermocouple(int ChipSelect) {
  uint16_t v;          // Declara variável de 16 bits - Tamanho ideal para o dado entregue pelo MAX

  digitalWrite(ChipSelect, LOW);
  _delay_ms(1);
  v = SPIRead();       // Leitura da parte alta - Primeiros 8 bits de dados
  v <<= 8;             // Desloca 8 posições para a esquerda
  v |= SPIRead();      // Faz leitura da parte baixo e armazena nos 8 primeiros bits atravez de uma OR
  digitalWrite(ChipSelect, HIGH);

  // Confere o bit 2 para termopar acoplado ou não
  if (v & 0x4) {
    return NAN;
  }
  v >>= 3;          // Descarta os 3 primeiros bits, onde apenas o bit 2 carrega o status e lê do bit 3 ao 14
  return v * 0.25;  // Multiplica pela resolução do MAX
}

/**************************************************************************************/
// Função que implementa um "SPI" via Software para leitura dos dados no MAX6675
/**************************************************************************************/
byte SPIRead(void) {
  int i;
  byte d = 0;

  // Laço FOR para apanhar 8 bits de cada vez
  for (i = 7; i >= 0; i--)    
  {
    digitalWrite(SCLK, LOW);  // Borda de descida do clock - Falling Edge
    _delay_ms(1);             // Aguarda 1ms
    if (digitalRead(SO)) {    // Faz a leitura do pino de dados de saída do MAX
      d |= (1 << i);          // Armazena os bits lidos, 0 ou 1, na variável e desloca de acordo com o indice para
    }                         // preencher todo o byte de dados
    digitalWrite(SCLK, HIGH); // Borda de subida do clock - Rising Edge
    _delay_ms(1);             // Aguarda 1ms
  }
  return d;                   // Retirna o byte de leitura dos dados lidos do MAX
}