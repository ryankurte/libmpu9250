/*
 * mpu9250 c++ to c driver adaptor
 * Converts between a c++ driver classes and underlying c function calls.
 *
 * Copyright 2016 Ryan Kurte
 */

#pragma once

#include "mpu9250/mpu9250.h"
#include "mpu9250/mpu9250_defs.h"

namespace MPU9250
{

// SPI driver interface class
class SpiDriverInterface {
public:
    virtual int spi_transfer(int len, uint8_t *data_out, uint8_t* data_in) = 0;
};

// Adaptor function, allows c++ object to be called from c(ish) context
int mpu9250_transfer_data_adaptor(void* context, int len, uint8_t *data_out, uint8_t* data_in)
{
    SpiDriverInterface *driver = (SpiDriverInterface*) context;
    return driver->spi_transfer(len, data_out, data_in);
}

// SPI Driver wrapper object
// Adapts C++ driver object for use in C based library
// Note that this can be static as driver context is passed separately to the driver
class SpiDriverWrapper {
public:
    static struct mpu9250_driver_s * GetWrapper() {
        return &driver;
    }

private:
    static struct mpu9250_driver_s driver;
};

struct mpu9250_driver_s SpiDriverWrapper::driver = { mpu9250_transfer_data_adaptor };


};

