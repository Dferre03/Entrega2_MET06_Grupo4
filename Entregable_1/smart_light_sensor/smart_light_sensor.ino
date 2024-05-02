//Mediante sensor de luz podremos adaptar la intensidad del LED

#include <Wire.h>
#include <BH1750.h>

const int ledPin = 2;      // Pin del LED
int intensity = 0;         // Nivel de intensidad del LED (0-255)

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  
  // Initialize the I2C bus
  Wire.begin();

  lightMeter.begin();
  Serial.println(F("BH1750 Test"));

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Leer la intensidad de luz
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  // Ajustar la intensidad del LED en función de la luz leída
  if (lux < 100) {
    intensity = 255;  // Máxima intensidad si hay poca luz
  } else if (lux >= 100 && lux < 500) {
    intensity = 192;  // Segundo nivel de intensidad
  } else if (lux >= 500 && lux < 1000) {
    intensity = 128;  // Tercer nivel de intensidad
  } else if (lux >= 1000 && lux < 2000){
    intensity = 64;   // Mínima intensidad si hay luz
  }else{
    intensity = 0;   // Vuelta al nivel 0 de instensidad si hay muchas luz
  }

  analogWrite(ledPin, intensity);

  delay(1000); // Esperar un segundo antes de realizar otra lectura
}
