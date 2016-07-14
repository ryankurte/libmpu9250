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
#define GYRO_SCALE_BASE         (pow(2, GYRO_RESOLUTION_BITS) / 2)

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
#define ACCEL_SCALE_BASE        (pow(2, ACCEL_RESOLUTION_BITS) / 2)

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
    MPU9250_ACCEL_DPLF_CFG_460Hz_DELAY_1_94MS_B = 0x07,     //!< BW: 460Hz Delay: 1.94 ms rate: 1kHz
} mpu9250_accel_dplf_cfg_e;

// I2C Master Control Register
#define MPU9250_I2C_MST_CTRL_MULTI_MST_EN  (1 << 7)    //!< Enable molti-master capability
#define MPU9250_I2C_MST_CTRL_WAIT_FOR_ES   (1 << 6)    //!< Delay data ready interrupt for external sensor data
#define MPU9250_I2C_MST_CTRL_SLV_3_FIFO_EN (1 << 4)    //!< Write EXT_SENS_DATA regusters for SLV3 to FIFO
#define MPU9250_I2C_MST_CTRL_I2C_MST_P_NSR (1 << 2)    //!< I2C master transition mode. 0 to restart, 1 to reset

#define MPU9250_I2C_MST_CTRL_CLK_MSK        0x07        //!< Mask for I2C clock in I2C_MST_CTRL register

/**
 * I2C Master clock frequencies
 * Used in the I2C_MST_CTRL register
 */
typedef enum {
    MPU9250_I2C_MST_CLK_348_KHZ = 0x00,
    MPU9250_I2C_MST_CLK_333_KHZ = 0x01,
    MPU9250_I2C_MST_CLK_320_KHZ = 0x02,
    MPU9250_I2C_MST_CLK_308_KHZ = 0x03,
    MPU9250_I2C_MST_CLK_296_KHZ = 0x04,
    MPU9250_I2C_MST_CLK_286_KHZ = 0x05,
    MPU9250_I2C_MST_CLK_276_KHZ = 0x06,
    MPU9250_I2C_MST_CLK_267_KHZ = 0x07,
    MPU9250_I2C_MST_CLK_258_KHZ = 0x08,
    MPU9250_I2C_MST_CLK_500_KHZ = 0x09,
    MPU9250_I2C_MST_CLK_471_KHZ = 0x0a,
    MPU9250_I2C_MST_CLK_444_KHZ = 0x0b,
    MPU9250_I2C_MST_CLK_421_KHZ = 0x0c,
    MPU9250_I2C_MST_CLK_400_KHZ = 0x0d,
    MPU9250_I2C_MST_CLK_381_KHZ = 0x0e,
    MPU9250_I2C_MST_CLK_364_KHZ = 0x0f
} mpu9250_i2c_mst_clk_e;

// User Control Register
#define MPU9250_USER_CTRL_FIFO_EN       (1 << 6)    //!< Enable FIFO operation mode
#define MPU9250_USER_CTRL_I2C_MST_EN    (1 << 5)    //!< Enable I2C master mode
#define MPU9250_USER_CTRL_I2C_IF_DIS    (1 << 4)    //!< Disable I2C master mode
#define MPU9250_USER_CTRL_FIFO_RST      (1 << 2)    //!< Reset FIFO module
#define MPU9250_USER_CTRL_I2C_MST_RST   (1 << 1)    //!< Reset I2C master module
#define MPU9250_USER_CTRL_SIG_COND_RST  (1 << 0)    //!< Reset all signal paths

// General configuration
#define MPU9250_REG_READ_FLAG       0x80
#define MPU9250_REG_WRITE_FLAG      0x00

#define MPU9250_PWR_MGMT_1_HRESET   (1 << 7)    //!< Power management reset flag

// I2C Slave control
#define MPU9250_I2C_SLV_CTRL_EN         (1 << 7)    //!< Enable an I2C slave 
#define MPU9250_I2C_SLV_CTRL_BYTE_SW    (1 << 6)    //!< Enable byte swapping on read
#define MPU9250_I2C_SLV_CTRL_REG_DIS    (1 << 5)    //!< Disable register setting (read/write data only)
#define MPU9250_I2C_SLV_CTRL_GRP        (1 << 4)    //!< Data grouping. 0 for 0 & 1, 1 for 1 & 2 

#define MPU9250_I2C_SLV_CTRL_LENG_SHIFT  0       //!< Shift for slave transfer length setting
#define MPU9250_I2C_SLV_CTRL_LENG_MASK   0x07    //!< Mask for slave transfer length setting

// Compass configuration
#define MPU9250_COMPASS_ADDR        0x0c    //!< Compass I2C address
#define MPU9250_COMPASS_ID          0x48    //!< Compass device ID (for device recognition)

#define MPU9250_COMPASS_READ_FLAG   0x80    //!< Read flag for the I2C compass
#define MPU9250_COMPASS_WRITE_FLAG  0x00    //!< Write flag for the I2C compass

#define MPU9250_COMPASS_CTL1_MODE_SHIFT  0       //!< Shift for compass mode setting
#define MPU9250_COMPASS_CTL1_MODE_MASK   0x0F    //!< Mask for compass mode setting
typedef enum {
    MPU9250_COMPASS_MODE_OFF            = 0x00,
    MPU9250_COMPASS_MODE_SINGLE         = 0x01,
    MPU9250_COMPASS_MODE_CONTINUOUS1    = 0x02,
    MPU9250_COMPASS_MODE_CONTINUOUS2    = 0x06,
    MPU9250_COMPASS_MODE_EXT_TRIGGER    = 0x04,
    MPU9250_COMPASS_MODE_SELF_TEST      = 0x08,
    MPU9250_COMPASS_MODE_FUSE_ROM       = 0x0F,
} mpu9250_compass_mode_e;

#define MPU9250_COMPASS_CTL1_OUTPUT_14BIT    (0 << 4)
#define MPU9250_COMPASS_CTL1_OUTPUT_16BIT    (1 << 4)

#define MPU9250_COMPASS_CTL2_RESET           (1 << 0)

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
