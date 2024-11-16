#include <N64Controller.h>

N64Controller n64Controller(2);  // Pin de datos al pin 2

// Definición de pines de salida para el GAME I/O del Apple II
const int pinPwmX = 5;  // Salida digital para el eje X
const int pinPwmY = 6;  // Salida digital para el eje Y
const int pinButtonA = 7;  // Botón 0 (A)
const int pinButtonZ = 8;  // Botón 1 (Z)

// Definir la zona muerta para evitar pequeños movimientos alrededor del centro
int deadZone = 15;  // Ajusta según sea necesario
int ajusteX = 0;   // Ajuste fino para corregir el centro en X
int ajusteY = 0;    // Ajuste fino para corregir el centro en Y

void setup() {
  Serial.begin(9600);
  n64Controller.begin();

  // Cambiar la frecuencia del Timer1 (pines 9 y 10)
  TCCR1B = TCCR1B & B11111000 | B00000001;  // Establecer la frecuencia PWM a 31.37 kHz

  pinMode(pinPwmX, OUTPUT);
  pinMode(pinPwmY, OUTPUT);
  pinMode(pinButtonA, OUTPUT);
  pinMode(pinButtonZ, OUTPUT);
}

void loop() {
  // Actualiza el estado del mando N64
  n64Controller.update();
  
  // Leer la posición del stick analógico
  int x = n64Controller.axis_x(); // Eje X (-128 a 128)
  int y = n64Controller.axis_y(); // Eje Y (-128 a 128)

  // Aplicar ajustes para corregir el centro
  x += ajusteX;
  y += ajusteY;

  // Definir los valores extremos para el eje X (Izquierda, Centro, Derecha)
  int pwmX = 127;  // Valor neutral en el centro
  if (x < -deadZone) {
    pwmX = 255;  // Izquierda
  } else if (x > deadZone) {
    pwmX = 0;  // Derecha
  }

  // Definir los valores extremos para el eje Y (Arriba, Centro, Abajo)
  int pwmY = 127;  // Valor neutral en el centro
  if (y < -deadZone) {
    pwmY = 0;  // Arriba
  } else if (y > deadZone) {
    pwmY = 255;  // Abajo
  }

  // Enviar las señales digitales a los pines correspondientes
  analogWrite(pinPwmX, pwmX);  // Movimiento en el eje X (digital)
  analogWrite(pinPwmY, pwmY);  // Movimiento en el eje Y (digital)

  // Leer los botones del mando N64
  bool buttonA = n64Controller.A();
  bool buttonZ = n64Controller.Z();

  // Enviar el estado de los botones al Apple II
  digitalWrite(pinButtonA, buttonA ? LOW : HIGH);  // Botón A
  digitalWrite(pinButtonZ, buttonZ ? LOW : HIGH);  // Botón Z

  // Imprimir los valores en el monitor serie para depuración
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" | PWM X: ");
  Serial.print(pwmX);
  Serial.print(" PWM Y: ");
  Serial.println(pwmY);

  //delay(50);  // Retardo para estabilidad
}

