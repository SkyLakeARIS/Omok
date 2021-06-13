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

int Board::recurUp(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurUp(x, y - 1, color) + 1;
    }

    return 0;
}

int Board::recurDown(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurDown(x, y + 1, color) + 1;
    }

    return 0;
}

int Board::recurLeft(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurLeft(x - 1, y, color) + 1;
    }

    return 0;
}

int Board::recurRight(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurRight(x + 1, y, color) + 1;
    }

    return 0;
}

int Board::recurDiagonalUpLeft(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurDiagonalUpLeft(x - 1, y - 1, color) + 1;
    }

    return 0;
}

int Board::recurDiagonalUpRight(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurDiagonalUpRight(x + 1, y - 1, color) + 1;
    }

    return 0;
}

int Board::recurDiagonalDownRight(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurDiagonalDownRight(x + 1, y + 1, color) + 1;
    }

    return 0;
}

int Board::recurDiagonalDownLeft(int x, int y, eStoneType color)
{
    if (mBaord[y][x] == color)
    {
        return recurDiagonalDownLeft(x - 1, y + 1, color) + 1;
    }

    return 0;
}

bool Board::CheckOmok(int x, int y, eStoneType color)
{
    const int OMOK = 5;
    //돌을 놓은 위치는 미리 카운트하고 재귀함수는 주변에 놓인 자신의 돌을 체크함.
    int omokCount = 1;
    //자신의 돌 사이에 둠으로써 오목이 완성되는 경우를 고려해서 두 함수의 리턴값을
    //더한 후 조건을 체크함.
    omokCount += (recurUp(x, y - 1, color) + recurDown(x, y + 1, color));
    if (omokCount == OMOK)
    {
        return true;
    }

    omokCount = 1;
    omokCount += (recurLeft(x - 1, y, color) + recurRight(x + 1, y, color));
    if (omokCount == OMOK)
    {
        return true;
    }

    omokCount = 1;
    omokCount += (recurDiagonalUpLeft(x - 1, y - 1, color) + recurDiagonalDownRight(x + 1, y + 1, color));
    if (omokCount == OMOK)
    {
        return true;
    }

    omokCount = 1;
    omokCount += (recurDiagonalUpRight(x + 1, y - 1, color) + recurDiagonalDownLeft(x - 1, y + 1, color));
    if (omokCount == OMOK)
    {
        return true;
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