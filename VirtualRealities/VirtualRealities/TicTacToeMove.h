#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "BoardPosition.h"
#include "BoardDirection.h"
#include "GameMove.h"

class TicTacToeMove : public GameMove {
private:
	BoardPosition mPosition;
	friend class TicTacToeBoard;

public:
	TicTacToeMove(BoardPosition p) : mPosition(p) {
	}

	bool operator==(const GameMove& rhs) const override;
	operator std::string() const override;

};
