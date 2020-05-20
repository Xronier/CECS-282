#pragma once
#include "BoardDirection.h"
#include <vector>
#include <iostream>
#include <sstream>

// Board position is a spot on a board that consists of a row and column
class BoardPosition {
private:
	char mRow;
	char mCol;

public:
	BoardPosition();
	BoardPosition(const char& row, const char& col);

	inline char GetRow() const { return mRow; }
	inline char GetCol() const { return mCol; }

	// Display string as (row, col)
	operator std::string() const;
	// Allow for row and column to be read in the format (row, col)
	friend std::istream& operator>>(std::istream& lhs, BoardPosition& rhs);
	bool operator==(BoardPosition rhs) const;
	bool operator<(BoardPosition rhs);
	// Allow for you to add a BoardDirection to a BoardPosition
	BoardPosition operator+(BoardDirection dir);

	bool InBounds(int boardSize);
	bool InBounds(int rows, int columns);
	
	static std::vector<BoardPosition> GetRectangularPositions(int rows, int columns);
};

std::ostream& operator<<(std::ostream& lhs, BoardPosition rhs);
