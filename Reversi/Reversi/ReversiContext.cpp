//#include "ReversiContext.h"
//#include <iostream>
//
//namespace Reversi
//{
//	ReversiContext::ReversiContext() {
//		// 初始化棋盤為 EMPTY
//		for (int i = 0; i < BOARD_SIZE; i++)
//			for (int j = 0; j < BOARD_SIZE; j++)
//				board[i][j] = SLOT_STATUS::EMPTY;
//
//		int center = BOARD_SIZE / 2;
//
//		// 設置初始的 4 顆棋子
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
//			return SLOT_STATUS::EMPTY; // 超出範圍時回傳 EMPTY
//
//		return board[row][column];
//	}
//
//	SLOT_STATUS ReversiContext::SetSlotStatus(int row, int column, SLOT_STATUS status) {
//		if (row < 0 || row >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE)
//			return SLOT_STATUS::EMPTY; // 超出範圍時不做變更
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
		// 初始化棋盤，全部設為 EMPTY
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				board[i][j] = SLOT_STATUS::EMPTY;

		// 設定初始黑白棋子位置
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
		// 如果該位置已經有棋子，則返回 false
		if (board[row][col] != SLOT_STATUS::EMPTY) {
			return false;
		}

		SLOT_STATUS opponent = (player == PLAYER_COLOR::BLACK) ? SLOT_STATUS::WHITE : SLOT_STATUS::BLACK;

		// 檢查周圍8個方向（上下左右、對角線）是否有對方的棋子，並且是否能翻轉
		for (int drow = -1; drow <= 1; ++drow) {
			for (int dcol = -1; dcol <= 1; ++dcol) {
				if (drow == 0 && dcol == 0) {
					continue;  // 跳過自己位置
				}

				int r = row + drow;
				int c = col + dcol;

				bool opponentFound = false;
				// 從這個方向開始，檢查是否有對方棋子
				while (r >= 0 && r < 8 && c >= 0 && c < 8) {
					if (board[r][c] == opponent) {
						opponentFound = true;
					}
					else if (board[r][c] == (player == PLAYER_COLOR::BLACK ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE)) {
						// 如果找到了相同顏色的棋子，並且前面有對方棋子，則為合法
						if (opponentFound) {
							return true;
						}
						break;  // 走到自己棋子就停止檢查
					}
					else {
						break;  // 遇到空格就停止檢查
					}

					// 移動到下一格
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

		// 檢查周圍8個方向
		for (int drow = -1; drow <= 1; ++drow) {
			for (int dcol = -1; dcol <= 1; ++dcol) {
				if (drow == 0 && dcol == 0) {
					continue; // 跳過原地
				}

				int r = row + drow;
				int c = col + dcol;

				// 儲存翻轉的棋子
				BoardPositionVector flippedPositions;

				while (r >= 0 && r < 8 && c >= 0 && c < 8) {
					if (GetSlotStatus(r, c) == opponent) {
						flippedPositions.push_back({ r, c });
					}
					else if (GetSlotStatus(r, c) == (player == PLAYER_COLOR::BLACK ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE)) {
						// 如果找到相同顏色的棋子，且有對方棋子需要翻轉
						for (auto& pos : flippedPositions) {
							// 翻轉這些對方棋子
							SetSlotStatus(pos.first, pos.second, (player == PLAYER_COLOR::BLACK) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE);
						}
						break; // 停止檢查此方向
					}
					else {
						break; // 遇到空格或無法翻轉的情況
					}

					// 繼續在此方向上往前走
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
