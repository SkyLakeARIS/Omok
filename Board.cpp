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
    //�ڽ��� �� ���̿� �����ν� ������ �ϼ��Ǵ� ��츦 ����ؼ� �˻� ������ �ݴ� ���⵵
    //�˻��Ͽ� �ջ��� ����� ���� ���� �ϼ� ���θ� �˻��Ѵ�.
    //����Լ��� �ڱ��ڽ�(���� ���� ��ġ)�� �����ϹǷ� 1�� �������ν� �ߺ� ����� �ذ��Ѵ�.
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