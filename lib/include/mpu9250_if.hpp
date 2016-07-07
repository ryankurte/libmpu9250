/*
 * mpu9250 c++ to c driver adaptor
 * Converts between a c++ driver classes and underlying c function calls.
 *
 * Copyright 2016 Ryan Kurte
 */

#pragma once

namespace MPU9250
{

// SPI driver interface class
class SpiDriverInterface {
    virtual int spi_transfer(uint8_t *data_in, uint8_t* data_out, uint8_t len) = 0;
};

// Adaptor function, allows c++ object to be called from c(ish) context
int8_t mpu9250_transfer_data_adaptor(void* context, uint8_t *data_in, uint8_t* data_out, uint8_t size)
{
    SpiDriverInterface *driver = (SpiDriverInterface*) context;
    return hal->spi_transfer(data_in, data_out, size);
}

// SPI Driver wrapper object
// Adapts C++ driver object for use in C based library
// Note that this can be static as driver context is passed separately to the driver
class SpiDriverWrapper {
public:
    static DriverWrapper() {
        driver.spi_transfer = mpu9250_transfer_data_adaptor;
    }

    static struct mpu9250_driver_s GetWrapper() {
        return driver;
    }

private:
    static struct mpu9250_driver_s driver;
};

};

