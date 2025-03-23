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


/***************************************************************************


                   Low-Level Library for the DRV8262
                   motor controller board, PWM mode.
                       Created for ESP32 boards.

    - Daniel

***************************************************************************/

#include "driver/ledc.h"

#define DRV8262_LEDC_MODE LEDC_LOW_SPEED_MODE
#define DRV8262_DIRECTION_FORWARD 0
#define DRV8262_DIRECTION_REVERSE 1

typedef uint8_t drv8262_motor_id_t;
typedef uint8_t drv8262_motor_pin_t;
typedef uint8_t drv8262_motor_channel_t;
typedef uint32_t drv8262_timer_freq_t;

typedef struct {
  ledc_timer_config_t* timer;
  drv8262_motor_channel_t channel_a;
  drv8262_motor_pin_t pin_a;
  drv8262_motor_channel_t channel_b;
  drv8262_motor_pin_t pin_b;
  float power;
  uint8_t direction : 1;
} drv8262_motor_ctx_t;

typedef drv8262_motor_ctx_t* drv8262_motor_handle_t;

static esp_err_t drv8262_motor_init(ledc_timer_config_t* ledc_timer, drv8262_motor_pin_t pin_a, drv8262_motor_pin_t pin_b, drv8262_motor_channel_t channel_a, drv8262_motor_channel_t channel_b, drv8262_motor_handle_t *out_handle)
{
  if (ledc_timer == NULL) {
    return ESP_ERR_INVALID_ARG;
  }

  ledc_channel_config_t ledc_channel_a = {
    .speed_mode = ledc_timer->speed_mode,
    .channel    = channel_a,
    .timer_sel  = ledc_timer->timer_num,
    .intr_type  = LEDC_INTR_DISABLE,
    .gpio_num   = pin_a,
    .duty       = 0,
    .hpoint     = 0,
  };
  esp_err_t err_ret = (ledc_channel_config(&ledc_channel_a));
  if (err_ret != ESP_OK) {
    return err_ret;
  }

  ledc_channel_config_t ledc_channel_b = {
    .speed_mode = ledc_timer->speed_mode,
    .channel    = channel_b,
    .timer_sel  = ledc_timer->timer_num,
    .intr_type  = LEDC_INTR_DISABLE,
    .gpio_num   = pin_b,
    .duty       = 0,
    .hpoint     = 0,
  };
  err_ret = (ledc_channel_config(&ledc_channel_b));
  if (err_ret != ESP_OK) {
    return err_ret;
  }

  drv8262_motor_ctx_t *context = out_handle;
  context->timer = ledc_timer;
  context->channel_a = channel_a;
  context->pin_a = pin_a;
  context->channel_b = channel_b;
  context->pin_b = pin_b;

  *out_handle = context;

  return ESP_OK;
}

static esp_err_t drv8262_apply(drv8262_motor_handle_t handle) {
  if (handle == NULL) {
    return ESP_ERR_INVALID_ARG;
  }
  drv8262_motor_ctx_t *motor = handle;

  uint32_t duty = (motor->timer->duty_resolution)*(motor->power);
  esp_err_t err_ret = ledc_set_duty_and_update(DRV8262_LEDC_MODE, motor->channel_a, duty*(1-motor->direction), 0);
  if (err_ret != ESP_OK) {
    return err_ret;
  }
  err_ret = ledc_set_duty_and_update(DRV8262_LEDC_MODE, motor->channel_b, duty*(0-motor->direction), 0);
  if (err_ret != ESP_OK) {
    return err_ret;
  }

  return ESP_OK;
}

static esp_err_t drv8262_set_power(drv8262_motor_handle_t handle, float new_power) {
  if (handle == NULL) {
    return ESP_ERR_INVALID_ARG;
  }
  drv8262_motor_ctx_t* motor = handle;

  motor->power = new_power;

  return ESP_OK;
}

static esp_err_t drv8262_set_direction(drv8262_motor_handle_t handle, uint8_t new_direction) {
  if (handle == NULL) {
    return ESP_ERR_INVALID_ARG;
  }
  drv8262_motor_ctx_t* motor = handle;

  motor->direction = new_direction;

  return ESP_OK;
}

static esp_err_t drv8262_set_power_and_direction(drv8262_motor_handle_t handle, float new_power, uint8_t new_direction) {
  if (handle == NULL) {
    return ESP_ERR_INVALID_ARG;
  }
  drv8262_motor_ctx_t* motor = handle;

  motor->power = new_power;
  motor->direction = new_direction;

  return ESP_OK;
}

static esp_err_t drv8262_shortbrake(drv8262_motor_handle_t handle) {
  if (handle == NULL) {
    return ESP_ERR_INVALID_ARG;
  }
  drv8262_motor_ctx_t* motor = handle;

  uint32_t duty = (motor->timer->duty_resolution)*(motor->power);
  esp_err_t err_ret = ledc_set_duty_and_update(DRV8262_LEDC_MODE, motor->channel_a, duty*(1-motor->direction), 0);
  if (err_ret != ESP_OK) {
    return err_ret;
  }
  err_ret = ledc_set_duty_and_update(DRV8262_LEDC_MODE, motor->channel_b, duty*(0-motor->direction), 0);
  if (err_ret != ESP_OK) {
    return err_ret;
  }

  return ESP_OK;
}