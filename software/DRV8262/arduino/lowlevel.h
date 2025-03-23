// tuxlwl/software/DRV8262
// Copyright (C) 2024 Gymnasium der Stadt Rahden
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


/***************************************************************************


                   Low-Level Library for the DRV8262
                   motor controller board, PWM mode.
                       Created for ESP32 boards.

    - Daniel

***************************************************************************/

#ifndef __DRV8262_lowlevel_H__
#define __DRV8262_lowlevel_H__

#include <vector>
#include "Arduino.h"

typedef struct {
    uint8_t channelA;
    uint8_t pinA;
    uint8_t channelB;
    uint8_t pinB;
    uint8_t power;
    uint8_t direction;
} DRV8262_Motor;

class DRV8262 {
    public:
        void AddMotor(uint8_t pinA, uint8_t pinB);
        void AddMotor(uint8_t pinA, uint8_t pinB, uint8_t manualChannel);
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