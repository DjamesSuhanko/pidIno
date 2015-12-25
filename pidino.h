#include "Arduino.h"
#ifndef PIDBOT_H
#define PIDBOT_H
# define PONLY 1
#define PI         2
#define PID       3

class pidIno
{
    public:
       explicit pidIno(float _Kp, float _Ki, float _Kd, float _setPoint);
        /*! calculate: recebe o valor adquirido pelo usuário, assim pode vir tanto de pino digital como analógico ou remoto, etc.
        * esse método devolve o resultado diretamente, mas os cálculos são feitos pelos métodos chamados dentro dele, ele
        * existe apenas para que seja uma chamada pública. Os métodos de cálculo são privados, portanto chamados apenas
        * internamente.
        */
        bool calculate(float sample, float adjustment);
        float getPid(); //!Após retornar true, sabe-se que o novo valor está armazenado e pode ser lido dentro do intervalo de tempo determinado.
        virtual ~pidIno();

        /*! Permite reajustar o valor do setpoint. De qualquer modo, o setpoint precisa ser declarado ao instanciar essa classe.
        */
        void setSetPoint(float _setPoint);
        void setTimerRuler(int timeIntervalToCompute);
        void windup(float _min, float _max);

    protected:
    private:
        float timerRuler = 100; // interval to starts computing. starting over 100ms
        struct _pidVars{
            float Kd;
            float Ki;
            float Kp;
            //valores finais
            float P = 0;
            float I  = 0;
            float D = 0;
            //setpoint
            float setPoint;
        } pidVars;

        float dt             = 0;  //delta time
        float d              = 0; //derivativa
        float lastTime   = 0;
        float lastValue  = 0;
        float value        = 0;
        float e               = 0; //error
        float angle        = 0;
        float myPID      = 0;
        float minimal    = 0; //windup
        float maximum = 0; //windup

        void proporcional(float valFromSensor);
        void integral();
        void derivativa();

};

#endif // PIDBOT_H
