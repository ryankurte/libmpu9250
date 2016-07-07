
#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>

#include "mpu9250_defs.h"

// SPI interaction function for dependency injection
typedef int8_t (*spi_transfer_f)(void* context, uint8_t *data_in, uint8_t* data_out, uint8_t len);

// Driver object for passing in to MPU9250 object
struct mpu9250_driver_s {
    spi_transfer_f spi_transfer;    //!< SPI transfer function
};

// Create an mpu9250 device
// Note that the device and driver objects must continue to exist outside this scope.
int8_t mpu9250_init(struct mpu9250_s *device, struct mpu9250_driver_s *driver, void* driver_ctx);

int mpu9250_set_gyro_scale(struct mpu9250_s *device, mpu9250_gyro_scale_e scale);
int mpu9250_set_accel_scale(struct mpu9250_s *device, mpu9250_accel_scale_e scale);

int mpu9250_read_gyro(struct mpu9250_s *device, uint16_t *x, uint16_t *y, uint16_t *z);
int mpu9250_read_accel(struct mpu9250_s *device, uint16_t *x, uint16_t *y, uint16_t *z);
int mpu9250_read_temp(struct mpu9250_s *device, uint16_t *temp);

// Close an mpu9250 device
int8_t mpu9250_close(struct mpu9250_s *device);

#endif
