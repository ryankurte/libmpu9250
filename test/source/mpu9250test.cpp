

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <stdint.h>
#include <tuple>

#include "mpu9250.hpp"
#include "mpu9250_defs.h"
#include "mpu9250_regs.h"
#include "mock_spi.hpp"

using namespace MPU9250;
using namespace testing;

using ::testing::ElementsAre;
using ::testing::ElementsAreArray;

// The fixture for testing class Foo.
class Mpu9250Test : public ::testing::Test
{
protected:

  void SetUp()
  {
    mpu = Mpu9250();

    int res = mpu.init(&mockSpi);

    EXPECT_EQ(0, res);
  }

  void TearDown()
  {
    mpu.close();
  }

  MockSpi mockSpi;
  Mpu9250 mpu;
};

MATCHER_P2(MaskedCompare, value, mask, "")
{
  return (arg & mask) == value;
}

TEST_F(Mpu9250Test, FakeTest)
{
  // Expected, actual
  EXPECT_EQ(0, 0);
}

TEST_F(Mpu9250Test, SetGyroRate)
{
  int res;
  Sequence s1;

  uint8_t read_addr = MPU9250_REG_GYRO_CONFIG | MPU9250_REG_READ_FLAG;
  uint8_t write_addr = MPU9250_REG_GYRO_CONFIG | MPU9250_REG_WRITE_FLAG;
  uint8_t mock_read[] = {0x00, 0x00};
  uint8_t read_cmd[] = {read_addr, 0x00};
  uint8_t write_cmd[] = {write_addr, MPU9250_GYRO_SCALE_500DPS << MPU9250_GYRO_CONFIG_SCALE_SHIFT};


  res = mpu.set_gyro_scale(MPU9250_GYRO_SCALE_500DPS);

  EXPECT_EQ(0, res);
}



