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
    void gliderRandom(int);
    void square(int x, int y);
    void squareRandom(int count);
    void gliderMaker(int x, int y);
    void gliderMakerRandom(int count);
    uint8_t *get();
    int width, height, cellsize;
    Colors color = Colors::YELLOW;

private:
    FrameBuffer *buffer;
    int8_t *cells;
    const uint8_t gliderArr[12] = {

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
    const uint16_t gliderMakerArr[9]={
        0b0000000000000010,
        0b0000000000001010,
        0b0011000000110000,
        0b0100010000110000,
        0b1000001000110000,
        0b1000101100001010,
        0b1000001000000010,
        0b0100010000000000,
        0b0011000000000000,

    };
};