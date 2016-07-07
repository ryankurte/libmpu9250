/*
 * mpu9250 driver functions
 *
 * Copyright 2016 Ryan Kurte
 */

#include "mpu9250.h"

#include <stdlib.h>
#include <stdint.h>

#include "mpu9250_regs.h"


/***        Internal Functions          ***/

static int mpu9250_reg_read(struct mpu9250_s *device, uint8_t reg, uint8_t* val) {
    uint8_t data_out[2];
    uint8_t data_in[2];
    int res;

    data_out[0] = reg | MPU9250_REG_READ_FLAG;
    data_out[1] = 0x00;

    res = device->driver->spi_transfer(device->driver_ctx, data_out, data_in, 2);

    if(res >= 0) {
        *val = data_in[1];
    }

    return res;
}

static int mpu9250_reg_write(struct mpu9250_s *device, uint8_t reg, uint8_t val) {
    uint8_t data_out[2];
    int res;

    data_out[0] = reg | MPU9250_REG_WRITE_FLAG;
    data_out[1] = val;

    res = device->driver->spi_transfer(device->driver_ctx, data_out, NULL, 2);

    return res;
}

/***        External Functions          ***/

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

int mpu9250_set_gyro_scale(struct mpu9250_s *device, mpu9250_gyro_scale_e scale)
{
    uint8_t gyro_cfg = 0;
    int res;

    // Read existing config
    res = mpu9250_reg_read(device, REG_GYRO_CONFIG, &gyro_cfg);
    if(res < 0) {
        return res;
    }

    // Update
    gyro_cfg &= ~MPU9250_GYRO_CONFIG_SCALE_MASK;
    gyro_cfg |=  MPU9250_GYRO_CONFIG_SCALE_MASK & (scale << MPU9250_GYRO_CONFIG_SCALE_SHIFT);
    
    // Write back
    return mpu9250_reg_write(device, REG_GYRO_CONFIG, gyro_cfg);
}

int mpu9250_set_accel_scale(struct mpu9250_s *device, mpu9250_accel_scale_e scale)
{
    uint8_t accel_cfg = 0;
    int res;

    // Read existing config
    res = mpu9250_reg_read(device, REG_ACCEL_CONFIG_1, &accel_cfg);
    if(res < 0) {
        return res;
    }

    // Update
    accel_cfg &= ~MPU9250_ACCEL_CONFIG_1_SCALE_MASK;
    accel_cfg |=  MPU9250_ACCEL_CONFIG_1_SCALE_MASK & (scale << MPU9250_ACCEL_CONFIG_1_SCALE_SHIFT);
    
    // Write back
    return mpu9250_reg_write(device, REG_ACCEL_CONFIG_1, accel_cfg);
}


int mpu9250_read_gyro(struct mpu9250_s *device, uint16_t *x, uint16_t *y, uint16_t *z)
{

}

int mpu9250_read_accel(struct mpu9250_s *device, uint16_t *x, uint16_t *y, uint16_t *z)
{

}

int mpu9250_read_temp(struct mpu9250_s *device, uint16_t *temp)
{

}


