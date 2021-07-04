#include <DHT.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

float temp_DHT11, humedad_DHT11;

void setup() {
  Serial.begin(9600);
  Serial.println("INICIANDO");
  dht.begin();
  delay(100);
}

void loop() {
  temp_DHT11 = dht.readTemperature();
  humedad_DHT11 = dht.readHumidity();
  
  Serial.print("Temperature DHT11 = ");
  Serial.print(temp_DHT11);
  Serial.println("ºC");
  Serial.print("Humidity DHT11 = ");
  Serial.print(humedad_DHT11);
  Serial.println(" %");
  Serial.println("--------------------------------");
  delay(1000);
}
