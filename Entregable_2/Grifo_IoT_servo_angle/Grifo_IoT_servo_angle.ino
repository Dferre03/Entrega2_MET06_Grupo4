//Regular grifo 3 estados + feedback LED

#include <Servo.h>

#define PULSADOR_PIN 16
#define PULSADOR_PIN_EMERGENCIA 14
#define SERVO_PIN 12
#define LED_PIN 2 // Pin del LED para el feedback del caudal

Servo miServo;  // Creamos un objeto Servo
bool pulsador_previo = HIGH; // Estado previo del pulsador
bool pulsador_previo_emergencia = HIGH; // Estado previo del pulsador
int contador_pulsaciones = 0; // Contador de pulsaciones
int intensity = 0; // Nivel de intensidad del LED (0-255)

void setup() {
  miServo.attach(SERVO_PIN,800,2500); // define el pin del servo y los milisegundo del señal de control PWM de 0º (800ms) y los de 180º (2500ms)
  pinMode(PULSADOR_PIN, INPUT_PULLUP); // Habilita la resistencia pull-up interna
  miServo.attach(SERVO_PIN);  // Adjuntamos el servo al pin 12
  miServo.write(0); // Coloca el servo en posición inicial
  pinMode(LED_PIN, OUTPUT); // Establece el pin del LED como salida
}

void loop() {
  bool pulsador_actual = digitalRead(PULSADOR_PIN); // Lee el estado actual del pulsador

  bool pulsador_emergencia = digitalRead(PULSADOR_PIN_EMERGENCIA);

  if (pulsador_emergencia == LOW && pulsador_previo_emergencia == HIGH) {

      miServo.write(0);  // Gira el servo en otra dirección (140 grados)
      delay(50);         // Espera un segundo
      contador_pulsaciones = 0; // Reiniciar el contador de pulsaciones

    } // Si se detecta un cambio en el estado del pulsador
  
  if (pulsador_actual == LOW && pulsador_previo == HIGH) { // Si se detecta un cambio en el estado del pulsador
    contador_pulsaciones++; // Incrementar el contador de pulsaciones
    
    if (contador_pulsaciones == 1) { // Primer pulso
      // Movimiento del servo para el primer pulso
      miServo.write(90);  // Gira el servo en una dirección (135 grados)
      delay(50);         // Espera un segundo
    } else if (contador_pulsaciones == 2) { // Segundo pulso
      // Movimiento del servo para el segundo pulso
      miServo.write(180);  // Gira el servo en una dirección diferente (120 grados)
      delay(50);         // Espera un segundo

    } else if (contador_pulsaciones == 3) { // Tercer pulso
      // Movimiento del servo para el tercer pulso
      miServo.write(0);  // Gira el servo en otra dirección (140 grados)
      delay(50);         // Espera un segundo
      contador_pulsaciones = 0; // Reiniciar el contador de pulsaciones
    }
  }
  
  // Control del LED para el feedback del caudal
  
  if (contador_pulsaciones == 0) {     
    // Si el contador de pulsaciones es 0, el caudal está cerrado
    analogWrite(LED_PIN, 0);
     // Apaga el LED  
     } else {     
      // Si el contador de pulsaciones es diferente de 0, el caudal está abierto
      // La intensidad del LED aumenta con el número de pulsaciones (feedback de frecuencia)
      analogWrite(LED_PIN, map(contador_pulsaciones, 0, 3, 0, 255)); // Mapea el contador de pulsaciones al rango de intensidad del LED 
      }



  
  pulsador_previo = pulsador_actual; // Actualiza el estado previo del pulsador
  pulsador_previo_emergencia = pulsador_emergencia;
}
