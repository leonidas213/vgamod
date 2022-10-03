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
#include "FrameBuffer/FrameBuffer.h"
#include "pico/stdlib.h"
#include "tetris.h"
#include "gof.h"
#include "vga.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// Stuff for Mandelbrot ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// Fixed point data type
typedef signed int fix28;
#define multfix28(a, b) ((fix28)((((signed long long)(a)) * ((signed long long)(b))) >> 28))
#define float2fix28(a) ((fix28)((a)*268435456.0f)) // 2^28
#define fix2float28(a) ((float)(a) / 268435456.0f)
#define int2fix28(a) ((a) << 28)
// the fixed point value 4
#define FOURfix28 0x40000000
#define SIXTEENTHfix28 0x01000000
#define ONEfix28 0x10000000

// Maximum number of iterations
#define max_count 1000

// Mandelbrot values
fix28 Zre, Zim, Cre, Cim;
fix28 Zre_sq, Zim_sq;

int i, j, count, total_count;

fix28 x[640];
fix28 y[480];

FrameBuffer buffer = FrameBuffer(640, 480, BufferType::rgbSingle);
////////////////////////////////////////////////////////////////////////////////////////////////////
#define HSYNC 10
#define VSYNC 9
#define RED_PIN 6
#define GREEN_PIN 7
#define BLUE_PIN 8
vga Vga=vga(HSYNC,VSYNC,RED_PIN,buffer.buffer);
int main()
{
    // Initialize stdio
    stdio_init_all();

    Vga.start();

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // ===================================== Mandelbrot =================================================
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    uint64_t begin_time;
    uint64_t end_time;
    // memset(vga_data_array, 0, TXCOUNT);
    gof engine = gof(640, 480, &buffer, 4);

    for (int r = 0; r < 100; r++)
    {
        engine.glider(rand() % 640, rand() % 480, rand() % 5);
    }

    // engine.randomize();
    //  buffer.fillCircle(320, 240, 100, Colors::WHITE);
    sleep_ms(5000);
    // buffer.drawCircle(320, 240, 100, Colors::WHITE);
    while (true)
    {

        // buffer.clear();
        engine.update();
        // printf("buff\n");
        //  buffer.fillRect(20, 20, 30, 30, Colors::WHITE);
        // printf("%d\n", buffer.getPixel(25, 25));
        //  sleep_ms(800);
        //
        /*
        int size = 5;
        int a = 0;
        for (int i = 0; i < buffer.width / size; i++)
        {
            for (int j = 0; j < buffer.height / size; j++)
            {
                for (int y = 0; y < size; y++)
                {
                    for (int x = 0; x < size; x++)
                    {
                        // buffer.setPixel(i * size + y, j * size + x, (Colors)a);
                    }
                }
                a = rand() % 8;
                if (a > 7)
                    a = 0;
            }
        }*/
        // buffer.addBitmapImage(0,0,640,480,&image[0]);

        // tetris(&buffer);
        /*
                for (i = 0; i < 640; i++)
                {
                    x[i] = float2fix28(-2.0f + (3.0f ) * (float)i / 640.0f);
                }

                // y values
                for (j = 0; j < 480; j++)
                {
                    y[j] = float2fix28(1.0f - (2.0f ) * (float)j / 480.0f);
                }

                total_count = 0;
                fix28 center = float2fix28(-0.25f);
                fix28 radius2 = float2fix28(0.25f);
                for (i = 0; i < 640; i++)
                {

                    for (j = 0; j < 480; j++)
                    {

                        Zre = Zre_sq = Zim = Zim_sq = 0;

                        Cre = x[i];
                        Cim = y[j];

                        // detect secondary bulb
                        // if ((multfix28(Cre+ONEfix28,Cre+ONEfix28)+multfix28(Cim,Cim))<SIXTEENTHfix28) {
                        //     count=max_count;
                        // }
                        // // detect big circle
                        // else if ((multfix28(Cre-center,Cre-center)+multfix28(Cim,Cim))<radius2) {
                        //     count=max_count;
                        // }
                        // // otherwise get ready to iterate
                        // else count = 0;
                        count = 0;

                        // Mandelbrot iteration
                        while (count++ < max_count)
                        {
                            Zim = (multfix28(Zre, Zim) << 1) + Cim;
                            Zre = Zre_sq - Zim_sq + Cre;
                            Zre_sq = multfix28(Zre, Zre);
                            Zim_sq = multfix28(Zim, Zim);

                            if ((Zre_sq + Zim_sq) >= FOURfix28)
                                break;
                        }
                        // Increment total count
                        total_count += count;

                        // Draw the pixel
                        if (count >= max_count)
                            buffer.setPixel(i, j, Colors::BLACK);
                        else if (count >= (max_count >> 1))
                            buffer.setPixel(i, j, Colors::WHITE);
                        else if (count >= (max_count >> 2))
                            buffer.setPixel(i, j, Colors::CYAN);
                        else if (count >= (max_count >> 3))
                            buffer.setPixel(i, j, Colors::BLUE);
                        else if (count >= (max_count >> 4))
                            buffer.setPixel(i, j, Colors::RED);
                        else if (count >= (max_count >> 5))
                            buffer.setPixel(i, j, Colors::YELLOW);
                        else if (count >= (max_count >> 6))
                            buffer.setPixel(i, j, Colors::MAGENTA);
                        else
                            buffer.setPixel(i, j, Colors::RED);
                    }
                }

                end_time = time_us_64();
                printf("Total time: %3.6f seconds \n", (float)(end_time - begin_time) * (1. / 1000000.));
                printf("Total iterations: %d", total_count);
                sleep_ms(1000);*/
        // buffer.clear();
    }
}