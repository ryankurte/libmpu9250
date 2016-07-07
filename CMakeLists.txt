

# Set minimum CMake version
cmake_minimum_required(VERSION 2.8.4)
include(ExternalProject)

##### Project Setup #####

# Set our output target
set(TARGET mpu9250test)

# Configure project and languages
project(${TARGET} C CXX ASM)

set(CMAKE_C_FLAGS "-std=gnu11 -g")
set(CMAKE_CXX_FLAGS "-std=gnu++11 -g")

# Set build type
set(CMAKE_BUILD_TYPE DEBUG)

# Fetch and build google test
ExternalProject_Add(googletest
    GIT_REPOSITORY git@github.com:google/googletest.git
    INSTALL_COMMAND echo "Skipping install"
    )

ExternalProject_Get_Property(googletest BINARY_DIR)
link_directories(${BINARY_DIR}/googlemock)
ExternalProject_Get_Property(googletest SOURCE_DIR)
include_directories(${SOURCE_DIR}/googlemock/include)

##### Modules #####

include(${PROJECT_SOURCE_DIR}/lib/mpu9250.cmake)
#add_subdirectory(${PROJECT_SOURCE_DIR}/modules/googletest/googlemock)

##### Files #####

# Add project headers
include_directories(${PROJECT_SOURCE_DIR}/test/include)

# Add project sources
set(TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/test/source/main.cpp
    ${PROJECT_SOURCE_DIR}/test/source/mpu9250test.cpp
)

##### Pre Build #####
add_custom_target(version ${PROJECT_SOURCE_DIR}/version.py LIBMPU9250 ${CMAKE_BINARY_DIR}/version.h)
include_directories(${CMAKE_BINARY_DIR})

##### Outputs #####

# Generate executable and link
add_executable(${TARGET} ${TEST_SOURCES})
target_link_libraries(${TARGET} ${OPTIONAL_LIBS} pthread gmock)
add_dependencies(${TARGET} googletest version)

##### Testing #####
add_custom_target(tests COMMAND ${TARGET})
