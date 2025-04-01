#pragma once
#include "IReversiContext.h"
#include "IReversiInput.h"
#include "IReversiView.h"

namespace Reversi
{
	/**
	* Represents the core game logic for Reversi.
	* Manages the game state, processes player moves, and coordinates with the view and input.
	*/
	class ReversiGame
	{
	private:
		IReversiContext* context;
		IReversiInput* input;
		IReversiView* view;
		BoardPositionVector placeablePositions;
		BoardPositionVector positionBuffer;

		void StartGame();
		void WaitForPlayerInput();
		bool ProcessDiskPlacement(BoardPosition placingPosition);
		void ProcessStateChange();
		void RestartGame();
		bool IsGameOver();

	public:
		ReversiGame(IReversiContext*, IReversiInput*, IReversiView*);
		void Execute();
	};
}
