#include "tetris.h"

//#ifndef Debug
//#define Debug
//#endif

Piece::Piece(int type, int x, int y, int rotation)
{
    this->pieceType = type;
    this->x = x;
    this->y = y;
    this->rotation = rotation;
    switch (type)
    {
    case 0:
        this->piece[0][0] = 0b00000000;
        this->piece[0][1] = 0b00111100;
        this->piece[0][2] = 0b00000000;
        this->piece[0][3] = 0b00000000;

        this->piece[1][0] = 0b00001000;
        this->piece[1][1] = 0b00001000;
        this->piece[1][2] = 0b00001000;
        this->piece[1][3] = 0b00001000;

        this->piece[2][0] = 0b00000000;
        this->piece[2][1] = 0b00000000;
        this->piece[2][2] = 0b00111100;
        this->piece[2][3] = 0b00000000;

        this->piece[3][0] = 0b00010000;
        this->piece[3][1] = 0b00010000;
        this->piece[3][2] = 0b00010000;
        this->piece[3][3] = 0b00010000;
        // aşşağı +y sol +x
        // I1 CW
        rotationRules[0][0] = {2, 0};
        rotationRules[0][1] = {-1, 0};
        rotationRules[0][2] = {2, 1};
        rotationRules[0][3] = {-1, -2};
        // I2 CW
        rotationRules[1][0] = {1, 0};
        rotationRules[1][1] = {-2, 0};
        rotationRules[1][2] = {1, -2};
        rotationRules[1][3] = {-2, 1};
        // I3 CW
        rotationRules[2][0] = {-2, 0};
        rotationRules[2][1] = {1, 0};
        rotationRules[2][2] = {-2, -1};
        rotationRules[2][3] = {1, 2};
        // I4 CW
        rotationRules[3][0] = {-1, 0};
        rotationRules[3][1] = {2, 0};
        rotationRules[3][2] = {-1, 2};
        rotationRules[3][3] = {2, -1};
        // I4 ACW
        rotationRules[4][0] = {2, 0};
        rotationRules[4][1] = {-1, 0};
        rotationRules[4][2] = {2, 1};
        rotationRules[4][3] = {-1, -2};
        // I3 ACW
        rotationRules[5][0] = {-1, 0};
        rotationRules[5][1] = {2, 0};
        rotationRules[5][2] = {-1, 2};
        rotationRules[5][3] = {2, -1};
        // I2 ACW
        rotationRules[6][0] = {-2, 0};
        rotationRules[6][1] = {1, 0};
        rotationRules[6][2] = {-2, -1};
        rotationRules[6][3] = {1, 2};
        // I1 ACW
        rotationRules[7][0] = {1, 0};
        rotationRules[7][1] = {-2, 0};
        rotationRules[7][2] = {1, -2};
        rotationRules[7][3] = {-2, 1};

        break;
    case 1:
        this->piece[0][0] = 0b00000000;
        this->piece[0][1] = 0b00100000;
        this->piece[0][2] = 0b00111000;
        this->piece[0][3] = 0b00000000;

        this->piece[1][0] = 0b00000000;
        this->piece[1][1] = 0b00011000;
        this->piece[1][2] = 0b00010000;
        this->piece[1][3] = 0b00010000;

        this->piece[2][0] = 0b00000000;
        this->piece[2][1] = 0b00000000;
        this->piece[2][2] = 0b00111000;
        this->piece[2][3] = 0b00001000;

        this->piece[3][0] = 0b00000000;
        this->piece[3][1] = 0b00010000;
        this->piece[3][2] = 0b00010000;
        this->piece[3][3] = 0b00110000;

        // aşşağı +y sol +x
        // I1 CW
        rotationRules[0][0] = {1, 0};
        rotationRules[0][1] = {1, -1};
        rotationRules[0][2] = {0, 2};
        rotationRules[0][3] = {1, 2};
        // I2 CW
        rotationRules[1][0] = {-1, 0};
        rotationRules[1][1] = {-1, 1};
        rotationRules[1][2] = {0, -2};
        rotationRules[1][3] = {-1, -2};
        // I3 CW
        rotationRules[2][0] = {-1, 0};
        rotationRules[2][1] = {-1, -1};
        rotationRules[2][2] = {0, 2};
        rotationRules[2][3] = {-1, 2};
        // I4 CW
        rotationRules[3][0] = {1, 0};
        rotationRules[3][1] = {1, 1};
        rotationRules[3][2] = {0, -2};
        rotationRules[3][3] = {1, -2};
        // I4 ACW
        rotationRules[4][0] = {1, 0};
        rotationRules[4][1] = {1, 1};
        rotationRules[4][2] = {0, -2};
        rotationRules[4][3] = {1, -2};
        // I3 ACW
        rotationRules[5][0] = {1, 0};
        rotationRules[5][1] = {1, -1};
        rotationRules[5][2] = {0, 2};
        rotationRules[5][3] = {1, 2};
        // I2 ACW
        rotationRules[6][0] = {-1, 0};
        rotationRules[6][1] = {-1, 1};
        rotationRules[6][2] = {0, -2};
        rotationRules[6][3] = {-1, -2};
        // I1 ACW
        rotationRules[7][0] = {-1, 0};
        rotationRules[7][1] = {-1, -1};
        rotationRules[7][2] = {0, 2};
        rotationRules[7][3] = {-1, 2};

        break;
    case 2:
        this->piece[0][0] = 0b00000000;
        this->piece[0][1] = 0b00001000;
        this->piece[0][2] = 0b00111000;
        this->piece[0][3] = 0b00000000;

        this->piece[1][0] = 0b00000000;
        this->piece[1][1] = 0b00010000;
        this->piece[1][2] = 0b00010000;
        this->piece[1][3] = 0b00011000;

        this->piece[2][0] = 0b00000000;
        this->piece[2][1] = 0b00000000;
        this->piece[2][2] = 0b00111000;
        this->piece[2][3] = 0b00100000;

        this->piece[3][0] = 0b00000000;
        this->piece[3][1] = 0b00110000;
        this->piece[3][2] = 0b00010000;
        this->piece[3][3] = 0b00010000;

        // aşşağı +y sol +x
        // I1 CW
        rotationRules[0][0] = {1, 0};
        rotationRules[0][1] = {1, -1};
        rotationRules[0][2] = {0, 2};
        rotationRules[0][3] = {1, 2};
        // I2 CW
        rotationRules[1][0] = {-1, 0};
        rotationRules[1][1] = {-1, 1};
        rotationRules[1][2] = {0, -2};
        rotationRules[1][3] = {-1, -2};
        // I3 CW
        rotationRules[2][0] = {-1, 0};
        rotationRules[2][1] = {-1, -1};
        rotationRules[2][2] = {0, 2};
        rotationRules[2][3] = {-1, 2};
        // I4 CW
        rotationRules[3][0] = {1, 0};
        rotationRules[3][1] = {1, 1};
        rotationRules[3][2] = {0, -2};
        rotationRules[3][3] = {1, -2};
        // I4 ACW
        rotationRules[4][0] = {1, 0};
        rotationRules[4][1] = {1, 1};
        rotationRules[4][2] = {0, -2};
        rotationRules[4][3] = {1, -2};
        // I3 ACW
        rotationRules[5][0] = {1, 0};
        rotationRules[5][1] = {1, -1};
        rotationRules[5][2] = {0, 2};
        rotationRules[5][3] = {1, 2};
        // I2 ACW
        rotationRules[6][0] = {-1, 0};
        rotationRules[6][1] = {-1, 1};
        rotationRules[6][2] = {0, -2};
        rotationRules[6][3] = {-1, -2};
        // I1 ACW
        rotationRules[7][0] = {-1, 0};
        rotationRules[7][1] = {-1, -1};
        rotationRules[7][2] = {0, 2};
        rotationRules[7][3] = {-1, 2};
        break;
    case 3:
        this->piece[0][0] = 0b00000000;
        this->piece[0][1] = 0b00011000;
        this->piece[0][2] = 0b00011000;
        this->piece[0][3] = 0b00000000;

        this->piece[1][0] = 0b00000000;
        this->piece[1][1] = 0b00011000;
        this->piece[1][2] = 0b00011000;
        this->piece[1][3] = 0b00000000;

        this->piece[2][0] = 0b00000000;
        this->piece[2][1] = 0b00011000;
        this->piece[2][2] = 0b00011000;
        this->piece[2][3] = 0b00000000;

        this->piece[3][0] = 0b00000000;
        this->piece[3][1] = 0b00011000;
        this->piece[3][2] = 0b00011000;
        this->piece[3][3] = 0b00000000;

        break;
    case 4:
        this->piece[0][0] = 0b00000000;
        this->piece[0][1] = 0b00011000;
        this->piece[0][2] = 0b00110000;
        this->piece[0][3] = 0b00000000;

        this->piece[1][0] = 0b00000000;
        this->piece[1][1] = 0b00010000;
        this->piece[1][2] = 0b00011000;
        this->piece[1][3] = 0b00001000;

        this->piece[2][0] = 0b00000000;
        this->piece[2][1] = 0b00000000;
        this->piece[2][2] = 0b00011000;
        this->piece[2][3] = 0b00110000;

        this->piece[3][0] = 0b00000000;
        this->piece[3][1] = 0b00100000;
        this->piece[3][2] = 0b00110000;
        this->piece[3][3] = 0b00010000;

        // aşşağı +y sol +x
        // I1 CW
        rotationRules[0][0] = {1, 0};
        rotationRules[0][1] = {1, -1};
        rotationRules[0][2] = {0, 2};
        rotationRules[0][3] = {1, 2};
        // I2 CW
        rotationRules[1][0] = {-1, 0};
        rotationRules[1][1] = {-1, 1};
        rotationRules[1][2] = {0, -2};
        rotationRules[1][3] = {-1, -2};
        // I3 CW
        rotationRules[2][0] = {-1, 0};
        rotationRules[2][1] = {-1, -1};
        rotationRules[2][2] = {0, 2};
        rotationRules[2][3] = {-1, 2};
        // I4 CW
        rotationRules[3][0] = {1, 0};
        rotationRules[3][1] = {1, 1};
        rotationRules[3][2] = {0, -2};
        rotationRules[3][3] = {1, -2};
        // I4 ACW
        rotationRules[4][0] = {1, 0};
        rotationRules[4][1] = {1, 1};
        rotationRules[4][2] = {0, -2};
        rotationRules[4][3] = {1, -2};
        // I3 ACW
        rotationRules[5][0] = {1, 0};
        rotationRules[5][1] = {1, -1};
        rotationRules[5][2] = {0, 2};
        rotationRules[5][3] = {1, 2};
        // I2 ACW
        rotationRules[6][0] = {-1, 0};
        rotationRules[6][1] = {-1, 1};
        rotationRules[6][2] = {0, -2};
        rotationRules[6][3] = {-1, -2};
        // I1 ACW
        rotationRules[7][0] = {-1, 0};
        rotationRules[7][1] = {-1, -1};
        rotationRules[7][2] = {0, 2};
        rotationRules[7][3] = {-1, 2};
        break;
    case 5:
        this->piece[0][0] = 0b00000000;
        this->piece[0][1] = 0b00110000;
        this->piece[0][2] = 0b00011000;
        this->piece[0][3] = 0b00000000;

        this->piece[1][0] = 0b00000000;
        this->piece[1][1] = 0b00001000;
        this->piece[1][2] = 0b00011000;
        this->piece[1][3] = 0b00010000;

        this->piece[2][0] = 0b00000000;
        this->piece[2][1] = 0b00000000;
        this->piece[2][2] = 0b00110000;
        this->piece[2][3] = 0b00011000;

        this->piece[3][0] = 0b00000000;
        this->piece[3][1] = 0b00010000;
        this->piece[3][2] = 0b00110000;
        this->piece[3][3] = 0b00100000;

        // aşşağı +y sol +x
        // I1 CW
        rotationRules[0][0] = {1, 0};
        rotationRules[0][1] = {1, -1};
        rotationRules[0][2] = {0, 2};
        rotationRules[0][3] = {1, 2};
        // I2 CW
        rotationRules[1][0] = {-1, 0};
        rotationRules[1][1] = {-1, 1};
        rotationRules[1][2] = {0, -2};
        rotationRules[1][3] = {-1, -2};
        // I3 CW
        rotationRules[2][0] = {-1, 0};
        rotationRules[2][1] = {-1, -1};
        rotationRules[2][2] = {0, 2};
        rotationRules[2][3] = {-1, 2};
        // I4 CW
        rotationRules[3][0] = {1, 0};
        rotationRules[3][1] = {1, 1};
        rotationRules[3][2] = {0, -2};
        rotationRules[3][3] = {1, -2};
        // I4 ACW
        rotationRules[4][0] = {1, 0};
        rotationRules[4][1] = {1, 1};
        rotationRules[4][2] = {0, -2};
        rotationRules[4][3] = {1, -2};
        // I3 ACW
        rotationRules[5][0] = {1, 0};
        rotationRules[5][1] = {1, -1};
        rotationRules[5][2] = {0, 2};
        rotationRules[5][3] = {1, 2};
        // I2 ACW
        rotationRules[6][0] = {-1, 0};
        rotationRules[6][1] = {-1, 1};
        rotationRules[6][2] = {0, -2};
        rotationRules[6][3] = {-1, -2};
        // I1 ACW
        rotationRules[7][0] = {-1, 0};
        rotationRules[7][1] = {-1, -1};
        rotationRules[7][2] = {0, 2};
        rotationRules[7][3] = {-1, 2};
        break;
    case 6:
        this->piece[0][0] = 0b00000000;
        this->piece[0][1] = 0b00010000;
        this->piece[0][2] = 0b00111000;
        this->piece[0][3] = 0b00000000;

        this->piece[1][0] = 0b00000000;
        this->piece[1][1] = 0b00010000;
        this->piece[1][2] = 0b00011000;
        this->piece[1][3] = 0b00010000;

        this->piece[2][0] = 0b00000000;
        this->piece[2][1] = 0b00000000;
        this->piece[2][2] = 0b00111000;
        this->piece[2][3] = 0b00010000;

        this->piece[3][0] = 0b00000000;
        this->piece[3][1] = 0b00010000;
        this->piece[3][2] = 0b00110000;
        this->piece[3][3] = 0b00010000;

        // aşşağı +y sol +x
        // I1 CW
        rotationRules[0][0] = {1, 0};
        rotationRules[0][1] = {1, -1};
        rotationRules[0][2] = {0, 2};
        rotationRules[0][3] = {1, 2};
        // I2 CW
        rotationRules[1][0] = {-1, 0};
        rotationRules[1][1] = {-1, 1};
        rotationRules[1][2] = {0, -2};
        rotationRules[1][3] = {-1, -2};
        // I3 CW
        rotationRules[2][0] = {-1, 0};
        rotationRules[2][1] = {-1, -1};
        rotationRules[2][2] = {0, 2};
        rotationRules[2][3] = {-1, 2};
        // I4 CW
        rotationRules[3][0] = {1, 0};
        rotationRules[3][1] = {1, 1};
        rotationRules[3][2] = {0, -2};
        rotationRules[3][3] = {1, -2};
        // I4 ACW
        rotationRules[4][0] = {1, 0};
        rotationRules[4][1] = {1, 1};
        rotationRules[4][2] = {0, -2};
        rotationRules[4][3] = {1, -2};
        // I3 ACW
        rotationRules[5][0] = {1, 0};
        rotationRules[5][1] = {1, -1};
        rotationRules[5][2] = {0, 2};
        rotationRules[5][3] = {1, 2};
        // I2 ACW
        rotationRules[6][0] = {-1, 0};
        rotationRules[6][1] = {-1, 1};
        rotationRules[6][2] = {0, -2};
        rotationRules[6][3] = {-1, -2};
        // I1 ACW
        rotationRules[7][0] = {-1, 0};
        rotationRules[7][1] = {-1, -1};
        rotationRules[7][2] = {0, 2};
        rotationRules[7][3] = {-1, 2};
        break;

    default:
        break;
    }
}
Piece::Piece(const Piece &p)
{
    this->piece[0] = p.piece[0];
    this->piece[1] = p.piece[1];
    this->piece[2] = p.piece[2];
    this->piece[3] = p.piece[3];

    this->rotationRules[0] = p.rotationRules[0];
    this->rotationRules[1] = p.rotationRules[1];
    this->rotationRules[2] = p.rotationRules[2];
    this->rotationRules[3] = p.rotationRules[3];
    this->rotationRules[4] = p.rotationRules[4];
    this->rotationRules[5] = p.rotationRules[5];
    this->rotationRules[6] = p.rotationRules[6];
    this->rotationRules[7] = p.rotationRules[7];

    this->pieceType = p.pieceType;
    this->x = p.x;
    this->y = p.y;
    this->rotation = p.rotation;
}
void Piece::rotateRight()
{
    this->rotation++;
    if (this->rotation > 3)
        this->rotation = 0;
}
void Piece::rotateLeft()
{
    this->rotation--;
    if (this->rotation < 0)
        this->rotation = 3;
}
bool Piece::get(int x, int y, int rot)
{
    if (rot != -1)
    {
        return this->piece[rot][x] & (1 << y);
    }
    return this->piece[this->rotation][x] & (1 << y);
}
Board::Board()
{
    this->Clear();
}
void Board::IFever()
{
    /*this->RealBoard[0] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[1] = {4, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 3};
    this->RealBoard[2] = {4, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[3] = {4, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[4] = {4, 2, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3};
    this->RealBoard[5] = {4, 2, 2, 2, 0, 2, 2, 0, 2, 2, 0, 3};
    this->RealBoard[6] = {4, 2, 2, 2, 0, 2, 2, 0, 2, 2, 0, 3};
    this->RealBoard[7] = {4, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 3};
    this->RealBoard[8] = {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 3};
    this->RealBoard[9] = {4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3};
    this->RealBoard[10] = {4, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3};
    this->RealBoard[11] = {4, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3};
    this->RealBoard[12] = {4, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3};
    this->RealBoard[13] = {4, 2, 0, 2, 2, 0, 2, 2, 2, 2, 0, 3};
    this->RealBoard[14] = {4, 2, 0, 2, 2, 0, 2, 2, 2, 2, 0, 3};
    this->RealBoard[15] = {4, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[16] = {4, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[17] = {4, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3};
    this->RealBoard[18] = {4, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 3};
    this->RealBoard[19] = {4, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 3};
    this->RealBoard[20] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3};
    this->RealBoard[21] = {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3};*/
    this->RealBoard[0] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[1] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[2] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[3] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[4] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[5] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[6] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[7] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[8] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[9] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[10] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[11] = {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[12] = {4, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 3};
    this->RealBoard[13] = {4, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[14] = {4, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[15] = {4, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[16] = {4, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[17] = {4, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[18] = {4, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[19] = {4, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[20] = {4, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 3};
    this->RealBoard[21] = {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3};
}
void Board::Clear()
{
    board.fill({});
    RealBoard.fill({});
    for (int y = 0; y < BOARD_HEIGHT + 1; y++)
    {
        this->RealBoard[y][0] = 4;
        this->RealBoard[y][BOARD_WIDTH + 1] = 3;
    }
    for (int x = 0; x < BOARD_WIDTH + 2; x++)
    {
        this->RealBoard[BOARD_HEIGHT][x] = 2;
    }
}
bool Board::putPiece(Piece piece, bool collided)
{
    int size = 6;
    bool isColliding = false;

    isColliding = this->collisionCheck(&piece);
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (piece.get(i, j))
            {
                int x = piece.x + j;
                int y = piece.y + i;
                if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
                {

                    this->board[y][x] = 1;
                }
            }
        }
    }
    if (collided)
    {
        CheckLines(true);
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            for (int y = 0; y < BOARD_HEIGHT; y++)
            {
                uint8_t val = this->board[y][x];
                if (val)
                {
                    this->RealBoard[y][x + 1] = val;
                }
                else
                {
                    this->RealBoard[y][x + 1] = 0;
                }
            }
        }
    }
    return isColliding;
}
void Board::toScreen(FrameBuffer *buf)
{
    int size = 10;

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            uint8_t val = this->board[y][x];
            this->board[y][x] = this->RealBoard[y][x + 1];
            if (val)
            {
                if (val == 2)
                {
                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            // buf->setPixel( i * size + y, j * size + x,Colors::GREEN);
                        }
                    }
                }
                else
                {
                    buf->drawLine(x * size, y * size, x * size + size, y * size + size, Colors::RED);
                }

                buf->drawRect(x * size, y * size, x * size + size, y * size + size, (Colors)val);
            }
        }
    }

    /*for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            uint8_t val = this->board[i][j];
            if (val)
            {
                if (val == 2)
                {
                    for (int y = 0; y < size; y++)
                    {
                        for (int x = 0; x < size; x++)
                        {
                            buf->setPixel(i * size + y, j * size + x, Colors::GREEN);
                        }
                    }
                }
                else
                {
                    buf->drawLine(i * size, j * size, i * size + size, j * size + size, Colors::RED);
                }

                buf->drawRect(i * size, j * size, i * size + size, j * size + size, Colors::YELLOW);
            }
        }
    }
    int ofset = BOARD_HEIGHT * size + 2;
    for (int i = 0; i < BOARD_HEIGHT + 1; i++)
    {
        for (int j = 0; j < BOARD_WIDTH + 2; j++)
        {
            if (this->RealBoard[i][j])
            {
                for (int y = 0; y < size; y++)
                {
                    for (int x = 0; x < size; x++)
                    {
                        buf->setPixel(i * size + y + ofset, j * size + x, Colors::BLUE);
                    }
                }
            }
        }
    }
*/
    /*for (int x = 0; x < BOARD_HEIGHT; x++)
    {
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            this->board[x][y] = this->RealBoard[x][y + 1];
        }
    }*/
}
bool Board::collisionCheck(Piece *piece, int *wallcol, int wallcolCheck)
{
    bool collision = false;
    int x1 = 0;
    int y1 = 0;
    if (wallcol != nullptr)
    {
        *wallcol = 0;
    }
    for (int y = 3; y >= 0; y--)
    {
        for (int x = 0; x < 8; x++)
        {
            if (piece->get(y, x))
            {

                x1 = piece->x + x + wallcolCheck;
                if (wallcol != nullptr)
                {
                    y1 = piece->y + y;
                }
                else
                {
                    y1 = piece->y + y + 1;
                }

                if (x1 >= -1 && x1 < BOARD_WIDTH + 2 && y1 >= 0 && y1 < BOARD_HEIGHT + 1)
                {
                    int value = (int)this->RealBoard[y1][x1 + 1];
                    if (value == 3)
                    {
                        if (wallcol != nullptr)
                        {
                            *wallcol = 1;
                        }
                    }
                    else if (value == 4)
                    {
                        if (wallcol != nullptr)
                        {
                            *wallcol = -1;
                        }
                    }
                    else if (value == 1 || value == 2)
                    {
                        collision = true;
                        if (wallcol != nullptr)
                        {
                            *wallcol = -4;
                        }
                    }
                }
            }
        }
    }

    return collision;
}
bool Board::CheckMoveHorizontal(Piece *piece)
{

    int moveint = 0;
    /**
     * Button Hold Timers
     */
    if (but1Timer > 0 & but1)
    {
        but1Timer--;
        but1Pressed = false;
    }
    else
    {
        but1Pressed = true;
        but1Timer = 2;
    }

    if (but2Timer > 0 & but2)
    {
        but2Timer--;
        but2Pressed = false;
    }
    else
    {
        but2Pressed = true;
        but2Timer = 2;
    }

    /**
     *Right
     *Onpress
     */

    if (gpio_get((ButtonA)) & (!this->but1 | but1Pressed))
    {
        // do things on press

        collisionCheck(piece, &moveint, -1);
        if (!but1)
        {
            but1Timer = 4;

            this->but1 = true;
        }
        if (moveint == 0)
        {
            piece->x--;
        }

        return true;
    }
    /**
     * Right
     * OnRelease
     */
    else if (!gpio_get((ButtonA)) & this->but1)
    { // do things on release
        but1 = false;
        but1Timer = 0;
        but1Pressed = false;
    }
    /**
     * Left
     * Onpress
     */
    if (gpio_get((ButtonB)) & (!this->but2 | but2Pressed))
    {
        // do things

        collisionCheck(piece, &moveint, 1);

        if (!but2)
        {
            but2Timer = 4;

            this->but2 = true;
        }

        if (moveint == 0)
        {
            piece->x++;
        }
        return true;
    }
    /**
     * Left
     * OnRelease
     */
    else if (!gpio_get((ButtonB)) & this->but2)
    { // do things on release
        this->but2 = false;
        but2Timer = 0;
        but2Pressed = false;
    }
    return false;
}
int Board::CheckLines(bool isCollided)
{

    // check and clear lineson the board
    if (isCollided)
    {
        int lines = 0;
        bool line = true;
        while (true)
        {

            for (int y = BOARD_HEIGHT - 1; y > 0; y--)
            {
                line = true;

                for (int x = 0; x < BOARD_WIDTH; x++)
                {
                    if (!this->board[y][x])
                    {
                        line = false;
                        break;
                    }
                }
                if (line)
                {
                    lines += 1;
                    for (int y2 = y; y2 > 0; y2--)
                    {
                        for (int x = 0; x < BOARD_WIDTH; x++)
                        {
                            this->board[y2][x] = this->board[y2 - 1][x];
                        }
                    }
                    break;
                }
            }
            if (!line)
            {
                break;
            }
        }
        return lines;
    }
}
bool Board::CheckMoveVertical(int *timer, Piece *piece, bool *col)
{

    /**
     * Button Hold Timers
     */
    if (but3Timer > 0 & but3)
    {
        but3Timer--;
        but3Pressed = false;
    }
    else
    {
        but3Pressed = true;
        but3Timer = 2;
    }

    /**
     * SoftDown
     * onPress
     */
    if (gpio_get((ButtonRight)) & (!this->but3 | but3Pressed))
    {
        if (!but3)
        {
            but3Timer = 2;

            this->but3 = true;
        }
// do things on press
#ifndef Debug
        *timer += 10;
#endif
#ifdef Debug
        piece->y = piece->y + 1;
#endif
        return true;
    }
    /**
     * SoftDown
     * OnRelease
     */
    else if (!gpio_get((ButtonRight)) & this->but3)
    { // do things on release
        but3 = false;
        but3Timer = 0;
        but3Pressed = false;
    }
    /**
     * HardDown
     * onPress
     */
    if (gpio_get((ButtonDown)) & !this->but4)
    {
        this->but4 = true;
// do things
#ifndef Debug
        int y = 0;
        while (true)
        {
            if (collisionCheck(piece))
                break;
            piece->y = piece->y + 1;
            y++;
        }
        *col = true;

        *timer = 20;
#endif
#ifdef Debug
        piece->y = piece->y - 1;
#endif
        return true;
    }
    /**
     * HardDown
     * OnRelease
     */
    else if (!gpio_get((ButtonDown)) & this->but4)
    { // do things on release
        this->but4 = false;
    }
    return false;
}
bool Board::GeneralCollisionCheck(Piece *piece, int offsetx, int offsety)
{
    bool collision = false;
    int x1 = 0;
    int y1 = 0;
    for (int y = 3; y >= 0; y--)
    {
        for (int x = 0; x < 8; x++)
        {
            if (piece->get(y, x))
            {

                x1 = piece->x + x + offsetx;

                y1 = piece->y + y + offsety;

                if (x1 >= -1 && x1 < BOARD_WIDTH + 2 && y1 >= 0 && y1 < BOARD_HEIGHT + 1)
                {
                    int value = (int)this->RealBoard[y1][x1 + 1];
                    if (value != 0)
                    {
                        collision = true;
                        break;
                    }
                    else
                    {
                        collision = false;
                    }
                }
            }
        }
        if (collision)
        {
            break;
        }
    }

    return collision;
}
void Board::CheckMoveRotation(Piece *piece)
{

    /**
     * Button Hold Timers
     */
    if (but5Timer > 0 & but5)
    {
        but5Timer--;
        but5Pressed = false;
    }
    else
    {
        but5Pressed = true;
        but5Timer = 2;
    }
    if (but6Timer > 0 & but6)
    {
        but6Timer--;
        but6Pressed = false;
    }
    else
    {
        but6Pressed = true;
        but6Timer = 2;
    }
    /**
     * SoftDown
     * onPress
     */
    if (gpio_get((ButtonLeft)) & (!this->but5 | but5Pressed))
    {
        if (!but5)
        {
            but5Timer = 2;

            this->but5 = true;
        }
        // do things on press

        collisionRotateCheck(piece, 1);
    }
    /**
     * SoftDown
     * OnRelease
     */
    else if (!gpio_get((ButtonLeft)) & this->but5)
    { // do things on release
        but5 = false;
        but5Timer = 0;
        but5Pressed = false;
    }
    /**
     * HardDown
     * onPress
     */
    if (gpio_get((ButtonUp)) & !this->but6)
    {
        if (!but6)
        {
            but6Timer = 2;

            this->but6 = true;
        }

        // do things

        collisionRotateCheck(piece, -1);
    }
    /**
     * HardDown
     * OnRelease
     */
    else if (!gpio_get((ButtonUp)) & this->but6)
    { // do things on release
        this->but6 = false;
        but6Timer = 0;
        but6Pressed = false;
    }
}
int Board::collisionRotateCheck(Piece *piece, int rot)
{
    bool collision = false;
    int x1 = 0;
    int y1 = 0;
    int tryCount = 0;
    int newrot;
    int rotpos = piece->rotation;
    int offsetx = 0, offsety = 0;
    Piece tempPiece = *piece;
    if (rot < 0)
    {
        tempPiece.rotateLeft();
        switch (rotpos)
        {
        case 0:
            newrot = 7;
            break;
        case 1:
            newrot = 6;
            break;
        case 2:
            newrot = 5;
            break;
        case 3:
            newrot = 4;
            break;
        }
    }
    else
    {
        tempPiece.rotateRight();
        switch (rotpos)
        {
        case 0:
            newrot = 0;
            break;
        case 1:
            newrot = 1;
            break;
        case 2:
            newrot = 2;
            break;
        case 3:
            newrot = 3;
            break;
        }
    }

    while (tryCount < 5)
    {
        collision = GeneralCollisionCheck(&tempPiece, offsetx, offsety);
        if (!collision)
            break;
        offsetx = tempPiece.rotationRules[newrot][tryCount][0];
        offsety = tempPiece.rotationRules[newrot][tryCount][1];
        tryCount++;
    }
    if (tryCount == 5)
    {
        return tryCount;
    }
    if (tryCount != 0)
    {
        piece->x = piece->x + offsetx;
        piece->y = piece->y + offsety;
    }
    piece->rotation = tempPiece.rotation;
    return tryCount;
}

void tetris(FrameBuffer *buf)
{
    Board board = Board();

    Piece I = Piece(0, 0, 0, 0);
    Piece J = Piece(1, 0, 0, 0);
    Piece L = Piece(2, 0, 0, 0);
    Piece O = Piece(3, 0, 0, 0);
    Piece S = Piece(4, 0, 0, 0);
    Piece Z = Piece(5, 0, 0, 0);
    Piece T = Piece(6, 0, 0, 0);
    Piece pieces[7] = {I, J, L, O, S, Z, T};
    board.Clear();
    board.IFever();
    int a = 6;
    bool isCollided = false, colliderTimerOn = false, colliding;
    int timer = 0;
    bool once = true, timerOnce = true, butT = true;
    while (1)
    {
        // board.Clear();
        //buf->clear();

        if (timer >= 10 & (!colliderTimerOn))
        {

            pieces[a].y++;

            timer = 0;
        }
        board.CheckMoveRotation(&pieces[a]);
        board.CheckMoveVertical(&timer, &pieces[a], &isCollided);
        bool moveCheck = board.CheckMoveHorizontal(&pieces[a]);

        colliding = board.putPiece(pieces[a], isCollided);

        if (colliding)
        {
            if (timerOnce)
            {
                timerOnce = false;
                timer = 0;
            }
            colliderTimerOn = true;
            once = true;
        }
        else
        {
            if (once)
            {
                timerOnce = true;
                once = false;
                timer = 0;
                colliderTimerOn = false;
            }
        }
        if (isCollided)
        {
            isCollided = false;
            colliderTimerOn = false;

            pieces[a].y = -1;
            pieces[a].x = 2;
            pieces[a].rotation = 0;
            a = rand() % 7;
        }
        if (colliderTimerOn)
        {
            if (moveCheck)
            {
                timer -= 1;
            }
            if (timer >= 20)
            {
                isCollided = true;
                timer = 0;
            }
        }

        timer += 1;
        board.toScreen(buf);
        buf->drawChar((char)48 + pieces[a].rotation + 1, 0, 0, Colors::WHITE);
        sleep_ms(30);
        buf->clear();
    }
}
