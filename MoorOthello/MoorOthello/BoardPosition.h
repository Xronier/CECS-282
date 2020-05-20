#pragma once
#include "BoardDirection.h"
#include <vector>
#include <iostream>
#include <sstream>

class BoardPosition {
private:
	char mRow;
	char mCol;

public:
	BoardPosition();
	BoardPosition(const char& row, const char& col);

	inline char GetRow() const { return mRow; }
	inline char GetCol() const { return mCol; }

	operator std::string() const;
	friend std::istream& operator>>(std::istream& lhs, BoardPosition& rhs);
	bool operator==(BoardPosition rhs);
	bool operator<(BoardPosition rhs);
	BoardPosition operator+(BoardDirection dir);

	bool InBounds(int boardSize);
	bool InBounds(int rows, int columns);
	
	static std::vector<BoardPosition> GetRectangularPositions(int rows, int columns);
};

std::ostream& operator<<(std::ostream& lhs, BoardPosition rhs);
