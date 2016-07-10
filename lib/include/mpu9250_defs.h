/*
 * mpu9250 related definitions for internal library use
 *
 * Copyright 2016 Ryan Kurte
 */

#ifndef MPU9250_DEFS_H
#define MPU9250_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

// Gyro configuration definitions
#define MPU9250_GYRO_CONFIG_X_SELF_TEST_EN     (1 << 7)
#define MPU9250_GYRO_CONFIG_Y_SELF_TEST_EN     (1 << 6)
#define MPU9250_GYRO_CONFIG_Z_SELF_TEST_EN     (1 << 5)

#define MPU9250_GYRO_CONFIG_SCALE_MASK          0x18
#define MPU9250_GYRO_CONFIG_SCALE_SHIFT         3

typedef enum {
    MPU9250_GYRO_SCALE_250DPS  = 0x00,
    MPU9250_GYRO_SCALE_500DPS  = 0x01,
    MPU9250_GYRO_SCALE_1000DPS = 0x02,
    MPU9250_GYRO_SCALE_2000DPS = 0x03
} mpu9250_gyro_scale_e;

#define GYRO_RESOLUTION_BITS    16


// Accel configuration definitions
#define MPU9250_ACCEL_CONFIG_1_X_SELF_TEST_EN     (1 << 7)
#define MPU9250_ACCEL_CONFIG_1_Y_SELF_TEST_EN     (1 << 6)
#define MPU9250_ACCEL_CONFIG_1_Z_SELF_TEST_EN     (1 << 5)

#define MPU9250_ACCEL_CONFIG_1_SCALE_MASK          0x18
#define MPU9250_ACCEL_CONFIG_1_SCALE_SHIFT         3

typedef enum {
    MPU9250_ACCEL_SCALE_2G  = 0x00,
    MPU9250_ACCEL_SCALE_4G  = 0x01,
    MPU9250_ACCEL_SCALE_8G  = 0x02,
    MPU9250_ACCEL_SCALE_16G = 0x03
} mpu9250_accel_scale_e;

#define ACCEL_RESOLUTION_BITS   16

// General configuration
#define MPU9250_REG_READ_FLAG       0x80
#define MPU9250_REG_WRITE_FLAG      0x80

#define MPU9250_PWR_MGMT_1_HRESET   (1 << 7)

// MPU9250 object for internal use
struct mpu9250_s {
    int open;                           //!< Indicates whether the device is open
    struct mpu9250_driver_s* driver;    //!< Driver function object
    void* driver_ctx;                   //!< Driver context
    float gyro_scale;
    float accel_scale;
};


#ifdef __cplusplus
}
#endif

#endif
