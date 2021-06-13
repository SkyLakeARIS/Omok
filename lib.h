#pragma once
#include <iostream>
#include <windows.h>

enum class eMessage
{
    TurnOfBlackStone,
    TurnOfWhiteStone,
    WinBlackStone,
    WinWhiteStone,
    CanNotPlaceStone,
    ContinueOrExit
};


enum class eStoneType
{
    EmptySpace,
    BlackStone,
    WhiteStone
};

inline void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}