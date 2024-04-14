
// Inclusão das Bibliotecas
#include <DHT.h>
#include <Wire.h>

// Definição de pinos dos módulos
#define DHTPIN A2     // pino utilizado para sensor
#define DHTTYPE DHT11 // Tipo de sensor: DHT11

// Cria variável para sensor DHT
DHT dht(DHTPIN, DHTTYPE);

byte umidade;
float temperatura;

String valString = "<";

void setup() {

  Serial.begin(115200);

  Wire.begin();

  // Inicializa sensor DHT
  dht.begin();

}

void loop() {

  umidade = dht.readHumidity();
  temperatura = dht.readTemperature();

  valString.concat(umidade);
  valString.concat(";");
  valString.concat(temperatura);
  valString.concat(">");
  
  Serial.print(valString);

  valString = "<";
  delay(10000);

}
