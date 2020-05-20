#include "TicTacToeView.h"
using namespace std;

void TicTacToeView::PrintBoard(std::ostream& s) const {
	s << "- 0 1 2" << endl;
	for (int i = 0; i < mTicTacToeBoard->BOARD_SIZE; i++) {
		for (int j = 0; j < mTicTacToeBoard->BOARD_SIZE; j++) {
			if (j == 0) {
				s << i << " ";
			}
			if (mTicTacToeBoard->mBoard[i][j] == TicTacToeBoard::Player::EMPTY) {
				s << ". ";
			}
			else if (mTicTacToeBoard->mBoard[i][j] == TicTacToeBoard::Player::X) {
				s << "X ";
			}
			else {
				s << "O ";
			}
		}
		cout << endl;
	}
}

std::ostream& operator<<(std::ostream& lhs, const TicTacToeView& rhs) {
	rhs.PrintBoard(lhs);
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const TicTacToeMove& rhs) {
	return lhs << static_cast<string>(rhs);
}

std::unique_ptr<GameMove> TicTacToeView::ParseMove(const std::string& strFormat) const {
	istringstream iss(strFormat);
	char miscVar;
	int row, col;

	iss >> miscVar >> row >> miscVar >> col >> miscVar;
	unique_ptr<TicTacToeMove> m = make_unique<TicTacToeMove>(BoardPosition(row, col));
	return move(m);
}

string TicTacToeView::GetPlayerString(int player) const {
	return player == 1 ? "X" : "O";
}