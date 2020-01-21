#include <MotorControl.h>

// Select the motors to control
MotorControl motor1(1);
MotorControl motor2(2);

void setup()
{
    // Initialize the shield for operation
    MotorControl::init();
}

void loop()
{
    // Set the motors initial speeds
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    // Move forward
    motor1.forward();
    motor2.forward();
    delay(5000);
    // Move backwards slowly
    motor1.setSpeed(127);
    motor2.setSpeed(127);
    motor1.backward();
    motor2.backward();
    delay(5000);
    // Stop!
    motor1.brake();
    motor2.brake();
    delay(3000);
}
