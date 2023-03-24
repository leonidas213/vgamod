add_library(tetris
tetris.cpp
        
)

target_link_libraries(tetris
pico_stdlib framebuffer
        hardware_timer
        )
target_include_directories (tetris PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})