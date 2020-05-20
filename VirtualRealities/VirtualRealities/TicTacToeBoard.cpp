#include "TicTacToeBoard.h"
using namespace std;

TicTacToeBoard::TicTacToeBoard()
	: mCurrentValue(0), mCurrentPlayer(Player::X), mBoard({Player::EMPTY}), mPasses(0) {
}

int TicTacToeBoard::GetCurrentPlayer() const {
	return mCurrentPlayer == Player::X ? 1 : 2;
}

const std::vector<std::unique_ptr<GameMove>>& TicTacToeBoard::GetMoveHistory() const {
	return mHistory;
}

int TicTacToeBoard::GetValue() const {
	return mCurrentValue;
}

bool TicTacToeBoard::IsFinished() const {
	return mCurrentValue != 0 || mHistory.size() == 9;
}

void TicTacToeBoard::CheckForWinner() {
	for (auto pos : BoardPosition::GetRectangularPositions(mBoard.size(), mBoard.size())) {
		for (auto dir : BoardDirection::CARDINAL_DIRECTIONS) {
			BoardPosition current = pos;
			bool threeInARow = true;

			for (int steps = 0; steps < 3; steps++) {
				if (!InBounds(current) || mCurrentPlayer != GetPlayerAtPosition(current)) {
					threeInARow = false;
					break;
				}
				current = current + dir;
			}

			if (threeInARow) {
				mCurrentValue = static_cast<int>(mCurrentPlayer);
				return;
			}
		}
	}
}

// The only requirement to apply a move is for the space to be empty
void TicTacToeBoard::ApplyMove(std::unique_ptr<GameMove> mv) {
	TicTacToeMove* m = dynamic_cast<TicTacToeMove*>(mv.get());
	mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = mCurrentPlayer;

	CheckForWinner();

	mHistory.push_back(std::move(mv));
	mCurrentPlayer = mCurrentPlayer == Player::X ? Player::O : Player::X;
}

// A move is considered possible a space is empty
vector<unique_ptr<GameMove>> TicTacToeBoard::GetPossibleMoves() const {
	vector<unique_ptr<GameMove>> possibleMoves;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (mBoard[i][j] == Player::EMPTY) {
				possibleMoves.push_back(std::make_unique<TicTacToeMove>(BoardPosition(i, j)));
			}
		}
	}
	return possibleMoves;
}

void TicTacToeBoard::UndoLastMove() {
	TicTacToeMove* lastMove = dynamic_cast<TicTacToeMove*>(mHistory.back().get());

	mBoard[lastMove->mPosition.GetRow()][lastMove->mPosition.GetCol()] = Player::EMPTY;
	mHistory.pop_back();
	mCurrentPlayer = mCurrentPlayer == Player::X ? Player::O : Player::X;
}
