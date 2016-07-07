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

static int mpu9250_read_reg(struct mpu9250_s *device, uint8_t reg, uint8_t* val)
{
    uint8_t data_out[2];
    uint8_t data_in[2];
    int res;

    data_out[0] = reg | MPU9250_REG_READ_FLAG;
    data_out[1] = 0x00;

    res = device->driver->spi_transfer(device->driver_ctx, data_out, data_in, 2);

    if (res >= 0) {
        *val = data_in[1];
    }

    return res;
}

static int mpu9250_read_regs(struct mpu9250_s *device, uint8_t start, uint8_t length, uint8_t* data)
{
    uint8_t data_out[length + 1];
    uint8_t data_in[length + 1];
    int res;

    data_out[0] = start | MPU9250_REG_READ_FLAG;
    for (int i = 0; i < length; i++) {
        data_out[i + 1] = 0x00;
    }

    res = device->driver->spi_transfer(device->driver_ctx, data_out, data_in, length + 1);

    if (res >= 0) {
        for (int i = 0; i < length; i++) {
            data[i] = data_in[i + 1];
        }
    }

    return res;
}

static int mpu9250_write_reg(struct mpu9250_s *device, uint8_t reg, uint8_t val)
{
    uint8_t data_out[2];
    int res;

    data_out[0] = reg | MPU9250_REG_WRITE_FLAG;
    data_out[1] = val;

    res = device->driver->spi_transfer(device->driver_ctx, data_out, NULL, 2);

    return res;
}

int mpu9250_update_reg(struct mpu9250_s *device, uint8_t reg, uint8_t val, uint8_t mask)
{
    uint8_t data = 0;
    int res;

    // Read existing config
    res = mpu9250_read_reg(device, reg, &data);
    if (res < 0) {
        return res;
    }

    // Update
    data &= ~mask;
    data |=  mask & val;

    // Write back
    return mpu9250_write_reg(device, reg, data);
}

/***        External Functions          ***/

int8_t mpu9250_init(struct mpu9250_s *device, struct mpu9250_driver_s *driver, void* driver_ctx)
{
    // Check driver functions exist
    if (driver->spi_transfer == NULL) {
        return -1;
    }

    // Save driver pointers
    device->driver = driver;
    device->driver_ctx = driver_ctx;

    // TODO: init

    // Reboot

    // Enable compass

    // Set default scales

    // Set default sampling rate


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
    return mpu9250_update_reg(device,
                              REG_GYRO_CONFIG,
                              scale << MPU9250_GYRO_CONFIG_SCALE_SHIFT,
                              MPU9250_GYRO_CONFIG_SCALE_MASK);
}

int mpu9250_set_accel_scale(struct mpu9250_s *device, mpu9250_accel_scale_e scale)
{
    return mpu9250_update_reg(device,
                              REG_ACCEL_CONFIG_1,
                              scale << MPU9250_ACCEL_CONFIG_1_SCALE_SHIFT,
                              MPU9250_ACCEL_CONFIG_1_SCALE_MASK);
}


int mpu9250_read_gyro_raw(struct mpu9250_s *device, uint16_t *x, uint16_t *y, uint16_t *z)
{
    uint8_t data_in[6];
    int res;

    res = mpu9250_read_regs(device, REG_GYRO_XOUT_H, 6, data_in);
    if (res >= 0) {
        *x = (uint16_t)data_in[0] << 8 | data_in[1];
        *y = (uint16_t)data_in[2] << 8 | data_in[3];
        *z = (uint16_t)data_in[4] << 8 | data_in[5];
    }
    return res;

}

int mpu9250_read_accel_raw(struct mpu9250_s *device, uint16_t *x, uint16_t *y, uint16_t *z)
{
    uint8_t data_in[6];
    int res;

    res = mpu9250_read_regs(device, REG_ACCEL_XOUT_H, 6, data_in);
    if (res >= 0) {
        *x = (uint16_t)data_in[0] << 8 | data_in[1];
        *y = (uint16_t)data_in[2] << 8 | data_in[3];
        *z = (uint16_t)data_in[4] << 8 | data_in[5];
    }
    return res;

}

int mpu9250_read_temp_raw(struct mpu9250_s *device, uint16_t *temp)
{
    uint8_t data_in[2];
    int res;

    res = mpu9250_read_regs(device, REG_TEMP_OUT_H, 2, data_in);
    if (res >= 0) {
        *temp = data_in[0] << 8 | data_in[1];
    }
    return res;
}


