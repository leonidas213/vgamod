#pragma once
#include "pico/stdlib.h"
#include <array>
#include "framebuffer.h"
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
class Piece
{
public:
    int pieceType;
    int oldx = 0, oldy = 0, oldrot = 0;
    void moveDown();
    void moveLeft();
    void moveRight();
    void Reset();
    void rotateRight();
    void rotateLeft();
    bool get(int, int, int rot = -1);
    std::array<std::array<int8_t, 4>, 4> piece = {0};
    /**
     * rotationRules[8][4][2]
     * 8 possible rotation rule(every rule have 5 different ofset value)
     * 4 possible offsets for each rule ( first one is always [0,0] so we ignore it)
     * 2 ofset value(x,y offset)
     *
     * clocwise rotation [0] to[3]
     * a rotation rule is if the rotation is possible and the offset of the piece
     * 1->2->3->4->1(each arrow is a rotation rule)
     * anti-clockwise rotation [4] to[7]
     * 4->3->2->1->4(each arrow is a rotation rule)
     */
    std::array<std::array<int8_t, 2>, 4> rotationRules[8] = {0};
    Piece(int type = 0, int x = 0, int y = 0, int rotation = 0);
    Piece(const Piece &p);
    int rotation = 0;
    int x = 0, y = 0;
};
class Board
{
private:
    const int ButtonA = 1;
    const int ButtonB = 1;
    const int ButtonLeft = 1;
    const int ButtonRight = 1;
    const int ButtonDown = 1;
    const int ButtonUp = 1;

    bool but1 = false, but2 = false;
    bool but3 = false, but4 = false;
    bool but5 = false, but6 = false;
    int but1Timer = 0, but2Timer = 0;
    int but3Timer = 0, but4Timer = 0;
    int but5Timer = 0, but6Timer = 0;
    bool but1Pressed = false, but2Pressed = false;
    bool but3Pressed = false, but4Pressed = false;
    bool but5Pressed = false, but6Pressed = false;

    int offsetx, offsety;
    FrameBuffer *buf;
    int size;

public:
    bool gameover = false;
    bool putPiece(Piece piece, bool real = false);
    void toScreen();
    void IFever();
    std::array<std::array<int8_t, (BOARD_WIDTH)>, (BOARD_HEIGHT)> board = {0};
    std::array<std::array<int8_t, (BOARD_WIDTH + 2)>, (BOARD_HEIGHT + 1)> RealBoard = {0};


    void pieceShower();
    void Clear();
    bool collisionCheck(Piece *piece, int *wallcol = nullptr, int wallcolCheck = 0);
    bool CheckMoveHorizontal(Piece *piece);
    bool CheckMoveVertical(int *timer, Piece *piece, bool *col = nullptr);
    void CheckMoveRotation(Piece *piece);
    int CheckLines(bool);
    int collisionRotateCheck(Piece *piece, int rot);
    bool GeneralCollisionCheck(Piece *piece, int offsetx, int offsety);
    Board(FrameBuffer *buf, int ofsetx = 0, int ofsety = 0, int size = 20);
};
void tetris(FrameBuffer *buf);
