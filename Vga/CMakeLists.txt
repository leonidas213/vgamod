add_library(vga
vga.cpp
        
)
pico_generate_pio_header(vga ${CMAKE_CURRENT_LIST_DIR}/hsync.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})
pico_generate_pio_header(vga ${CMAKE_CURRENT_LIST_DIR}/vsync.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})
pico_generate_pio_header(vga ${CMAKE_CURRENT_LIST_DIR}/rgb.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})
pico_generate_pio_header(vga ${CMAKE_CURRENT_LIST_DIR}/mono.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(vga
pico_stdlib
hardware_pio 
hardware_dma 
        )
target_include_directories (vga PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})