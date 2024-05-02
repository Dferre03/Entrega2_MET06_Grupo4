//Mediante pulsador regulamos la luz con modos de intensidad

const int buttonPin = 16; // Pin del pulsador
const int ledPin = 2;    // Pin del LED

int buttonState = 0;     // Estado actual del pulsador
int intensity = 0;       // Nivel de intensidad del LED (0-255)

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
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
}
