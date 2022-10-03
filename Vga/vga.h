#include "pico/stdlib.h"
#include "string.h"
#include "stdint.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hsync.pio.h"
#include "vsync.pio.h"
#include "rgb.pio.h"

#define H_ACTIVE 655
#define V_ACTIVE 479
#define RGB_ACTIVE 319
#define TXCOUNT 153600

class vga
{

public:
    vga(uint8_t hsync, uint8_t vsync, uint8_t redPin, uint8_t *buf = nullptr);
    void start();
private:

char *address_pointer=nullptr;

};