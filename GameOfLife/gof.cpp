#include "gof.h"

gof::gof(int width, int height, FrameBuffer *buffer, int cellsize)
{

    this->width = width / cellsize;
    this->height = height / cellsize;
    this->cellsize = cellsize;
    this->buffer = buffer;
    cells = new int8_t[this->width * this->height];
    memset(cells, 0, this->width * this->height);
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
            if (gliderArr[x + spoint] & (1 << y))
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        buffer->setPixel((xpos * cellsize) + (x * cellsize) + i, (ypos * cellsize) + (y * cellsize) + j, color);
                    }
                }
                this->cells[(xpos + x) + (ypos + y) * this->width] = 1;
            }
        }
    }
}
void gof::gliderRandom(int count)
{
    for (int r = 0; r < count; r++)
    {
        glider(rand() % (width - 3), rand() % (height - 3), rand() % 4);
    }
}
void gof::randomize()
{
    this->gliderRandom(rand() % 15);
    this->squareRandom(rand() % 15);
}
void gof::squareRandom(int count)
{
    for (int r = 0; r < count; r++)
    {
        int x = rand() % (width - 3);
        int y = rand() % (height - 3);
        this->square(x, y);
    }
}
void gof::square(int x, int y)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < cellsize; k++)
            {
                for (int l = 0; l < cellsize; l++)
                {
                    buffer->setPixel((x * cellsize) + (i * cellsize) + k, (y * cellsize) + (j * cellsize) + l, color);
                }
            }
            this->cells[(x + i) + (y + j) * this->width] = 1;
        }
    }
}
void gof::gliderMaker(int x, int y)
{
    int posx = x + 11;
    this->square(x+1, y + 2);
    this->square(x+35, y + 5);
    for (int y2 = 0; y2 < 9; y2++)
    {
        for (int x2 = 0; x2 < 17; x2++)
        {
            if (gliderMakerArr[y2] & (1 << x2))
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        buffer->setPixel((posx * cellsize) + (x2 * cellsize) + i, (y * cellsize) + (y2 * cellsize) + j, color);
                    }
                }
                this->cells[(posx + x2) + (y + y2) * this->width] = 1;
            }
        }
    }
}
/*void gof::update()
{

    int8_t cpy[width][height];
    memcpy(cpy, this->cells, width * height * sizeof(int8_t));

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int NORTH = (height + j - 1) % height;
            int SOUTH = (height + j + 1) % height;

            int EAST = (width + i + 1) % width;
            int WEST = (width + i - 1) % width;

            int neighbours =
                this->cells[EAST][NORTH] + this->cells[WEST][NORTH] +
                this->cells[EAST][SOUTH] + this->cells[WEST][SOUTH] +
                this->cells[i][SOUTH] + this->cells[i][NORTH] +
                this->cells[EAST][j] + this->cells[WEST][j];

            if (neighbours < 2 || neighbours > 3)
                if (cpy[i][j])
                    cpy[i][j] = -1;

            if (neighbours == 3)
                cpy[i][j] = 1;
        }
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (cpy[x][y] == 1)
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        buffer->setPixel(x * cellsize + i, y * cellsize + j, color);
                    }
                }
            }
            else if (cpy[x][y] == -1)
            {
                for (int i = 0; i < cellsize; i++)
                {
                    for (int j = 0; j < cellsize; j++)
                    {
                        buffer->setPixel(x * cellsize + i, y * cellsize + j, Colors::BLACK);
                    }
                }
                cpy[x][y] = 0;
            }
        }
    }

    memcpy(this->cells, cpy, width * height * sizeof(int8_t));
}
*/
void gof::update()
{
    int8_t newarr[width * height];
    memset(newarr, 0, width * height * sizeof(int8_t));
    memcpy(newarr, this->cells, width * height * sizeof(int8_t));
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
                    {

                        int newx = (x + i) < 0 ? (x + i) + width : (x + i) % width;
                        int newy = (y + j) < 0 ? (y + j) + height : (y + j) % height;

                        if (newarr[newx + newy * width])
                            neighbours++;
                        printf("x: %d, y: %d, i: %d, j: %d \n", x, y, i, j);
                        printf("newx: %d, newy: %d \n", (x + i) % width, (y + j) % height);
                        continue;
                    }

                    if (newarr[((x + i)) + ((y + j)) * width])
                        neighbours++;
                }
            }
            if (newarr[(x) + (y)*width])
            {
                if (neighbours < 2 || neighbours > 3)
                {
                    cells[x + y * width] = -1;
                }
            }
            else
            {
                if (neighbours == 3)
                {
                    cells[x + y * width] = 1;
                }
            }
        }
    }
    printf("time to draw");
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
                        newarr[x + y * width] = 1;
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
                        newarr[x + y * width] = 0;
                        buffer->setPixel(x * cellsize + i, y * cellsize + j, Colors::BLACK, Mode::replace);
                    }
                }
            }
        }
    }
    printf("time to cpy");
    memcpy(this->cells, newarr, width * height * sizeof(int8_t));
}
