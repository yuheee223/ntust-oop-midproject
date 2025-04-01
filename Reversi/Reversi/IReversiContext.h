#pragma once
#include "ReversiDefine.h"

namespace Reversi
{
	/**
	* Implementations of this interface manage the game data.
	*/
	class IReversiContext
	{
	public:
		virtual SLOT_STATUS GetSlotStatus(int row, int column) = 0;
		virtual SLOT_STATUS SetSlotStatus(int row, int column, SLOT_STATUS status) = 0;
		virtual GAME_STATE GetCurrentState() = 0;
		virtual GAME_STATE SetCurrentState(GAME_STATE state) = 0;

		virtual void PrintBoard() = 0;
		virtual bool HasValidMove(PLAYER_COLOR player) = 0;
		virtual int CountDisks(SLOT_STATUS color) = 0;
		virtual bool IsValidMove(int row, int col, PLAYER_COLOR player) = 0;
		virtual void FlipDisks(int row, int col) = 0;


	};
}
