//Codigo que permite escoger mediante Monitor Serie entre regular la luz con pulsador o con sensor de luz

#include <Wire.h>
#include <BH1750.h>

const int buttonPin = 16; // Pin del pulsador
const int ledPin = 2;    // Pin del LED

int buttonState = 0;     // Estado actual del pulsador
int intensity = 0;       // Nivel de intensidad del LED (0-255)

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize the I2C bus
  Wire.begin();
  lightMeter.begin();
}

void loop() {
  Serial.println("Seleccione una opción:");
  Serial.println("1. Controlar LED con botón.");
  Serial.println("2. Controlar LED con sensor de luz.");
  
  while (!Serial.available()) {} // Espera a que el usuario ingrese datos

  char option = Serial.read();

  switch (option) {
    case '1':
      controlConBoton();
      break;
    case '2':
      controlConSensor();
      break;
    default:
      Serial.println("Opción no válida. Por favor, seleccione 1 o 2.");
      break;
  }
}

void controlConBoton() {
  while (true) {
    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
      // Incrementa la intensidad del LED
      intensity += 64; // 255/4 = 64 (4 niveles de intensidad)

      if (intensity > 256) {
        intensity = 0; // Vuelve al nivel de intensidad 0 si supera 255
      }

      analogWrite(ledPin, intensity);

      // Espera a que se suelte el botón antes de cambiar de intensidad nuevamente
      while (digitalRead(buttonPin) == HIGH) {
        delay(10);
      }
    }
    delay(100); // Pequeña pausa para liberar el procesador
  }
}

void controlConSensor() {
  while (true) {
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
    } else {
      intensity = 0;   // Vuelta al nivel 0 de intensidad si hay muchas luz
    }

    analogWrite(ledPin, intensity);

    delay(1000); // Esperar un segundo antes de realizar otra lectura
  }
}
