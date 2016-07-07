/*
 * mpu9250 registers for internal library use
 *
 */

#ifndef REGISTERS_H
#define REGISTERS_H

// MPU9250 Register Enumeration
enum mpu9250_reg_e {

    // Self test registers
    REG_SELF_TEST_X_GYRO = 0x00,
    REG_SELF_TEST_Y_GYRO = 0x01,
    REG_SELF_TEST_Z_GYRO = 0x02,
    REG_SELF_TEST_X_ACCEL = 0x0D,
    REG_SELF_TEST_Y_ACCEL = 0x0E,
    REG_SELF_TEST_Z_ACCEL = 0x0F,

    // Gyro offset registers
    REG_XG_OFFSET_H = 0x13,
    REG_XG_OFFSET_L = 0x14,
    REG_YG_OFFSET_H = 0x15,
    REG_YG_OFFSET_L = 0x16,
    REG_ZG_OFFSET_H = 0x17,
    REG_ZG_OFFSET_L = 0x18,

    // Configuration Registers
    REG_SMPLRT_DIV = 0x19,      //!< Sample rate divisor (Internal_Sample_Rate / (1 + SMPLRT_DIV))
    REG_CONFIG = 0x1A,          //!< General Configuration
    REG_GYRO_CONFIG = 0x1B,     //!< Gyro configuration
    REG_ACCEL_CONFIG_1 = 0x1C,  //!< Accel configuration 1
    REG_ACCEL_CONFIG_2 = 0x1D,  //!< Accel configuration 2
    REG_LP_ACCEL_ODR = 0x1E,    //!< Low Power accel control
    REG_WOM_THR = 0x1F,         //!< Wake on Movement threshold
    REG_FIFO_EN = 0x23,         //!< FIFO output config, sets readings to be stored in fifo

    // I2C Slave configuration registers
    REG_I2C_MST_CTRL = 0x24,    //!< I2C Master control

    REG_I2C_SLV0_ADDR = 0x25,
    REG_I2C_SLV0_REG = 0x26,
    REG_I2C_SLV0_CTRL = 0x27,
    
    REG_I2C_SLV1_ADDR = 0x28,
    REG_I2C_SLV1_REG = 0x29,
    REG_I2C_SLV1_CTRL = 0x2A,
    
    REG_I2C_SLV2_ADDR = 0x2B,
    REG_I2C_SLV2_REG = 0x2C,
    REG_I2C_SLV2_CTRL = 0x2D,
    
    REG_I2C_SLV3_ADDR = 0x2E,
    REG_I2C_SLV3_REG = 0x2F,
    REG_I2C_SLV3_CTRL = 0x30,
    
    REG_I2C_SLV4_ADDR = 0x31,
    REG_I2C_SLV4_REG = 0x32,
    REG_I2C_SLV4_DO = 0x33,
    REG_I2C_SLV4_CTRL = 0x34,
    REG_I2C_SLV4_DI = 0x35,

    REG_I2C_MST_STATUS = 0x36,  //!< I2C Master Status

    // Interrupt control registers
    REG_INT_PIN_CFG = 0x37,     //!< Interrupt pin configuration
    REG_INT_ENABLE = 0x38,      //!< Interrupt Enable mask
    REG_INT_STATUS = 0x3A,      //!< Interrupt Status

    // Accelerator output registers
    REG_ACCEL_XOUT_H = 0x3B,
    REG_ACCEL_XOUT_L = 0x3C,
    REG_ACCEL_YOUT_H = 0x3D,
    REG_ACCEL_YOUT_L = 0x3E,
    REG_ACCEL_ZOUT_H = 0x3F,
    REG_ACCEL_ZOUT_L = 0x40,

    // Temperature output registers
    REG_TEMP_OUT_H = 0x41,
    REG_TEMP_OUT_L = 0x42,

    // Gyro output registers
    REG_GYRO_XOUT_H = 0x43,
    REG_GYRO_XOUT_L = 0x44,
    REG_GYRO_YOUT_H = 0x45,
    REG_GYRO_YOUT_L = 0x46,
    REG_GYRO_ZOUT_H = 0x47,
    REG_GYRO_ZOUT_L = 0x48,

    // External sensor output registers
    REG_EXT_SENS_DATA_00 = 0x49,
    REG_EXT_SENS_DATA_01 = 0x4A,
    REG_EXT_SENS_DATA_02 = 0x4B,
    REG_EXT_SENS_DATA_03 = 0x4C,
    REG_EXT_SENS_DATA_04 = 0x4D,
    REG_EXT_SENS_DATA_05 = 0x4E,
    REG_EXT_SENS_DATA_06 = 0x4F,
    REG_EXT_SENS_DATA_07 = 0x50,
    REG_EXT_SENS_DATA_08 = 0x51,
    REG_EXT_SENS_DATA_09 = 0x52,
    REG_EXT_SENS_DATA_10 = 0x53,
    REG_EXT_SENS_DATA_11 = 0x54,
    REG_EXT_SENS_DATA_12 = 0x55,
    REG_EXT_SENS_DATA_13 = 0x56,
    REG_EXT_SENS_DATA_14 = 0x57,
    REG_EXT_SENS_DATA_15 = 0x58,
    REG_EXT_SENS_DATA_16 = 0x59,
    REG_EXT_SENS_DATA_17 = 0x5A,
    REG_EXT_SENS_DATA_18 = 0x5B,
    REG_EXT_SENS_DATA_19 = 0x5C,
    REG_EXT_SENS_DATA_20 = 0x5D,
    REG_EXT_SENS_DATA_21 = 0x5E,
    REG_EXT_SENS_DATA_22 = 0x5F,
    REG_EXT_SENS_DATA_23 = 0x60,

    // I2C Slave Data Out
    REG_I2C_SLV0_DO = 0x63,
    REG_I2C_SLV1_DO = 0x64,
    REG_I2C_SLV2_DO = 0x65,
    REG_I2C_SLV3_DO = 0x66,

    // Configuration registers
    REG_I2C_MST_DELAY_CTRL = 0x67,  //!< I2C Master Delay Control
    REG_SIGNAL_PATH_RESET = 0x68,   //!< Signal Path Reset
    REG_MOT_DETECT_CTRL = 0x69,     //!< Motion Detect Control (see ACCEL_INTEL_CTRL)
    REG_USER_CTRL = 0x6A,           //!< User control, sets FIFO and I2C modes

    // Power management registers
    REG_PWR_MGMT_1 = 0x6B,          //!< Power management 1
    REG_PWR_MGMT_2 = 0x6C,          //!< Power management 2

    // FIFO status registers
    REG_FIFO_COUNTH = 0x72,         //!< Current fifo count, high byte
    REG_FIFO_COUNTL = 0x73,         //!< Current fifo count, low byte
    REG_FIFO_R_W = 0x74,            //!< Register to read/write from/to the FIFO

    REG_WHO_AM_I = 0x75,            //!< Device ID check, always 0x71

    // Accelerometer offsets
    // Full scale compensation: 15 bit 0.98-mg steps
    REG_XA_OFFSET_H = 0x77,
    REG_XA_OFFSET_L = 0x78,
    REG_YA_OFFSET_H = 0x7A,
    REG_YA_OFFSET_L = 0x7B,
    REG_ZA_OFFSET_H = 0x7D,
    REG_ZA_OFFSET_L = 0x7E

};

#endif

