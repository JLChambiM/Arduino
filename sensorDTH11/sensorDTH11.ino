#include <LiquidCrystal.h>
#include <DHT.h>

// Definición de pines LCD
const int RS = 12;
const int E = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

// Configuración DHT11
const int DHT_PIN = 8;
#define DHT_TYPE DHT11

// Intervalo de actualización (ms)
const int UPDATE_INTERVAL = 2000;
unsigned long lastUpdate = 0;

// Inicialización de objetos
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // Inicialización del LCD
  lcd.begin(16, 2);
  
  // Inicialización del puerto serie
  Serial.begin(9600);
  
  // Inicialización del sensor DHT
  dht.begin();
  
  // Mensaje inicial
  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Actualizar lecturas cada UPDATE_INTERVAL millisegundos
  if (millis() - lastUpdate >= UPDATE_INTERVAL) {
    // Lectura de sensores
    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();
    float tempF = dht.readTemperature(true);

    // Verificar si las lecturas son válidas
    if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
      Serial.println("Error al leer el sensor DHT11!");
      lcd.clear();
      lcd.print("Error sensor!");
      lastUpdate = millis();
      return;
    }

    // Mostrar datos en el Serial Monitor
    Serial.print("Humedad Relativa: ");
    Serial.print(humidity);
    Serial.print("% / Temperatura: ");
    Serial.print(tempC);
    Serial.print("ºC / ");
    Serial.print(tempF);
    Serial.println("ºF");

    // Mostrar datos en el LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humedad: ");
    lcd.print(humidity, 1);
    lcd.print("%");
    
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(tempC, 1);
    lcd.write(223);  // Símbolo de grado
    lcd.print("C");

    lastUpdate = millis();
  }
}