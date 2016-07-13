# mpu9250-library

A Dependency Injection based SPI Driver library for the MPU9250 from InvenSense.  
This is a work in progress, see Status for more information.

## Status
- [X] Register operations
- [X] Initialisation
- [X] Polling 
- [ ] Filter Configuration
- [ ] Autonomous mode (free wheeling)
- [ ] Externally triggered mode

## Usage
Check out [mpu9250.h](lib/include/mpu9250.h) for the c language interface, or [mpu9250.hpp](lib/include/mpu9250.hpp) for the c++ language interface.  
A C++ adaptor is provided in [mpu9250_if.hpp](lib/include/mpu9250_if.hpp) to adapt between c++ driver objects and the underlying c implementation.  

For C use you will need to implement an SPI driver function with the prototype `int8_t spi_transfer(void* context, uint8_t len, uint8_t *data_out, uint8_t* data_in);`.  

For C++ use you can use the above function, or create an object extending `MPU9250::SpiDriverInterface` with the method `int spi_transfer(uint8_t len, uint8_t *data_out, uint8_t* data_in)`.  

Both of the above functions should return >= 0 for success, < 0 for failure.

------

If you have any questions, comments, or suggestions, feel free to open an issue or a pull request.
