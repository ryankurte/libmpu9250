
#ifndef MPU9250_H
#define MPU9250_h

#include <stdint.h>

// SPI interaction function for dependency injection
typedef int8_t (*spi_transfer_f)(void* context, uint8_t *data_in, uint8_t* data_out, uint8_t len);

// Driver object for passing in to MPU9250 object
struct mpu9250_driver_s {
    spi_transfer_f spi_transfer;    //!< SPI transfer function
    void* spi_ctx;                  //!< SPI transfer function context
};




#endif
