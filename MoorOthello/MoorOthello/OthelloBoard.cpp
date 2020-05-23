#include "OthelloBoard.h"
using namespace std;

OthelloBoard::OthelloBoard()
	: mCurrentValue(0), mCurrentPlayer(Player::BLACK), mBoard(), mPasses(0) {
	mBoard = { Player::EMPTY };
	mBoard[3][3] = Player::WHITE;
	mBoard[3][4] = Player::BLACK;
	mBoard[4][3] = Player::BLACK;
	mBoard[4][4] = Player::WHITE;
}



void OthelloBoard::ApplyMove(std::unique_ptr<OthelloMove> m) {
	if (!m->IsPass()) {
		mPasses = 0;
		mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = GetCurrentPlayer();
		mCurrentValue = GetCurrentPlayer() == Player::BLACK ? mCurrentValue + 1 : mCurrentValue - 1;

		for (BoardDirection dir : BoardDirection::CARDINAL_DIRECTIONS) {
			BoardPosition newSpot(m->mPosition.GetRow() + dir.getRowChange(), m->mPosition.GetCol() + dir.getColChange());
			char enemies = 0;

			while (InBounds(newSpot) && GetPlayerAtPosition(newSpot) != Player::EMPTY) {
				BoardPosition oldSpot(newSpot.GetRow() - dir.getRowChange(), newSpot.GetCol() - dir.getColChange());

				enemies = PositionIsEnemy(newSpot, GetCurrentPlayer()) ? enemies + 1 : enemies + 0;

				while (enemies > 0 && (GetPlayerAtPosition(newSpot) == GetCurrentPlayer())) {
					m->AddFlipSet(OthelloMove::FlipSet(enemies, dir));
					mBoard[oldSpot.GetRow()][oldSpot.GetCol()] = GetCurrentPlayer();
					enemies -= 1;
					// Add 2 b/c you flip an enemy and place your piece
					mCurrentValue = GetCurrentPlayer() == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
					oldSpot = oldSpot + BoardDirection(-(dir.getRowChange()), -(dir.getColChange()));
				}

				if (GetPlayerAtPosition(newSpot) == GetCurrentPlayer() && enemies == 0) {
					break;
				}
				newSpot = newSpot + BoardDirection(dir.getRowChange(), dir.getColChange());
			}
		}
	}
	else {
		mPasses++;
	}
	mCurrentPlayer = GetCurrentPlayer() == Player::BLACK ? Player::WHITE : Player::BLACK;
	mHistory.push_back(move(m));
}

// itr through board
// if you find an empty space look around it
// if, around that empty space, you find an enemy, keep going in the enemies direction
// if you find a friendly piece at the end, you can place a piece in the opposite end, making it a possible move
// add that move into list and continue searching
vector<std::unique_ptr<OthelloMove>> OthelloBoard::GetPossibleMoves() const {
	vector<std::unique_ptr<OthelloMove>> possibleMoves;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {

			bool duplicate = (mBoard[i][j] == Player::EMPTY) ? false : true;
			for (BoardDirection dir : BoardDirection::CARDINAL_DIRECTIONS) {
				BoardPosition newSpot(dir.getRowChange() + i, dir.getColChange() + j);

				while (InBounds(newSpot) && mBoard[newSpot.GetRow()][newSpot.GetCol()] != Player::EMPTY) {
					if (mBoard[newSpot.GetRow()][newSpot.GetCol()] != GetCurrentPlayer()) { // implies it's an enemy
						while (InBounds(newSpot) && PositionIsEnemy(newSpot, GetCurrentPlayer())) {
							BoardPosition newrSpot(newSpot.GetRow() + dir.getRowChange(), newSpot.GetCol() + dir.getColChange());

							if (InBounds(newrSpot) && mBoard[newrSpot.GetRow()][newrSpot.GetCol()] == GetCurrentPlayer() && !duplicate) {
								possibleMoves.push_back(std::make_unique<OthelloMove>(BoardPosition(i, j)));
								duplicate = true;
								break;
							}
							newSpot = newSpot + BoardDirection(dir.getRowChange(), dir.getColChange());
						}
					}
					break;
				}
			}
		}
	}

	if (possibleMoves.size() == 0) {
		possibleMoves.push_back(std::make_unique<OthelloMove>(BoardPosition(-1, -1)));
	}
	return possibleMoves;
}
// Look for flip in flipset
// walk in the direction of flip mFlipCount times
void OthelloBoard::UndoLastMove() {
	auto lastMove = GetMoveHistory().back().get(); // BOARD POSITION
	mPasses = (mPasses == 1) ? 0 : 0;

	for (OthelloMove::FlipSet flip : lastMove->mFlips) {
		mCurrentValue = GetCurrentPlayer() == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
		mBoard[lastMove->mPosition.GetRow()][lastMove->mPosition.GetCol()] = Player::EMPTY;
		auto undo = lastMove->mPosition + flip.mDirection;
		while (flip.mFlipCount != 0) {
			mCurrentValue = GetCurrentPlayer() == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
			mBoard[undo.GetRow()][undo.GetCol()] = GetCurrentPlayer();
			undo = undo + flip.mDirection;
			flip.mFlipCount -= 1;
		}
	}
	mHistory.pop_back();
	mCurrentPlayer = GetCurrentPlayer() == Player::BLACK ? Player::WHITE : Player::BLACK;
}