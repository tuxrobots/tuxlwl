/***************************************************************************


                   Low-Level Library for the DRV8262
                   motor controller board, PWM mode.
                       Created for ESP32 boards.

    - Daniel

***************************************************************************/

#include <vector>
#include "lowlevel.h"

void DRV8262::AddMotor(uint8_t pinA, uint8_t pinB) {
    DRV8262_Motor newMotor;
    newMotor.pinA = pinA;
    newMotor.pinB = pinB;
    newMotor.channelA = DRV8262::channelAmount;
    newMotor.channelB = DRV8262::channelAmount+1;

    ledcSetup(newMotor.channelA, 400, 8);
    ledcAttachPin(newMotor.pinA, newMotor.channelA);
    ledcWrite(newMotor.channelA, 0);

    ledcSetup(newMotor.channelB, 400, 8);
    ledcAttachPin(newMotor.pinB, newMotor.channelB);
    ledcWrite(newMotor.channelB, 0);

    DRV8262::channelAmount+=2;
    DRV8262::motorList.push_back(newMotor);
}

void DRV8262::ApplyMotor(DRV8262_Motor *motor) {
    if (motor->direction) {
        ledcWrite(motor->channelA, motor->power);
        ledcWrite(motor->channelB, (uint8_t)0);
    } else {
        ledcWrite(motor->channelA, (uint8_t)0);
        ledcWrite(motor->channelB, motor->power);
    }
}

void DRV8262::SetPower(uint8_t id, uint8_t power, uint8_t direction) {
    DRV8262::motorList[id].power = power;
    DRV8262::motorList[id].direction = direction;
    DRV8262::ApplyMotor(&DRV8262::motorList[id]);
}

void DRV8262::SetPower(uint8_t id, uint8_t power) {
    DRV8262::motorList[id].power = power;
    DRV8262::ApplyMotor(&DRV8262::motorList[id]);
}

void DRV8262::Disable(uint8_t id) {
    ledcWrite(DRV8262::motorList[id].channelA, (uint8_t)0);
    ledcWrite(DRV8262::motorList[id].channelB, (uint8_t)0);
}

void DRV8262::Shortbrake(uint8_t id) {
    ledcWrite(DRV8262::motorList[id].channelA, (uint8_t)255);
    ledcWrite(DRV8262::motorList[id].channelB, (uint8_t)255);
}
