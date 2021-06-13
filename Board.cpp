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
                if (y == 0) // ù�� �׸���
                {
                    if (x == 0)
                    {
                        std::cout << "��";
                    }
                    if (x == (BOARD_SIZE - 1))
                    {
                        std::cout << "��";
                    }
                    if (x != 0 && x != (BOARD_SIZE - 1))
                    {
                        std::cout << "��";
                    }
                }
                else // ������ �� �׸���
                {
                    if (y == (BOARD_SIZE - 1))
                    {
                        if (x == 0)
                        {
                            std::cout << "��";
                        }
                        if (x == (BOARD_SIZE - 1))
                        {
                            std::cout << "��";
                        }
                        if (x != 0 && x != (BOARD_SIZE - 1))
                        {
                            std::cout << "��";
                        }
                    }
                    else //�߰� �� �׸���
                    {
                        if (x == 0)
                        {
                            std::cout << "��";
                        }
                        if (x == (BOARD_SIZE - 1))
                        {
                            std::cout << "��";
                        }
                        if (x != 0 && x != (BOARD_SIZE - 1))
                        {
                            std::cout << "��";
                        }
                    }
                }
            }
            else
            {
                if (mBaord[y][x] == eStoneType::BlackStone)
                {
                    std::cout << "��";
                }
                else
                {
                    std::cout << "��";
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
    //���� ���� ��ġ�� �̸� ī��Ʈ�ϰ� ����Լ��� �ֺ��� ���� �ڽ��� ���� üũ��.
    int omokCount = 1;
    //�ڽ��� �� ���̿� �����ν� ������ �ϼ��Ǵ� ��츦 ����ؼ� �� �Լ��� ���ϰ���
    //���� �� ������ üũ��.
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

//���忡 ���� �δ� �Լ�
//�Ű������� ���� ��ǥ�� ���� ���ʿ� �´� ���� �ΰ�
//��ȯ������ �ش� ��ġ�� ���� �� �� �ִ��� ���θ� ��ȯ��. ���� == true, �� �� ���� == false
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