/*
 * mpu9250 c++ wrapper
 *
 * Copyright 2016 Ryan Kurte
 */

#pragma once

#include "mpu9250/mpu9250_if.hpp"

namespace MPU9250
{

#include "mpu9250/mpu9250.h"
#include "mpu9250/mpu9250_defs.h"

class Mpu9250
{
public:

    // Init using C style driver interface
    int init(struct mpu9250_driver_s *driver, void *driver_ctx) {
        return mpu9250_init(&(this->device), driver, driver_ctx);
    }

    // Init using C++ style driver interface
    int init(SpiDriverInterface* driver_ctx) {
        struct mpu9250_driver_s *driver = SpiDriverWrapper::GetWrapper();
        return mpu9250_init(&(this->device), driver, (void*)driver_ctx);
    }

    // Close device
    int close() {
        return mpu9250_close(&(this->device));
    }

    int set_gyro_scale(mpu9250_gyro_scale_e scale) {
        return mpu9250_set_gyro_scale(&(this->device), scale);
    }
    int set_accel_scale(mpu9250_accel_scale_e scale) {
        return mpu9250_set_accel_scale(&(this->device), scale);
    }

    int read_gyro_raw(int16_t *x, int16_t *y, int16_t *z) {
        return mpu9250_read_gyro_raw(&(this->device), x, y, z);
    }
    int read_accel_raw(int16_t *x, int16_t *y, int16_t *z) {
        return mpu9250_read_accel_raw(&(this->device), x, y, z);
    }
    int read_temp_raw(int16_t *temp) {
        return mpu9250_read_temp_raw(&(this->device), temp);
    }

    int read_gyro(float *x, float *y, float *z) {
        return mpu9250_read_gyro(&(this->device), x, y, z);
    }
    int read_accel(float *x, float *y, float *z) {
        return mpu9250_read_accel(&(this->device), x, y, z);
    }
    int read_temp(float *temp) {
        return mpu9250_read_temp(&(this->device), temp);
    }

private:
    struct mpu9250_s device;
};


};

