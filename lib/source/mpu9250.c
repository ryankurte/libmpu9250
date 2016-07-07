

#include "mpu9250.h"

#include <stdint.h>

int8_t mpu9250_init(struct mpu9250_s *device, struct mpu9250_driver_s *driver, void* driver_ctx)
{
    // Check driver functions exist
    if(driver->spi_transfer == NULL) {
        return -1;
    }
    
    // Save driver pointers
    device->driver = driver;
    device->driver_ctx = driver_ctx;
    
    // TODO: init
    
    return 0;
}

int8_t mpu9250_close(struct mpu9250_s *device)
{
    // TODO: shutdown
    
    // Clear driver pointer
    device->driver = NULL;
    
    return 0;
}

