#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "FrameBuffer.h"
class gof
{

public:
    gof(int width, int height, FrameBuffer *buffer, int cellsize = 3);
    void randomize();
    void update();
    void glider(int x, int y, int rot);
    uint8_t *get();
    int width, height, cellsize;
    Colors color = Colors::WHITE;

private:
    FrameBuffer *buffer;
    int8_t *cells;
    uint8_t gliderArr[12] = {

        0b00100000,
        0b01000000,
        0b01110000,
        //
        0b00100000,
        0b00010000,
        0b01110000,
        //
        0b01110000,
        0b00010000,
        0b00100000,
        //
        0b01110000,
        0b01000000,
        0b00100000,
    };
};