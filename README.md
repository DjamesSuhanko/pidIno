# pidIno
Just a PID lib for Arduino
"Eu poderia estar roubando, eu poderia estar matando, mas estou aqui: Pidino".

O arquivo contém um arquivo .cpp e um arquivo .h dentro de um diretório chamado pidino.

Descomprima o arquivo dentro do diretório libraries da sua IDE do Arduino, depois basta importá-lo em um novo projeto.

Um exemplo de utilização:

#include <pidino.h>

#define MOTOR1_P1 6
#define MOTOR1_P2 5
#define Kp 30.0
#define Ki  0.0
#define Kd  0.0
#define SETPOINT 68.90

pidino pid(Kp,Ki,Kd,SETPOINT);

void doPid(float fromSensor){
  bool stat = pid.calculate(fromSensor,SETPOINT); 
  if (!stat){
    return;
  }
  float pidVal = pid.getPid();
  int pidMap = pidVal > -1 ? pidVal + SETPOINT : (pidVal * -1) + SETPOINT; 
  int speedMap = constrain(pidMap,80,190);
  motors.balance(pidVal,speedMap);

  Serial.print("PID: ");
  Serial.print(pidVal);
  Serial.print(" Source: ");
  Serial.print(fromSensor);
  Serial.print(" Correction: ");
  Serial.print(fromSensor-pidVal);
  Serial.print(" PWM: ");
  Serial.print(speedMap);
  Serial.println(" ");
}

Em setup(), defini-se o intervalo entre as leituras:

pid.setTimerRuler(60);

