/**
 * Hunter Adams (vha3@cornell.edu)
 *
 * Mandelbrot set calculation and visualization
 * Uses PIO-assembly VGA driver
 *
 * HARDWARE CONNECTIONS
 *  - GPIO 16 ---> VGA Hsync
 *  - GPIO 17 ---> VGA Vsync
 *  - GPIO 18 ---> 330 ohm resistor ---> VGA Red
 *  - GPIO 19 ---> 330 ohm resistor ---> VGA Green
 *  - GPIO 20 ---> 330 ohm resistor ---> VGA Blue
 *  - RP2040 GND ---> VGA GND
 *
 * RESOURCES USED
 *  - PIO state machines 0, 1, and 2 on PIO instance 0
 *  - DMA channels 0 and 1
 *  - 153.6 kBytes of RAM (for pixel color data)
 *
 */
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "hardware/regs/rosc.h"
#include "hardware/regs/addressmap.h"

#include "FrameBuffer/FrameBuffer.h"
#include "pico/stdlib.h"
#include "tetris.h"
#include "gof.h"
#include "vga.h"

FrameBuffer buffer = FrameBuffer(640, 480, BufferType::rgbSingle);
#define HSYNC 2
#define VSYNC 3
#define RED_PIN 6
#define GREEN_PIN 7
#define BLUE_PIN 8
vga Vga = vga(HSYNC, VSYNC, RED_PIN, buffer.buffer, true);
void seed_random_from_rosc()
{
  uint32_t random = 0x811c9dc5;
  uint8_t next_byte = 0;
  volatile uint32_t *rnd_reg = (uint32_t *)(ROSC_BASE + ROSC_RANDOMBIT_OFFSET);

  for (int i = 0; i < 16; i++)
  {
    for (int k = 0; k < 8; k++)
    {
      next_byte = (next_byte << 1) | (*rnd_reg & 1);
    }

    random ^= next_byte;
    random *= 0x01000193;
  }

  srand(random);
}
int main()
{
  // Initialize stdio
  stdio_init_all();
  seed_random_from_rosc();
  //buffer.drawRect(0, 0, 80, 80, Colors::WHITE, Mode::draw);

  Vga.start();
  set_sys_clock_khz(160000, true);
  gof engine = gof(640, 480, &buffer, 5);
  //  engine.randomize();
   engine.gliderMaker(5, 5);

  printf("codeStarted");
  sleep_ms(5000);

  while (true)
  {

    engine.update();

    // tetris(&buffer);
  }
}
