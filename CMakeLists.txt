cmake_minimum_required(VERSION 3.13)

include(../pico-sdk/external/pico_sdk_import.cmake)

project(myproject C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(router router.c)

# pull in common dependencies
target_link_libraries(router pico_stdlib hardware_rtc)

# create map/bin/hex file etc.
pico_add_extra_outputs(router)
