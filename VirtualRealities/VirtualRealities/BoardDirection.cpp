#include "BoardDirection.h"

BoardDirection::BoardDirection()
	: mRowChange(0), mColChange(0) {
}

BoardDirection::BoardDirection(const char& rowChange, const char& colChange)
	: mRowChange(rowChange), mColChange(colChange) {
}

std::array<BoardDirection, 8> BoardDirection::CARDINAL_DIRECTIONS = { BoardDirection(-1, -1), BoardDirection(-1, 0), 
	BoardDirection(-1, 1), BoardDirection(0, -1), BoardDirection(0, 1), BoardDirection(1, -1), BoardDirection(1, 0),
	BoardDirection(1, 1) };