/*
 * mpu9250 driver functions
 *
 * Copyright 2016 Ryan Kurte
 */

#include "mpu9250/mpu9250.h"

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "mpu9250/mpu9250_regs.h"

//#define DEBUG_MPU9250

// Scalar for conversion from G to ms-2
#define G_TO_MS 9.80665

// Define PI if not available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Automagically define PLATFORM_SLEEP_MS and _US on unix-like platforms
#ifndef PLATFORM_SLEEP_MS
#if (defined __linux__ || defined __APPLE__ || defined __unix__)
#include <unistd.h>
#define PLATFORM_SLEEP_MS(a)    usleep(a * 1000);
#define PLATFORM_SLEEP_US(a)    usleep(a);
#else
#warning "PLATFORM_SLEEP_MS undefined and platform not recognised"
#define PLATFORM_SLEEP_MS(a) for (volatile uint32_t i = 0; i < 1000000; i++);
#define PLATFORM_SLEEP_US(a) for (volatile uint32_t i = 0; i < 1000; i++);
#endif

#else
extern void PLATFORM_SLEEP_MS(uint32_t);
extern void PLATFORM_SLEEP_US(uint32_t);
#endif

// Wrap debug outputs
#ifdef DEBUG_MPU9250
#define MPU9250_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define MPU9250_DEBUG_PRINT(...)
#endif


/***        Internal Functions          ***/

// Read a single register from the device
static int mpu9250_read_reg(struct mpu9250_s *device, uint8_t reg, uint8_t* val)
{
    uint8_t data_out[2] = {0xFF, 0xFF};
    uint8_t data_in[2] = {0xFF, 0xFF};
    int res;

    data_out[0] = reg | MPU9250_REG_READ_FLAG;
    data_out[1] = 0x00;

    res = device->driver->spi_transfer(device->driver_ctx, 2, data_out, data_in);

    if (res >= 0) {
        *val = data_in[1];
    }

    return res;
}

// Read an array of registers from the device
static int mpu9250_read_regs(struct mpu9250_s *device, uint8_t start, uint8_t length, uint8_t* data)
{
    uint8_t data_out[length + 1];
    uint8_t data_in[length + 1];
    int res;

    data_out[0] = start | MPU9250_REG_READ_FLAG;
    for (int i = 0; i < length; i++) {
        data_out[i + 1] = 0x00;
    }

    res = device->driver->spi_transfer(device->driver_ctx, length + 1, data_out, data_in);

    if (res >= 0) {
        for (int i = 0; i < length; i++) {
            data[i] = data_in[i + 1];
        }
    }

    return res;
}

// Write a single register on the device
static int mpu9250_write_reg(struct mpu9250_s *device, uint8_t reg, uint8_t val)
{
    uint8_t data_out[2] = {0xFF, 0xFF};
    uint8_t data_in[2] = {0xFF, 0xFF};
    int res;

    data_out[0] = reg | MPU9250_REG_WRITE_FLAG;
    data_out[1] = val;

    res = device->driver->spi_transfer(device->driver_ctx, 2, data_out, data_in);

    return res;
}

// Update a single register on the device
// Mask should be the mask for the information to be changed
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

// Write a single compass register
int mpu9250_write_compass_reg(struct mpu9250_s *device, uint8_t reg, uint8_t val)
{
    int res;

    // Set I2C to write address
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_ADDR, MPU9250_COMPASS_ADDR | MPU9250_COMPASS_WRITE_FLAG);
    if (res < 0) {
        return res;
    }
    // Set register address
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_REG, reg);
    if (res < 0) {
        return res;
    }
    // Buffer data for writing
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_DO, val);
    if (res < 0) {
        return res;
    }
    // Trigger write
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_CTRL, MPU9250_I2C_SLV_CTRL_EN | (1 & MPU9250_I2C_SLV_CTRL_LENG_MASK));

    return res;

}

// Read a single compass register
int mpu9250_read_compass_reg(struct mpu9250_s *device, uint8_t reg, uint8_t *val)
{
    int res;

    // Set I2C to read address
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_ADDR, MPU9250_COMPASS_ADDR | MPU9250_COMPASS_READ_FLAG);
    if (res < 0) {
        return res;
    }
    // Set register address
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_REG, reg);
    if (res < 0) {
        return res;
    }
    // Trigger read
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_CTRL, MPU9250_I2C_SLV_CTRL_EN | (1 & MPU9250_I2C_SLV_CTRL_LENG_MASK));
    if (res < 0) {
        return res;
    }

    // Wait for response
    //TODO: should be able to await interrupt on pin here
    PLATFORM_SLEEP_MS(1);

    res = mpu9250_read_reg(device, MPU9250_REG_EXT_SENS_DATA_00, val);

    return res;
}

int mpu9250_read_compass_regs(struct mpu9250_s *device, uint8_t reg, uint8_t len, uint8_t *vals)
{
    int res;

    // Set I2C to read address
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_ADDR, MPU9250_COMPASS_ADDR | MPU9250_COMPASS_READ_FLAG);
    if (res < 0) {
        return res;
    }
    // Set register address
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_REG, reg);
    if (res < 0) {
        return res;
    }
    // Trigger read
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_CTRL, MPU9250_I2C_SLV_CTRL_EN | (len & MPU9250_I2C_SLV_CTRL_LENG_MASK));
    if (res < 0) {
        return res;
    }

    // Wait for response
    PLATFORM_SLEEP_MS(1);

    res = mpu9250_read_regs(device, MPU9250_REG_EXT_SENS_DATA_00, len, vals);

    return res;
}

/***        External Functions          ***/

int8_t mpu9250_init(struct mpu9250_s *device, struct mpu9250_driver_s *driver, void* driver_ctx)
{
    int res;

    // Check driver functions exist
    if (driver->spi_transfer == NULL) {
        return MPU9250_DRIVER_INVALID;
    }

    // Save driver pointers
    device->driver = driver;
    device->driver_ctx = driver_ctx;

    // Initialize device

    // Hard reset chip (nb. only works if SPI working)
    res = mpu9250_write_reg(device, MPU9250_REG_PWR_MGMT_1, MPU9250_PWR_MGMT_1_HRESET);
    if (res < 0) {
        MPU9250_DEBUG_PRINT("RESET write error: %d\r\n", res);
        return MPU9250_DRIVER_ERROR;
    }

    // Give device time to reset
    PLATFORM_SLEEP_MS(10);

    MPU9250_DEBUG_PRINT("RESET complete\r\n");

    // Check communication
    uint8_t who;
    res = mpu9250_read_reg(device, MPU9250_REG_WHO_AM_I, &who);
    if (res < 0) {
        MPU9250_DEBUG_PRINT("WHOAMI read error: %d\r\n", res);
        return MPU9250_DRIVER_ERROR;
    }
    if (who != 0x71) {
        MPU9250_DEBUG_PRINT("Unexpected whoami response: %.2x\r\n", who);
        return MPU9250_COMMS_ERROR;
    }

    MPU9250_DEBUG_PRINT("Device identified\r\n");

    // Set default scales
    res = mpu9250_set_gyro_scale(device, MPU9250_GYRO_SCALE_2000DPS);
    if (res < 0) {
        MPU9250_DEBUG_PRINT("Error %d setting gyro scale\r\n", res);
        return MPU9250_DRIVER_ERROR;
    }

    res = mpu9250_set_accel_scale(device, MPU9250_ACCEL_SCALE_16G);
    if (res < 0) {
        MPU9250_DEBUG_PRINT("Error %d setting accel scale\r\n", res);
        return MPU9250_DRIVER_ERROR;
    }

    // TODO: Set default sampling rates & filters


    // Enable compass

    // Enable master mode
    res = mpu9250_write_reg(device, MPU9250_REG_USER_CTRL, MPU9250_USER_CTRL_I2C_MST_EN);
    // Set freq to 400kHz
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_MST_CTRL, MPU9250_I2C_MST_CLK_400_KHZ);
    // Set compass device address
    res = mpu9250_write_reg(device, MPU9250_REG_I2C_SLV0_ADDR, MPU9250_COMPASS_ADDR);

    // Reset compass
    res = mpu9250_write_compass_reg(device, MPU9250_COMPASS_REG_CNTL2, MPU9250_COMPASS_CTL2_RESET);

    // Check for compass whoami response
    res = mpu9250_read_compass_reg(device, MPU9250_COMPASS_REG_WIA, &who);
    if (res < 0) {
        MPU9250_DEBUG_PRINT("WHOAMI compass read error: %d\r\n", res);
        return MPU9250_DRIVER_ERROR;
    }
    if (who != 0x48) {
        MPU9250_DEBUG_PRINT("Unexpected compass whoami response: %.2x\r\n", who);
        return MPU9250_COMMS_ERROR;
    }

    MPU9250_DEBUG_PRINT("Compass identified\r\n");

    // Enable continuous measurement mode at 16-bit
    res = mpu9250_write_compass_reg(device, MPU9250_COMPASS_REG_CNTL1, MPU9250_COMPASS_CTL1_OUTPUT_16BIT
                                    | (MPU9250_COMPASS_CTL1_MODE_MASK & MPU9250_COMPASS_MODE_CONTINUOUS1));
    if (res < 0) {
        MPU9250_DEBUG_PRINT("Error %d setting compass mode\r\n", res);
        return MPU9250_DRIVER_ERROR;
    }

    //TODO: set compass auto trigger from MPU to regs


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
    switch (scale) {
    case MPU9250_GYRO_SCALE_250DPS:
        device->gyro_scale = 250.0 / 180 * M_PI / (float)GYRO_SCALE_BASE;
        break;
    case MPU9250_GYRO_SCALE_500DPS:
        device->gyro_scale = 500.0 / 180 * M_PI / (float)GYRO_SCALE_BASE;
        break;
    case MPU9250_GYRO_SCALE_1000DPS:
        device->gyro_scale = 1000.0 / 180 * M_PI / (float)GYRO_SCALE_BASE;
        break;
    case MPU9250_GYRO_SCALE_2000DPS:
        device->gyro_scale = 2000.0 / 180 * M_PI / (float)GYRO_SCALE_BASE;
        break;
    default:
        return -1;
    }

    return mpu9250_update_reg(device,
                              MPU9250_REG_GYRO_CONFIG,
                              scale << MPU9250_GYRO_CONFIG_SCALE_SHIFT,
                              MPU9250_GYRO_CONFIG_SCALE_MASK);
}

int mpu9250_set_accel_scale(struct mpu9250_s *device, mpu9250_accel_scale_e scale)
{
    switch (scale) {
    case MPU9250_ACCEL_SCALE_2G:
        device->accel_scale = 2.0 / (float)ACCEL_SCALE_BASE;
        break;
    case MPU9250_ACCEL_SCALE_4G:
        device->accel_scale = 4.0 / (float)ACCEL_SCALE_BASE;
        break;
    case MPU9250_ACCEL_SCALE_8G:
        device->accel_scale = 8.0 / (float)ACCEL_SCALE_BASE;
        break;
    case MPU9250_ACCEL_SCALE_16G:
        device->accel_scale = 16.0 / (float)ACCEL_SCALE_BASE;
        break;
    default:
        return -1;
    }

    return mpu9250_update_reg(device,
                              MPU9250_REG_ACCEL_CONFIG_1,
                              scale << MPU9250_ACCEL_CONFIG_1_SCALE_SHIFT,
                              MPU9250_ACCEL_CONFIG_1_SCALE_MASK);
}


int mpu9250_read_gyro_raw(struct mpu9250_s *device, int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t data_in[6];
    int res;

    res = mpu9250_read_regs(device, MPU9250_REG_GYRO_XOUT_H, 6, data_in);
    if (res >= 0) {
        *x = (int16_t)data_in[0] << 8 | data_in[1];
        *y = (int16_t)data_in[2] << 8 | data_in[3];
        *z = (int16_t)data_in[4] << 8 | data_in[5];
    }
    return res;

}

int mpu9250_read_gyro(struct mpu9250_s *device, float *x, float *y, float *z)
{
    int16_t raw_x, raw_y, raw_z;
    int res;

    res = mpu9250_read_gyro_raw(device, &raw_x, &raw_y, &raw_z);
    if (res >= 0) {
        *x = raw_x * device->gyro_scale;
        *y = raw_y * device->gyro_scale;
        *z = raw_z * device->gyro_scale;
    }

    return res;
}

int mpu9250_read_accel_raw(struct mpu9250_s *device, int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t data_in[6];
    int res;

    res = mpu9250_read_regs(device, MPU9250_REG_ACCEL_XOUT_H, 6, data_in);
    if (res >= 0) {
        *x = (int16_t)data_in[0] << 8 | data_in[1];
        *y = (int16_t)data_in[2] << 8 | data_in[3];
        *z = (int16_t)data_in[4] << 8 | data_in[5];
    }
    return res;

}

int mpu9250_read_accel(struct mpu9250_s *device, float *x, float *y, float *z)
{
    int16_t raw_x, raw_y, raw_z;
    int res;

    res = mpu9250_read_accel_raw(device, &raw_x, &raw_y, &raw_z);
    if (res >= 0) {
        *x = raw_x * device->accel_scale;
        *y = raw_y * device->accel_scale;
        *z = raw_z * device->accel_scale;
    }

    return res;
}

int mpu9250_read_temp_raw(struct mpu9250_s *device, int16_t *temp)
{
    uint8_t data_in[2];
    int res;

    res = mpu9250_read_regs(device, MPU9250_REG_TEMP_OUT_H, 2, data_in);
    if (res >= 0) {
        *temp = data_in[0] << 8 | data_in[1];
    }
    return res;
}

int mpu9250_read_temp(struct mpu9250_s *device, float* temp)
{

    int16_t raw_temp;
    int res;

    res = mpu9250_read_temp_raw(device, &raw_temp);
    if (res >= 0) {
        //TODO: no datasheet source for these factors
        // Find and refactor out to constants.
        *temp = ((float)raw_temp / 340) + 36.53;
    }

    return res;
}

int mpu9250_read_compass_raw(struct mpu9250_s *device, int16_t *temp, int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t data_in[7];
    int res;

    // ST2 reg must be read to unlatch data registers
    // As this immediately follows the data register, this is easily achieved by reading 7 bytes
    res = mpu9250_read_compass_regs(device, MPU9250_COMPASS_REG_HXL, 7, data_in);
    if (res >= 0) {
        *x = (int16_t)data_in[0] << 8 | data_in[1];
        *y = (int16_t)data_in[2] << 8 | data_in[3];
        *z = (int16_t)data_in[4] << 8 | data_in[5];
    }
    return res;
}


