
#ifndef MPU9250_H
#define MPU9250_h

#include <stdint.h>

// SPI interaction function for dependency injection
typedef int8_t (*spi_transfer_f)(void* context, uint8_t *data_in, uint8_t* data_out, uint8_t len);

// Driver object for passing in to MPU9250 object
struct mpu9250_driver_s {
    spi_transfer_f spi_transfer;    //!< SPI transfer function
};

// Create an mpu9250 device
// Note that the device and driver objects must continue to exist outside this scope.
int8_t mpu9250_init(struct mpu9250_s *device, struct mpu9250_driver_s *driver, void* driver_ctx);

// Close an mpu9250 device
int8_t mpu9250_close(struct mpu9250_s *device);

#endif
