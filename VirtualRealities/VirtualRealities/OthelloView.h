#pragma once
#include "OthelloBoard.h"
#include "GameView.h"
#include <memory>
#include <iostream>
#include <sstream> 

class OthelloView : public GameView {
private:
	// An OthelloView shares ownership of an OthelloBoard object.
	std::shared_ptr<OthelloBoard> mOthelloBoard;

	// Prints JUST the board (including row/column headers) to the given ostream object.
	void PrintBoard(std::ostream& s) const override;

public:
	// Constructs an OthelloView over an existing Board object. The View participates
	// as a shared owner of the Board.
	OthelloView(std::shared_ptr<OthelloBoard> b) 
		: mOthelloBoard(b) {
	}

	// Creates and returns ownership of an OthelloMove object by parsing a string
	// of the format (r, c) and constructing a corresponding Move object. Yields
	// ownership of the created Move.
	// You can assume that the string contains a valid move format.
	std::unique_ptr<GameMove> ParseMove(const std::string &strFormat) const override;

	friend std::ostream& operator<<(std::ostream &lhs, const OthelloView &rhs);

	std::string GetPlayerString(int player) const override;

};

// It doesn't belong to the OthelloView class, but we still consider this operator
// to be part of the "view". This operator prints a Move by printing its position.
// Reminder: OthelloMove has operator std::string.
std::ostream& operator<<(std::ostream &lhs, const OthelloMove &rhs);
