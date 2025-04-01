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
			context->PrintBoard(); // �T�{�ѽL�O�_��s
			WaitForPlayerInput();  // �����a�~���J
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

		// �P�_�O�_���X�k�B�J
		if (!context->IsValidMove(row, col, (context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? PLAYER_COLOR::BLACK : PLAYER_COLOR::WHITE)) {
			return false;
		}
		//// ���o��e���a�C��
		//PLAYER_COLOR currentPlayer = (context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? PLAYER_COLOR::BLACK : PLAYER_COLOR::WHITE;

		//SLOT_STATUS playerSlot = (currentPlayer == PLAYER_COLOR::BLACK) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE;
		//SLOT_STATUS opponentSlot = (currentPlayer == PLAYER_COLOR::BLACK) ? SLOT_STATUS::WHITE : SLOT_STATUS::BLACK;

		//// ���ˬd�Ӧ�m�O�_����
		//if (context->GetSlotStatus(row, col) != SLOT_STATUS::EMPTY)
		//{
		//	std::cout << "Invalid move: Slot is not empty!" << std::endl;
		//	return false;
		//}

		//BoardPositionVector capturedDisks; // �s��ݭn½�઺�Ѥl

		//// �w�q 8 �Ӥ�V
		//int directions[8][2] = {
		//	{-1, -1}, {-1, 0}, {-1, 1},  // �W��T�Ӥ�V
		//	{0, -1},         {0, 1},  // ���k��V
		//	{1, -1}, {1, 0}, {1, 1}   // �U��T�Ӥ�V
		//};

		//// �ˬd 8 �Ӥ�V�O�_�i�H½��
		//for (auto& dir : directions)
		//{
		//	int dx = dir[0], dy = dir[1];
		//	int r = row + dx, c = col + dy;
		//	BoardPositionVector tempCaptured; // �{�ɦs��Ӥ�V�W���Ѥl

		//	// �����s�򪺹��Ѥl
		//	while (r >= 0 && r < 8 && c >= 0 && c < 8 && context->GetSlotStatus(r, c) == opponentSlot)
		//	{
		//		tempCaptured.push_back({ r, c });
		//		r += dx;
		//		c += dy;
		//	}

		//	// �ˬd�O�_�J��ۤv���Ѥl
		//	if (r >= 0 && r < 8 && c >= 0 && c < 8 && context->GetSlotStatus(r, c) == playerSlot)
		//	{
		//		// �p�G�J��ۤv���Ѥl�A�h�e�������Ѥl�i�H½��
		//		capturedDisks.insert(capturedDisks.end(), tempCaptured.begin(), tempCaptured.end());
		//	}
		//}

		//// �Y�S���n½�઺�Ѥl�A�h�o�B���X�k
		//if (capturedDisks.empty())
		//{
		//	std::cout << "Invalid move: No pieces to flip!" << std::endl;
		//	return false;
		//}


		// �p�G�X�k�A��m�Ѥl�öi��½���޿�
		context->SetSlotStatus(row, col, (context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE);
		// �]�m�Ѥl
		//context->SetSlotStatus(row, col, (currentPlayer == PLAYER_COLOR::BLACK) ? SLOT_STATUS::BLACK : SLOT_STATUS::WHITE);
		std::cout << "Placed " << ((context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? "Black" : "White")
			<< " at (" << row << ", " << col << ")" << std::endl;

		//// �o�̬O½���޿�
		context->FlipDisks(row, col);
		//// ½��Ѥl
		//for (auto& pos : capturedDisks)
		//{
		//	context->SetSlotStatus(pos.first, pos.second, playerSlot);
		//}

		// ��s�C�����A
		ProcessStateChange();
		//context->SetCurrentState((context->GetCurrentState() == GAME_STATE::BLACK_TURN) ? GAME_STATE::WHITE_TURN : GAME_STATE::BLACK_TURN);

		// ��ܰʵe
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

		// �ˬd�U�@�쪱�a�O�_���X�k�B�J
		if (!context->HasValidMove((nextState == GAME_STATE::BLACK_TURN) ? PLAYER_COLOR::BLACK : PLAYER_COLOR::WHITE)) {
			// �Y�L�X�k�B�J�A�h������~��
			nextState = prevState;

			// �Y���賣�L�k���ʡA�h�P�w�C������
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

		// ��ܪ��A�ܧ�
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
