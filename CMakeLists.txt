# cmake version
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
#set(PICO_BOARD pico_w)
# include the sdk.cmake file
include(pico_sdk_import.cmake)

# give the project a name (anything you want)
project(VgaDen C CXX ASM)

# initialize the sdk
pico_sdk_init()

#######

add_executable(VgaDen main.cpp

)
# name anything you want

# must match with executable name and source file names
pico_enable_stdio_uart(VgaDen 0)
pico_enable_stdio_usb(VgaDen 1)
add_subdirectory(FrameBuffer)
add_subdirectory(tetris)
add_subdirectory(GameOfLife)
add_subdirectory(Vga)
# must match with executable name
target_link_libraries(VgaDen pico_stdlib 
framebuffer 
tetris
gof
vga
pico_bootsel_via_double_reset
)

# must match with executable name
pico_add_extra_outputs(VgaDen)
