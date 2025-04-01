#include "ReversiGame.h"
#include <iostream>

namespace Reversi
{

	ReversiGame::ReversiGame(IReversiContext* ctx, IReversiInput* inp, IReversiView* vw) : context(ctx), input(inp), view(vw)
	{

	}

	void ReversiGame::Execute()
	{
		view->Initialize();
		view->ShowGameStarting(context, [this]() {
			WaitForPlayerInput();
			});
		//StartGame();
	}

	void ReversiGame::StartGame()
	{
		// initialize the context

		input->SetInputLock(true);
		view->ShowGameStarting(context, [=]() {
			input->SetInputLock(false);
		WaitForPlayerInput();
			});
	}

	void ReversiGame::WaitForPlayerInput()
	{
		std::cout << "Waiting for player input..." << std::endl;

		input->WaitPlacingInput([this](BoardPosition position) {
			std::cout << "Received input: (" << position.first << ", " << position.second << ")" << std::endl;
		if (ProcessDiskPlacement(position)) {
			std::cout << "Move processed!" << std::endl;
			context->PrintBoard(); // 確認棋盤是否更新
			WaitForPlayerInput();  // 讓玩家繼續輸入
		}
		else {
			std::cout << "Invalid move. Try again." << std::endl;
			WaitForPlayerInput();
		}
			});

		//input->SetInputLock(false);
		//// view->ShowPlaceablePreview

		//input->WaitPreviewInput([=](BoardPosition position) {
		//	view->ClearCapturablePreview();
		//	// view->ShowCapturablePreview
		//	});

		//input->WaitPlacingInput([=](BoardPosition position) {
		//	if (ProcessDiskPlacement(position)) {
		//		input->SetInputLock(true);
		//		view->ClearPlaceablePreview();
		//		view->ClearCapturablePreview();
		//	}
		//	});
	}

	bool ReversiGame::ProcessDiskPlacement(BoardPosition placingPosition)
	{
		// If the placement is not valid, return false.
		// Update the board(slot status) to what it will look like after placing this piece on the placingPosition.
		int row = placingPosition.first;
		int col = placingPosition.second;

		// 判斷是否為合法步驟
		if (!context->IsValidMove(row, col, (context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? PLAYER_COLOR::BLACK : PLAYER_COLOR::WHITE)) {
			return false;
		}
		//// 取得當前玩家顏色
		//PLAYER_COLOR currentPlayer = (context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? PLAYER_COLOR::BLACK : PLAYER_COLOR::WHITE;

		//SLOT_STATUS playerSlot = (currentPlayer == PLAYER_COLOR::BLACK) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE;
		//SLOT_STATUS opponentSlot = (currentPlayer == PLAYER_COLOR::BLACK) ? SLOT_STATUS::WHITE : SLOT_STATUS::BLACK;

		//// 先檢查該位置是否為空
		//if (context->GetSlotStatus(row, col) != SLOT_STATUS::EMPTY)
		//{
		//	std::cout << "Invalid move: Slot is not empty!" << std::endl;
		//	return false;
		//}

		//BoardPositionVector capturedDisks; // 存放需要翻轉的棋子

		//// 定義 8 個方向
		//int directions[8][2] = {
		//	{-1, -1}, {-1, 0}, {-1, 1},  // 上方三個方向
		//	{0, -1},         {0, 1},  // 左右方向
		//	{1, -1}, {1, 0}, {1, 1}   // 下方三個方向
		//};

		//// 檢查 8 個方向是否可以翻轉
		//for (auto& dir : directions)
		//{
		//	int dx = dir[0], dy = dir[1];
		//	int r = row + dx, c = col + dy;
		//	BoardPositionVector tempCaptured; // 臨時存放該方向上的棋子

		//	// 先找到連續的對手棋子
		//	while (r >= 0 && r < 8 && c >= 0 && c < 8 && context->GetSlotStatus(r, c) == opponentSlot)
		//	{
		//		tempCaptured.push_back({ r, c });
		//		r += dx;
		//		c += dy;
		//	}

		//	// 檢查是否遇到自己的棋子
		//	if (r >= 0 && r < 8 && c >= 0 && c < 8 && context->GetSlotStatus(r, c) == playerSlot)
		//	{
		//		// 如果遇到自己的棋子，則前面的對手棋子可以翻轉
		//		capturedDisks.insert(capturedDisks.end(), tempCaptured.begin(), tempCaptured.end());
		//	}
		//}

		//// 若沒有要翻轉的棋子，則這步不合法
		//if (capturedDisks.empty())
		//{
		//	std::cout << "Invalid move: No pieces to flip!" << std::endl;
		//	return false;
		//}


		// 如果合法，放置棋子並進行翻轉邏輯
		context->SetSlotStatus(row, col, (context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE);
		// 設置棋子
		//context->SetSlotStatus(row, col, (currentPlayer == PLAYER_COLOR::BLACK) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE);
		std::cout << "Placed " << ((context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? "Black" : "White")
			<< " at (" << row << ", " << col << ")" << std::endl;

		//// 這裡是翻轉邏輯
		context->FlipDisks(row, col);
		//// 翻轉棋子
		//for (auto& pos : capturedDisks)
		//{
		//	context->SetSlotStatus(pos.first, pos.second, playerSlot);
		//}

		// 更新遊戲狀態
		ProcessStateChange();
		//context->SetCurrentState((context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? GAME_STATE::WHITE_TURN : GAME_STATE::BLACK_TURN);

		// 顯示動畫
		// view->ShowDiskPlacing(playerColor, placingPosition, [=]() {
		// 	view->ShowDiskFlipping(capturableDisks, [=]() {
		// 		ProcessStateChange();
		// 	});
		// });
		return true;
	}

	void ReversiGame::ProcessStateChange()
	{
		// auto prevState = context->GetCurrentState();
		// auto nextState = context->SetCurrentState(the next state);

		// view->ShowStateChanging(nextState, prevState, [=]() {
		// 		After the state change show ends...
		// });

		GAME_STATE prevState = context->GetCurrentState();
		GAME_STATE nextState = (prevState == GAME_STATE::BLACK_TURN) ? GAME_STATE::WHITE_TURN : GAME_STATE::BLACK_TURN;

		// 檢查下一位玩家是否有合法步驟
		if (!context->HasValidMove((nextState == GAME_STATE::BLACK_TURN) ? PLAYER_COLOR::BLACK : PLAYER_COLOR::WHITE)) {
			// 若無合法步驟，則讓對手繼續
			nextState = prevState;

			// 若雙方都無法移動，則判定遊戲結束
			if (!context->HasValidMove((prevState == GAME_STATE::BLACK_TURN) ? PLAYER_COLOR::WHITE : PLAYER_COLOR::BLACK)) {
				int blackCount = context->CountDisks(SLOT_STATUS::BLACK);
				int whiteCount = context->CountDisks(SLOT_STATUS::WHITE);

				if (blackCount > whiteCount) {
					nextState = GAME_STATE::BLACK_WON;
				}
				else if (whiteCount > blackCount) {
					nextState = GAME_STATE::WHITE_WON;
				}
				else {
					nextState = GAME_STATE::DRAW;
				}
			}
		}

		context->SetCurrentState(nextState);

		// 顯示狀態變更
		view->ShowStateChanging(nextState, prevState, [=]() {
			if (nextState == GAME_STATE::BLACK_TURN || nextState == GAME_STATE::WHITE_TURN) {
				context->PrintBoard();
				WaitForPlayerInput();
			}
			else {
				view->ShowGameOver(nextState);
			}
			});
	}

	void ReversiGame::RestartGame()
	{
		// Clear the data of prev game.
		StartGame();
	}
}
