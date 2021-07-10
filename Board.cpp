#include "Board.h"

void Board::PrintBoard()
{
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            gotoxy(x*2, y);
            if (mBaord[y][x] == eStoneType::EmptySpace)
            {
                if (y == 0) // 첫출 그리기
                {
                    if (x == 0)
                    {
                        std::cout << "┌";
                    }
                    if (x == (BOARD_SIZE - 1))
                    {
                        std::cout << "┐";
                    }
                    if (x != 0 && x != (BOARD_SIZE - 1))
                    {
                        std::cout << "┬";
                    }
                }
                else // 마지막 줄 그리기
                {
                    if (y == (BOARD_SIZE - 1))
                    {
                        if (x == 0)
                        {
                            std::cout << "└";
                        }
                        if (x == (BOARD_SIZE - 1))
                        {
                            std::cout << "┘";
                        }
                        if (x != 0 && x != (BOARD_SIZE - 1))
                        {
                            std::cout << "┴";
                        }
                    }
                    else //중간 줄 그리기
                    {
                        if (x == 0)
                        {
                            std::cout << "├";
                        }
                        if (x == (BOARD_SIZE - 1))
                        {
                            std::cout << "┤";
                        }
                        if (x != 0 && x != (BOARD_SIZE - 1))
                        {
                            std::cout << "┼";
                        }
                    }
                }
            }
            else
            {
                if (mBaord[y][x] == eStoneType::BlackStone)
                {
                    std::cout << "○";
                }
                else
                {
                    std::cout << "●";
                }
            }
        }
    }
}

int Board::recurCountStone(int currentX, int currentY, const POINT dir, const eStoneType color)
{
    if (mBaord[currentY][currentX] == color)
    {
        return recurCountStone(currentX + dir.x, currentY + dir.y, dir, color) + 1;
    }

    return 0;
}

bool Board::CheckOmok(int x, int y, eStoneType color)
{
    const int OMOK = 5;
    const POINT DIR[8] =
    {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0}, {1, 0},
        {-1, 1}, {0, 1}, {1, 1}
    };
    //자신의 돌 사이에 둠으로써 오목이 완성되는 경우를 고려해서 검사 방향의 반대 방향도
    //검사하여 합산한 결과를 통해 오목 완성 여부를 검사한다.
    //재귀함수는 자기자신(돌을 놓은 위치)를 포함하므로 1을 빼줌으로써 중복 계산을 해결한다.
    for (int i = 0; i < 4; i++)
    {
        int omokCount = 0;
        omokCount += recurCountStone(x, y, DIR[i], color);
        omokCount += recurCountStone(x, y, DIR[7-i], color);
        if ((omokCount-1) == OMOK)
        {
            return true;
        }
    }

    return false;
}

//보드에 돌을 두는 함수
//매개변수로 받은 좌표에 현재 차례에 맞는 돌을 두고
//반환형으로 해당 위치에 돌을 둘 수 있는지 여부를 반환함. 정상 == true, 둘 수 없음 == false
bool Board::PlaceStone(const int x, const int y, eStoneType color)
{
    if (mBaord[y][x] == eStoneType::EmptySpace)
    {
        mBaord[y][x] = color;
        return true;
    }
    else
    {
        return false;
    }
}