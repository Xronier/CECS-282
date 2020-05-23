#pragma once
#include <iostream>
#include <sstream>
#include <array>

class BoardDirection {
private:
	char mRowChange;
	char mColChange;

public:
	BoardDirection();
	BoardDirection(const char& rowChange, const char& colChange);

	inline char getRowChange() const { return mRowChange; }
	inline char getColChange() const { return mColChange; }

	static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;
};


