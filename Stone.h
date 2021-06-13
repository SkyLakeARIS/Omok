#pragma once
#include "lib.h"

class Stone
{
public:
	Stone(eStoneType setColor)
	{
		mColor = setColor;
		if (setColor == eStoneType::BlackStone)
		{
			mStone = "��";
		}
		else
		{
			mStone = "��";
		}
	}

	//const char* GetStone();

	eStoneType GetColor();

private:
	const char* mStone;
	eStoneType mColor;
};