#pragma once
#include "IReversiContext.h"

namespace Reversi
{
	class ReversiContext : public IReversiContext
	{
	private:
		static const int BOARD_SIZE = 8;
		SLOT_STATUS board[BOARD_SIZE][BOARD_SIZE];
		GAME_STATE currentState;

	public:
		ReversiContext(); // �غc�l�A��l�ƴѽL
		SLOT_STATUS GetSlotStatus(int row, int column) override;
		SLOT_STATUS SetSlotStatus(int row, int column, SLOT_STATUS status) override;
		GAME_STATE GetCurrentState() override;
		GAME_STATE SetCurrentState(GAME_STATE state) override;

		void PrintBoard() override; // �ΨӴ��ծɦL�X�ѽL
		bool HasValidMove(PLAYER_COLOR player) override;
		int CountDisks(SLOT_STATUS color) override;
		bool IsValidMove(int row, int col, PLAYER_COLOR player) override;
		void FlipDisks(int row, int col) override;

	};
}
