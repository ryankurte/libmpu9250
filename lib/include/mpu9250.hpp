/*
 * mpu9250 c++ wrapper
 *
 * Copyright 2016 Ryan Kurte
 */

#pragma once

#include "mcp9250_if.hpp"

namespace MPU9250
{

#include "mpu9250.h"
#include "mpu9250_defs.h"

class MPU9250
{
public:
    int Init(struct mpu9250_driver_s *driver) {
        return mpu9250_init(this.device, driver);
    }
    Close() {
        return mpu9250_close(this.device);
    }

private:
    struct mpu9250_s *device;
};


};

