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

/**
 * Gyro full scale setting
 * Configures the maximum operating range of the gyroscope
 */
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

/**
 * Accelerometer full scale setting
 * Configures the maximum operating range of the accelerometer
 */
typedef enum {
    MPU9250_ACCEL_SCALE_2G  = 0x00,
    MPU9250_ACCEL_SCALE_4G  = 0x01,
    MPU9250_ACCEL_SCALE_8G  = 0x02,
    MPU9250_ACCEL_SCALE_16G = 0x03
} mpu9250_accel_scale_e;

#define ACCEL_RESOLUTION_BITS   16

/**
 * Accelerometer Digital Low Pass Filter (DPLF) bandwidth configuration
 * DPLF can be disabled with ACCEL_FCHOICE = 0
 */
typedef enum {
    MPU9250_ACCEL_DPLF_CFG_1_13KHz_DELAY_0_75MS = 0x00,     //!< BW: 1.13 kHz Delay: 0.75 ms rate: 4kHz. DPLF disabled.
    MPU9250_ACCEL_DPLF_CFG_460Hz_DELAY_1_94MS   = 0x00,     //!< BW: 460Hz Delay: 1.94 ms rate: 1kHz
    MPU9250_ACCEL_DPLF_CFG_184Hz_DELAY_5_80MS   = 0x01,     //!< BW: 184Hz Delay: 5.80 ms rate: 1kHz
    MPU9250_ACCEL_DPLF_CFG_92Hz_DELAY_7_80MS    = 0x02,     //!< BW: 92Hz Delay: 7.10 ms rate: 1kHz
    MPU9250_ACCEL_DPLF_CFG_41Hz_DELAY_11_80MS   = 0x03,     //!< BW: 41Hz Delay: 11.80 ms rate: 1kHz
    MPU9250_ACCEL_DPLF_CFG_20Hz_DELAY_19_80MS   = 0x04,     //!< BW: 20Hz Delay: 19.80 ms rate: 1kHz
    MPU9250_ACCEL_DPLF_CFG_10Hz_DELAY_35_70MS   = 0x05,     //!< BW: 10Hz Delay: 35.70 ms rate: 1kHz
    MPU9250_ACCEL_DPLF_CFG_5Hz_DELAY_66_96MS    = 0x06,     //!< BW: 5Hz Delay: 66.96 ms rate: 1kHz
    MPU9250_ACCEL_DPLF_CFG_460Hz_DELAY_1_94MS   = 0x07,     //!< BW: 460Hz Delay: 1.94 ms rate: 1kHz
} mpu9250_accel_dplf_cfg_e;

// General configuration
#define MPU9250_REG_READ_FLAG       0x80
#define MPU9250_REG_WRITE_FLAG      0x80

#define MPU9250_PWR_MGMT_1_HRESET   (1 << 7)    //!< Power management reset flag

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
