
#pragma once

#include "gmock/gmock.h"

#include <stdint.h>

#include "mpu9250_if.hpp"

class MockSpi : public MPU9250::SpiDriverInterface
{
public:
    MOCK_METHOD3(spi_transfer, int(int len, uint8_t* data_out, uint8_t *data_in));

};