/***************************************************************************


                   Low-Level Library for the DRV8262
                   motor controller board, PWM mode.
                       Created for ESP32 boards.

    - Daniel

***************************************************************************/

#ifndef __DRV8262_lowlevel_H__
#define __DRV8262_lowlevel_H__

#include <vector>

typedef struct {
    uint8_t channelA;
    uint8_t pinA;
    uint8_t channelB;
    uint8_t pinB;
    uint8_t power;
    uint8_t direction;
} DRV8262_Motor;

struct DRV8262 {
    public:
        void AddMotor(uint8_t pinA, uint8_t pinB);
        void SetPower(uint8_t id, uint8_t power, uint8_t direction);
        void SetPower(uint8_t id, uint8_t power);
        void Shortbrake(uint8_t id);
        void Disable(uint8_t id);
    private:
        void ApplyMotor(DRV8262_Motor *motor);
        uint8_t channelAmount;
        std::vector<DRV8262_Motor> motorList;
};

#endif
