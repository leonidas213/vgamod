add_library(gof
gof.cpp
        
)

target_link_libraries(gof
pico_stdlib framebuffer
        )
target_include_directories (gof PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})