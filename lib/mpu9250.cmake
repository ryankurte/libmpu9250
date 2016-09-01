# Libmpu9250 cmake include file

# Add library includes
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Add project sources
set(LIBMPU9250_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/source/mpu9250.c
)

# Create library
add_library(mpu9250 ${LIBMPU9250_SOURCES})

set(OPTIONAL_LIBS mpu9250 ${OPTIONAL_LIBS})
