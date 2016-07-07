

#include "mpu9250.h"

#include <stdlib.h>
#include <stdint.h>

#define DRIVER_CTX device->driver_ctx

static int mpu9250_reg_read(struct mpu9250_s *device, uint8_t reg, uint8_t* val) {
    uint8_t data_out[2];
    uint8_t data_in[2];
    int res;

    data_out[0] = reg | MPU9250_REG_READ_FLAG;
    data_out[1] = 0x00;

    res = device->driver->spi_transfer(DRIVER_CTX, data_out, data_in, 2);

    if(res >= 0) {
        *val = data_in[1];
    }

    return res;
}

static int mpu9250_reg_write(struct mpu9250_s *device, uint8_t reg, uint8_t val) {
    uint8_t data_out[2];
    int res;

    data_out[0] = reg;
    data_out[1] = val;

    res = device->driver->spi_transfer(DRIVER_CTX, data_out, NULL, 2);

    return res;
}

int8_t mpu9250_init(struct mpu9250_s *device, struct mpu9250_driver_s *driver, void* driver_ctx)
{
    // Check driver functions exist
    if(driver->spi_transfer == NULL) {
        return -1;
    }
    
    // Save driver pointers
    device->driver = driver;
    device->driver_ctx = driver_ctx;
    
    // TODO: init
    
    return 0;
}

int8_t mpu9250_close(struct mpu9250_s *device)
{
    // TODO: shutdown
    
    // Clear driver pointer
    device->driver = NULL;
    
    return 0;
}

