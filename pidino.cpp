#include "pidIno.h"

//inicialmente um bom valor eh 1.0, 0, 0, valorPadraoDesejado
pidIno::pidIno(float _Kp, float _Ki, float _Kd, float _setPoint)
{
    this->pidVars.Kp         = _Kp;
    this->pidVars.Ki          = _Ki;
    this->pidVars.Kd         = _Kd;
    this->pidVars.setPoint = _setPoint;
}

//Apenas chame esse metodo com amostra do sensor e valor desejado para a correcao
bool pidIno::calculate(float sample, float adjustment)
{
    this->dt += (millis() - lastTime);
    lastTime = millis();
    if (this->dt >= timerRuler){
        this->dt = this->dt/1000.0;

        this->proporcional(sample);
        this->integral();
        this->derivativa();

        this->myPID = this->pidVars.P + this->pidVars.I + this->pidVars.D;

        this->dt = 0;
       // if (this->maximum > 0){
        //    this->myPID = this->myPID < this->maximum ? this->myPID : this->maximum;
        //}
        //return this->myPID; // + adjustment; //talvez  adjustment nao deva existir
        return true;
    }
    return false;
}

void pidIno::derivativa()
{
    this->d = this->lastValue - this->value; // derivativa. fica mais parecido com a formula assim.
    this->pidVars.D = this->pidVars.Kd * (d / dt) * e;
    this->lastValue = this->value;
}

float pidIno::getPid()
{
    return this->myPID;
}

void pidIno::integral()
{
    this->pidVars.I += (this->pidVars.Ki * e) * dt;
    Serial.print("Integral: ");
    Serial.println(this->pidVars.I);
}

void pidIno::proporcional(float valFromSensor)
{
    e = this->pidVars.setPoint - valFromSensor;
    this->pidVars.P = this->pidVars.Kp * e ;
    Serial.print("P: ");
    Serial.println(this->pidVars.P);
}

void pidIno::setSetPoint(float _setPoint)
{
    this->pidVars.setPoint = _setPoint;
}

void pidIno::setTimerRuler(int timeIntervalToCompute)
{
    this->timerRuler = timeIntervalToCompute;
}

//TODO: tratar o minimo, analisar sinal
void pidIno::windup(float _min, float _max)
{
    this->minimal     = _min;
    this->maximum = _max;
}

pidIno::~pidIno()
{

}
