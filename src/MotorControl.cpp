#include "MotorControl.h"

byte MotorControl::register_output;

MotorControl::MotorControl() {
   
}

MotorControl::MotorControl(byte motor)
{
    switch (motor) {
    case 1:
        motorA    = MOTOR1_A;
        motorB    = MOTOR1_B;
        speed_pin = MOTOR1_PWM;
        break;
    case 2:
        motorA    = MOTOR2_A;
        motorB    = MOTOR2_B;
        speed_pin = MOTOR2_PWM;
        break;
    case 3:
        motorA    = MOTOR3_A;
        motorB    = MOTOR3_B;
        speed_pin = MOTOR3_PWM;
        break;
    case 4:
        motorA    = MOTOR4_A;
        motorB    = MOTOR4_B;
        speed_pin = MOTOR4_PWM;
        break;
    default:
        break;
    }
}

void MotorControl::init()
{
    // Register control pins setup
    pinMode(MC_LATCH, OUTPUT);
    pinMode(MC_ENABLE, OUTPUT);
    pinMode(MC_DATA, OUTPUT);
    pinMode(MC_CLK, OUTPUT);
    // deactivate motors by default (EN pin is active low)
    register_output = 0;
    update_register();
    digitalWrite(MC_ENABLE, LOW);
}

void MotorControl::update_register()
{
    digitalWrite(MC_LATCH, LOW);
    shiftOut(MC_DATA, MC_CLK, MSBFIRST, register_output);
    // rising edge updates shift register output
    digitalWrite(MC_LATCH, HIGH);
}

void MotorControl::forward()
{
    bitSet(register_output, motorA);
    bitClear(register_output, motorB);
    update_register();
}

void MotorControl::backward()
{
    bitClear(register_output, motorA);
    bitSet(register_output, motorB);
    update_register();
}

void MotorControl::brake()
{
    bitClear(register_output, motorA);
    bitSet(register_output, motorB);
    update_register();
}

void MotorControl::setSpeed(byte speed)
{
    //  set speed
    analogWrite(speed_pin, speed);
}
