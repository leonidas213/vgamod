#include "gof.h"

gof::gof(int width, int height, FrameBuffer *buffer, int cellsize)
{

    this->width = width / cellsize;
    this->height = height / cellsize;
    this->cellsize = cellsize;
    this->buffer = buffer;
    cells = new int8_t[76800];
}
void gof::glider(int xpos, int ypos, int rot)
{
    int spoint = 0;
    switch (rot)
    {
    case 1:
        spoint = 3;
        break;
    case 2:
        spoint = 6;
        break;
    case 3:
        spoint = 9;
        break;

    default:
        spoint = 0;
        break;
    }
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (gliderArr[x+spoint] & (1 << y))
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        buffer->setPixel(xpos + (x * cellsize) + i, ypos + (y * cellsize) + j, color);
                    }
                }
            }
        }
    }
}

void gof::randomize()

{
    this->color = (Colors)(rand() % 7);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            Colors newcolor = rand() % 2 ? color : Colors::BLACK;
            if (rand() % 8 > 2)
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        buffer->setPixel(x * cellsize + i, y * cellsize + j, newcolor);
                    }
                }
            }
        }
    }
}
void gof::update()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int neighbours = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (i == 0 && j == 0)
                        continue;
                    if (x + i < 0 || x + i >= width || y + j < 0 || y + j >= height)
                        continue;
                    if (buffer->getPixel((x + i) * cellsize, (y + j) * cellsize) != (int)Colors::BLACK)
                        neighbours++;
                }
            }
            if (buffer->getPixel(x * cellsize, y * cellsize) != (int)Colors::BLACK)
            {
                if (neighbours < 2 || neighbours > 3)
                {
                    cells[x + y * width] = -1;
                    /* for (int i = 0; i < cellsize; i++)
                     {
                         for (int j = 0; j < cellsize; j++)
                         {
                             //buffer->setPixel(x * cellsize + i, y * cellsize + j, Colors::BLACK, Mode::replace);
                         }
                     }*/
                }
            }
            else
            {
                if (neighbours == 3)
                {
                    cells[x + y * width] = 1;
                    /*for (int i = 0; i < cellsize; i++)
                    {
                        for (int j = 0; j < cellsize; j++)
                        {
                            buffer->setPixel(x * cellsize + i, y * cellsize + j, this->color, Mode::replace);
                        }
                    }*/
                }
                else
                {
                    cells[x + y * width] = -1;
                    /*for (int i = 0; i < cellsize; i++)
                    {
                        for (int j = 0; j < cellsize; j++)
                        {
                            buffer->setPixel(x * cellsize + i, y * cellsize + j, Colors::BLACK, Mode::replace);
                        }
                    }*/
                }
            }
        }
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (cells[x + y * width] == 1)
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        cells[x + y * width] = 0;
                        buffer->setPixel(x * cellsize + i, y * cellsize + j, this->color, Mode::replace);
                    }
                }
            }
            else if (cells[x + y * width] == -1)
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        cells[x + y * width] = 0;
                        buffer->setPixel(x * cellsize + i, y * cellsize + j, Colors::BLACK, Mode::replace);
                    }
                }
            }
        }
    }
}
