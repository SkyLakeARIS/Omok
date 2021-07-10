#pragma once
#include "lib.h"

#define BOARD_SIZE (20)

class Board
{
public:

    Board()
    {
        for (int LoopY = 0; LoopY < BOARD_SIZE; LoopY++)
        {
            for (int LoopX = 0; LoopX < BOARD_SIZE; LoopX++)
            {
                mBaord[LoopY][LoopX] = eStoneType::EmptySpace;
            }
        }
    }

    bool CheckOmok(int x, int y, eStoneType color);

    bool PlaceStone(const int x, const int y, eStoneType color);

    void PrintBoard();

private:

    int recurCountStone(int currentX, int currentY, const POINT dir, const eStoneType color);

private:
    eStoneType mBaord[BOARD_SIZE][BOARD_SIZE];
};