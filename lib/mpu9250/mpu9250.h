/*
 * mpu9250 9-DOF IMU driver
 *
 * Copyright 2016 Ryan Kurte
 */

#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>

#include "mpu9250/mpu9250_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mpu9250_result_e {
    MPU9250_RES_OK = 0,
    MPU9250_DRIVER_INVALID = -1,
    MPU9250_DRIVER_ERROR = -2,
    MPU9250_COMMS_ERROR = -3
};

// SPI interaction function for dependency injection
typedef int (*spi_transfer_f)(void* context, int len, uint8_t *data_out, uint8_t* data_in);

// Driver object for passing in to MPU9250 object
struct mpu9250_driver_s {
    spi_transfer_f spi_transfer;    //!< SPI transfer function
};

/****       Initialization           ****/

// Create an mpu9250 device
// Note that the device and driver objects must continue to exist outside this scope.
int8_t mpu9250_init(struct mpu9250_s *device, struct mpu9250_driver_s *driver, void* driver_ctx);

// Close an mpu9250 device
int8_t mpu9250_close(struct mpu9250_s *device);


/****       Configuration           ****/
int mpu9250_set_gyro_scale(struct mpu9250_s *device, mpu9250_gyro_scale_e scale);
int mpu9250_set_accel_scale(struct mpu9250_s *device, mpu9250_accel_scale_e scale);

/****       Raw readings            ****/
int mpu9250_read_gyro_raw(struct mpu9250_s *device, int16_t *x, int16_t *y, int16_t *z);
int mpu9250_read_accel_raw(struct mpu9250_s *device, int16_t *x, int16_t *y, int16_t *z);
int mpu9250_read_temp_raw(struct mpu9250_s *device, int16_t *temp);

/****       Processed readings      ****/
int mpu9250_read_gyro(struct mpu9250_s *device, float *x, float *y, float *z);
int mpu9250_read_accel(struct mpu9250_s *device, float *x, float *y, float *z);
int mpu9250_read_temp(struct mpu9250_s *device, float* temp);



#ifdef __cplusplus
}
#endif

#endif
