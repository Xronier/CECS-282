#pragma once

#include "TicTacToeMove.h";
#include "BoardPosition.h"
#include "GameBoard.h"
#include <array>
#include <memory>
#include <vector>
#include <sstream>

class TicTacToeBoard : public GameBoard {
public:
	enum class Player : char {
		EMPTY = 0,
		X = 1,
		O = -1
	};

	TicTacToeBoard();

	std::vector<std::unique_ptr<GameMove>> GetPossibleMoves() const override;
	void ApplyMove(std::unique_ptr<GameMove> m) override;
	void UndoLastMove() override;
	int GetCurrentPlayer() const override;
	const std::vector<std::unique_ptr<GameMove>>& GetMoveHistory() const override;
	int GetValue() const override;
	static const int BOARD_SIZE = 3;

	inline Player GetPlayerAtPosition(BoardPosition position) const {
		return mBoard[position.GetRow()][position.GetCol()];
	}

	bool IsFinished() const override;

private:
	friend class TicTacToeView;

	void CheckForWinner();

	std::array<std::array<Player, BOARD_SIZE>, BOARD_SIZE> mBoard;
	Player mCurrentPlayer;
	std::vector<std::unique_ptr<GameMove>> mHistory;

	int mCurrentValue;
	int mPasses;

	inline bool InBounds(BoardPosition p) const {
		return p.InBounds(BOARD_SIZE);
	}

	inline bool PositionIsEnemy(BoardPosition position, Player p) const {
		Player atPosition = GetPlayerAtPosition(position);
		return atPosition != Player::EMPTY && atPosition != p;
	}
};