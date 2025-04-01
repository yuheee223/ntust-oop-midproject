//#include "ReversiContext.h"
//#include <iostream>
//
//namespace Reversi
//{
//	ReversiContext::ReversiContext() {
//		// ��l�ƴѽL�� EMPTY
//		for (int i = 0; i < BOARD_SIZE; i++)
//			for (int j = 0; j < BOARD_SIZE; j++)
//				board[i][j] = SLOT_STATUS::EMPTY;
//
//		int center = BOARD_SIZE / 2;
//
//		// �]�m��l�� 4 ���Ѥl
//		board[center - 1][center - 1] = SLOT_STATUS::WHITE;
//		board[center - 1][center] = SLOT_STATUS::BLACK;
//		board[center][center - 1] = SLOT_STATUS::BLACK;
//		board[center][center] = SLOT_STATUS::WHITE;
//
//		currentState = GAME_STATE::BLACK_TURN;
//	}
//
//	SLOT_STATUS ReversiContext::GetSlotStatus(int row, int column) {
//		if (row < 0 || row >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE)
//			return SLOT_STATUS::EMPTY; // �W�X�d��ɦ^�� EMPTY
//
//		return board[row][column];
//	}
//
//	SLOT_STATUS ReversiContext::SetSlotStatus(int row, int column, SLOT_STATUS status) {
//		if (row < 0 || row >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE)
//			return SLOT_STATUS::EMPTY; // �W�X�d��ɤ����ܧ�
//
//		board[row][column] = status;
//
//		return status;
//	}
//
//	GAME_STATE ReversiContext::GetCurrentState() {
//		return currentState;
//	}
//
//	GAME_STATE ReversiContext::SetCurrentState(GAME_STATE state) {
//		currentState = state;
//
//		return state;
//	}
//
//	void ReversiContext::PrintBoard()
//	{
//		std::cout << "  0 1 2 3 4 5 6 7" << std::endl;
//		for (int i = 0; i < BOARD_SIZE; i++)
//		{
//			std::cout << i << " ";
//			for (int j = 0; j < BOARD_SIZE; j++)
//			{
//				switch (board[i][j])
//				{
//				case SLOT_STATUS::EMPTY:
//					std::cout << ". ";
//					break;
//				case SLOT_STATUS::BLACK:
//					std::cout << "B ";
//					break;
//				case SLOT_STATUS::WHITE:
//					std::cout << "W ";
//					break;
//				}
//			}
//			std::cout << std::endl;
//		}
//	}
//}

#include "ReversiContext.h"
#include <iostream>

namespace Reversi
{
	ReversiContext::ReversiContext()
	{
		// ��l�ƴѽL�A�����]�� EMPTY
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				board[i][j] = SLOT_STATUS::EMPTY;

		// �]�w��l�¥մѤl��m
		board[3][3] = SLOT_STATUS::WHITE;
		board[3][4] = SLOT_STATUS::BLACK;
		board[4][3] = SLOT_STATUS::BLACK;
		board[4][4] = SLOT_STATUS::WHITE;

		currentState = GAME_STATE::BLACK_TURN;
	}

	SLOT_STATUS ReversiContext::GetSlotStatus(int row, int col)
	{
		return board[row][col];
	}

	SLOT_STATUS ReversiContext::SetSlotStatus(int row, int col, SLOT_STATUS status)
	{
		board[row][col] = status;
		return status;
	}

	GAME_STATE ReversiContext::GetCurrentState()
	{
		return currentState;
	}

	GAME_STATE ReversiContext::SetCurrentState(GAME_STATE state)
	{
		currentState = state;
		return state;
	}

	void ReversiContext::PrintBoard()
	{
		std::cout << "  0 1 2 3 4 5 6 7" << std::endl;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			std::cout << i << " ";
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				switch (board[i][j])
				{
				case SLOT_STATUS::EMPTY:
					std::cout << ". ";
					break;
				case SLOT_STATUS::BLACK:
					std::cout << "B ";
					break;
				case SLOT_STATUS::WHITE:
					std::cout << "W ";
					break;
				}
			}
			std::cout << std::endl;
		}
	}

	bool ReversiContext::IsValidMove(int row, int col, PLAYER_COLOR player)
	{
		// �p�G�Ӧ�m�w�g���Ѥl�A�h��^ false
		if (board[row][col] != SLOT_STATUS::EMPTY) {
			return false;
		}

		SLOT_STATUS opponent = (player == PLAYER_COLOR::BLACK) ? SLOT_STATUS::WHITE : SLOT_STATUS::BLACK;

		// �ˬd�P��8�Ӥ�V�]�W�U���k�B�﨤�u�^�O�_����誺�Ѥl�A�åB�O�_��½��
		for (int drow = -1; drow <= 1; ++drow) {
			for (int dcol = -1; dcol <= 1; ++dcol) {
				if (drow == 0 && dcol == 0) {
					continue;  // ���L�ۤv��m
				}

				int r = row + drow;
				int c = col + dcol;

				bool opponentFound = false;
				// �q�o�Ӥ�V�}�l�A�ˬd�O�_�����Ѥl
				while (r >= 0 && r < 8 && c >= 0 && c < 8) {
					if (board[r][c] == opponent) {
						opponentFound = true;
					}
					else if (board[r][c] == (player == PLAYER_COLOR::BLACK ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE)) {
						// �p�G���F�ۦP�C�⪺�Ѥl�A�åB�e�������Ѥl�A�h���X�k
						if (opponentFound) {
							return true;
						}
						break;  // ����ۤv�Ѥl�N�����ˬd
					}
					else {
						break;  // �J��Ů�N�����ˬd
					}

					// ���ʨ�U�@��
					r += drow;
					c += dcol;
				}
			}
		}
		return false;
	}

	void ReversiContext::FlipDisks(int row, int col)
	{
		PLAYER_COLOR player = (GetSlotStatus(row, col) == SLOT_STATUS::BLACK) ? PLAYER_COLOR::BLACK : PLAYER_COLOR::WHITE;
		SLOT_STATUS opponent = (player == PLAYER_COLOR::BLACK) ? SLOT_STATUS::WHITE : SLOT_STATUS::BLACK;

		// �ˬd�P��8�Ӥ�V
		for (int drow = -1; drow <= 1; ++drow) {
			for (int dcol = -1; dcol <= 1; ++dcol) {
				if (drow == 0 && dcol == 0) {
					continue; // ���L��a
				}

				int r = row + drow;
				int c = col + dcol;

				// �x�s½�઺�Ѥl
				BoardPositionVector flippedPositions;

				while (r >= 0 && r < 8 && c >= 0 && c < 8) {
					if (GetSlotStatus(r, c) == opponent) {
						flippedPositions.push_back({ r, c });
					}
					else if (GetSlotStatus(r, c) == (player == PLAYER_COLOR::BLACK ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE)) {
						// �p�G���ۦP�C�⪺�Ѥl�A�B�����Ѥl�ݭn½��
						for (auto& pos : flippedPositions) {
							// ½��o�ǹ��Ѥl
							SetSlotStatus(pos.first, pos.second, (player == PLAYER_COLOR::BLACK) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE);
						}
						break; // �����ˬd����V
					}
					else {
						break; // �J��Ů�εL�k½�઺���p
					}

					// �~��b����V�W���e��
					r += drow;
					c += dcol;
				}
			}
		}
	}


	bool ReversiContext::HasValidMove(PLAYER_COLOR player)
	{
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (IsValidMove(row, col, player)) {
					return true;
				}
			}
		}
		return false;
	}

	int ReversiContext::CountDisks(SLOT_STATUS color)
	{
		int count = 0;
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (board[row][col] == color) {
					count++;
				}
			}
		}
		return count;
	}

}
