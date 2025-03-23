// tuxlwl/software/DRV8262
// Copyright (C) 2025 Gymnasium der Stadt Rahden
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

#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_adc/adc_continuous.h"

#include "drv8262.c"

#define motor_fl 0
#define motor_fr 1
#define motor_rl 2
#define motor_rr 3

#define LEDC_FREQUENCY 4000

// Create motor handles: these are invalid until initialised below.
drv8262_motor_handle_t motors[4];

void app_main(void)
{
  // Create a PWM controller timer with default ESP32 defines.
  ledc_timer_config_t ledc_timer = {
    .speed_mode      = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT,
    .timer_num       = LEDC_TIMER_0,
    .freq_hz         = LEDC_FREQUENCY,
    .clk_cfg         = LEDC_AUTO_CLK
  };
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  // Initialise the motor handles
  ESP_ERROR_CHECK(drv8262_motor_init(&ledc_timer, 13, 25, 0, 1, &motors[motor_fl]));
  ESP_ERROR_CHECK(drv8262_motor_init(&ledc_timer, 12, 33, 2, 3, &motors[motor_fr]));
  ESP_ERROR_CHECK(drv8262_motor_init(&ledc_timer, 2, 19, 4, 5, &motors[motor_rl]));
  ESP_ERROR_CHECK(drv8262_motor_init(&ledc_timer, 4, 14, 6, 7, &motors[motor_rr]));

  // This shorts out the motor (both pins are set to max power) resulting in active braking.
  ESP_ERROR_CHECK(drv8262_shortbrake(motors[motor_fl]));

  // Sets power to the motor as a float. This is scaled up to the duty resolution set in the timer.
  ESP_ERROR_CHECK(drv8262_set_power(motors[motor_fl], 0.5));

  // Set the motor direction.
  // DRV8262_DIRECTION_FORWARD: 0, this directs power to pin A
  // DRV8262_DIRECTION_REVERSE: 1, this directs power to pin B.
  ESP_ERROR_CHECK(drv8262_set_direction(motors[motor_fl], DRV8262_DIRECTION_REVERSE));

  // Combined set power and set direction.
  ESP_ERROR_CHECK(drv8262_set_power_and_direction(motors[motor_fl], 0.5, DRV8262_DIRECTION_FORWARD));

  // Apply. This is required for all "set" functions
  ESP_ERROR_CHECK(drv8262_apply(motors[motor_fl]));
}