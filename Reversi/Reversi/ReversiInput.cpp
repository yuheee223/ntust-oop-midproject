#include "IReversiInput.h"
#include <iostream>

namespace Reversi
{
	class ReversiInput : public IReversiInput {
	public:
		void WaitPreviewInput(PositionCallback callback) override {}

		void WaitPlacingInput(PositionCallback callback) override {
			int row, col;
			while (true) {
				std::cout << "Enter move (row col): ";
				std::cin >> row >> col;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input. Try again.\n";
					continue;
				}
				callback(BoardPosition(row, col));
				break;
			}
		}

		void SetInputLock(bool lockState) override {}
	};

	///**
	//* Waits for the player to input a preview position.
	//* This function is used to notify the game time to highlight all possible capturable before placing a piece on specified position.
	//*
	//* \param callback A callback function that is triggered when the player selects a preview position.
	//*                 For example, if the player hovers over (3,4), the callback will be called with (3,4).
	//*/
	//void WaitPreviewInput(PositionCallback callback) {}

	///**
	//* Waits for the player to input a move for placing a piece.
	//* This function is used to notify the game the player want to make a move.
	//*
	//* \param callback A callback function that is triggered when the player selects a position to place a piece.
	//*                 For example, if the player clicks on (5,3) to place a piece, the callback will be called with (5,3).
	//*/
	//void WaitPlacingInput(PositionCallback callback) {}

	///**
	//* Enables or disables input locking.
	//* When input is locked, player interactions (such as placing a piece) are ignored.
	//* This is useful for preventing input during animations or state transitions.
	//*
	//* \param lockState If true, input will be locked; if false, input will be enabled.
	//*/
	//void SetInputLock(bool lockState) {}
}
