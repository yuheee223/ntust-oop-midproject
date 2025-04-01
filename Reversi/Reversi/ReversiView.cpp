#include "IReversiView.h"
#include <iostream>


namespace Reversi
{
	class ReversiView : public IReversiView {
	public:
		void Initialize() override {}
		void ShowGameStarting(IReversiContext* context, Callback endCallback) override {
			std::cout << "Game is starting...\n";
			context->PrintBoard();
			endCallback();
		}
		void ShowDiskPlacing(PLAYER_COLOR color, BoardPosition position, Callback endCallback) override {
			std::cout << "Placing " << (color == PLAYER_COLOR::BLACK ? "Black" : "White")
				<< " at (" << position.first << ", " << position.second << ")\n";
			endCallback();
		}
		void ShowDiskFlipping(const BoardPositionVector& positions, Callback endCallback) override {
			std::cout << "Flipping disks at: ";
			for (const auto& pos : positions) {
				std::cout << "(" << pos.first << ", " << pos.second << ") ";
			}
			std::cout << "\n";
			endCallback();
		}
		void ShowStateChanging(GAME_STATE state, GAME_STATE prevState, Callback endCallback) override {
			std::cout << "Game state changed.\n";
			endCallback();
		}
		void ShowPlaceablePreview(PLAYER_COLOR targetColor, const BoardPositionVector& positions) override {}
		void ClearPlaceablePreview() override {}
		void ShowCapturablePreview(const BoardPositionVector& positions) override {}
		void ClearCapturablePreview() override {}

		void ShowGameOver(GAME_STATE state) override
		{
			std::cout << "Game Over!" << std::endl;
			if (state == GAME_STATE::BLACK_WON) {
				std::cout << "Black wins!" << std::endl;
			}
			else if (state == GAME_STATE::WHITE_WON) {
				std::cout << "White wins!" << std::endl;
			}
			else {
				std::cout << "It's a draw!" << std::endl;
			}
		}

	};
}
