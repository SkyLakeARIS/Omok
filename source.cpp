#include "Board.h"
#include "Stone.h"

void message(eMessage message)
{
    switch (message)
    {
    case eMessage::TurnOfBlackStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "○흑돌 차례 입니다.          ";
        break;
    case eMessage::TurnOfWhiteStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "●백돌 차례 입니다.          ";
        break;
    case eMessage::WinBlackStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "흑돌이 이겼습니다!              ";
        break;
    case eMessage::WinWhiteStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "백돌이 이겼습니다!              ";
        break;
    case eMessage::CanNotPlaceStone:
        gotoxy(1, BOARD_SIZE + 2);
        std::cout << "돌을 놓을 수 없는 곳 입니다!";
        break;
    case eMessage::ContinueOrExit:
        gotoxy(2, BOARD_SIZE + 3);
        std::cout << "재시작은 Y 종료는 다른키를 입력하세요....";
        break;
    default:
        //Assert
        break;
    }
}

int main()
{
    HANDLE hStdin;
    DWORD fdwSaveOldMode;
    INPUT_RECORD mouseInput;
    DWORD numRead;
    Board board;
    Stone blackStone(eStoneType::BlackStone);
    Stone whiteStone(eStoneType::WhiteStone);
    Stone* currentTurn = &blackStone;
    int cursorX = 0;
    int cursorY = 0;
    bool bIsCompleteOmok = false;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error.GetStdHandle";
    }

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
    {
        std::cout << "Error.GetConsoleMode";
    }

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        std::cout << "Error.SetConsoleMode";
    }

    board.PrintBoard();

    while (!bIsCompleteOmok)
    {
        if (!ReadConsoleInput(hStdin, &mouseInput, 1, &numRead))
        {
            std::cout << "Error.ReadConsoleInput";
        }

        if (mouseInput.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouse = mouseInput.Event.MouseEvent;
            switch (mouse.dwEventFlags)
            {
            case 0:
                if (mouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    if ((mouse.dwMousePosition.Y >= 0 && mouse.dwMousePosition.Y < BOARD_SIZE) && (mouse.dwMousePosition.X >= 0 && mouse.dwMousePosition.X < BOARD_SIZE * 2))
                    {
                        gotoxy((mouse.dwMousePosition.X / 2) * 2, mouse.dwMousePosition.Y);
                    }
                }
                break;
            case DOUBLE_CLICK:
                if ((mouse.dwMousePosition.Y >= 0 && mouse.dwMousePosition.Y < BOARD_SIZE) && (mouse.dwMousePosition.X >= 0 && mouse.dwMousePosition.X < BOARD_SIZE * 2))
                {
                    cursorX = mouse.dwMousePosition.X / 2;
                    cursorY = mouse.dwMousePosition.Y;

                    //특수문자가 2칸(2바이트)를 차지함으로서 생기는 좌표차이(클릭하는 위치와 돌이 놓이는 위치)
                    //없애기위해 /2후 출력되는 위치를 맞추기위해 *2를 함
                    gotoxy((mouse.dwMousePosition.X / 2) * 2, mouse.dwMousePosition.Y);

                    if (board.PlaceStone(cursorX, cursorY, currentTurn->GetColor()))
                    {
                        board.PrintBoard();
                        //오목이 완성되면 종료 그렇지않으면, 차례교대 후 게임을 진행함.
                        if (board.CheckOmok(cursorX, cursorY, currentTurn->GetColor()))
                        {
                            bIsCompleteOmok = true;
                            if (currentTurn->GetColor() == eStoneType::BlackStone)
                            {
                                message(eMessage::WinBlackStone);
                            }
                            else
                            {
                                message(eMessage::WinWhiteStone);
                            }
                        }
                        else
                        {
                            if (currentTurn->GetColor() == eStoneType::BlackStone)
                            {
                                currentTurn = &whiteStone;
                                message(eMessage::TurnOfWhiteStone);
                            }
                            else
                            {
                                currentTurn = &blackStone;
                                message(eMessage::TurnOfBlackStone);
                            }
                        }
                    }
                    else
                    {
                        message(eMessage::CanNotPlaceStone);
                    }
                }
                break;
            }
        }
    }

    SetConsoleMode(hStdin, fdwSaveOldMode);

    return 0;
}