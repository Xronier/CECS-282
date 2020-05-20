#pragma once
#include <iostream>
#include <sstream>
#include <array>

// A BoardDirection is a change to a row and column
class BoardDirection {
private:
	char mRowChange;
	char mColChange;

public:
	BoardDirection();
	BoardDirection(const char& rowChange, const char& colChange);

	inline char getRowChange() const { return mRowChange; }
	inline char getColChange() const { return mColChange; }

	// An array full of the cardinal directions surrounding a row, col (such as north (0, 2), south (2, 2), etc)
	// but excluding itself (0, 0)
	static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;
};


