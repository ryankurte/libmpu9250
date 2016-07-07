/*
 * mpu9250 related definitions for internal library use
 *
 */

#ifndef MPU9250_DEFS_H
#define MPU9250_DEFS_H

// MPU9250 object for internal use
struct mpu9250_s {
    int open;                           //!< Indicates whether the device is open
    struct mpu9250_driver_s* driver;    //!< Driver function object
};

#endif
