#pragma once
#include "TicTacToeBoard.h"
#include "GameView.h"
#include <memory>
#include <iostream>
#include <sstream> 

class TicTacToeView : public GameView {
private:
	std::shared_ptr<TicTacToeBoard> mTicTacToeBoard;
	void PrintBoard(std::ostream& s) const override;

public:
	// Constructor with a given Board b that you will be able to view
	TicTacToeView(std::shared_ptr<TicTacToeBoard> b)
		: mTicTacToeBoard(b) {
	}

	std::unique_ptr<GameMove> ParseMove(const std::string& strFormat) const override;
	friend std::ostream& operator<<(std::ostream& lhs, const TicTacToeView& rhs);
	std::string GetPlayerString(int player) const override;
};

std::ostream& operator<<(std::ostream& lhs, const TicTacToeMove& rhs);