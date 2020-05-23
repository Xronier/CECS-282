#include "OthelloView.h"
using namespace std;

void OthelloView::PrintBoard(std::ostream& s) const {
	s << "- 0 1 2 3 4 5 6 7" << endl;
	for (int i = 0; i < mOthelloBoard->BOARD_SIZE; i++) {
		for (int j = 0; j < mOthelloBoard->BOARD_SIZE; j++) {
			if (j == 0) {
				s << i << " ";
			}
			if (mOthelloBoard->mBoard[i][j] == OthelloBoard::Player::EMPTY) {
				s << ". ";
			}
			else if (mOthelloBoard->mBoard[i][j] == OthelloBoard::Player::BLACK) {
				s << "B ";
			}
			else {
				cout << "W ";
			}
		}
		cout << endl;
	}
}

std::ostream& operator<<(std::ostream& lhs, const OthelloView& rhs) {
	rhs.PrintBoard(lhs);
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const OthelloMove& rhs) {
	return lhs << static_cast<string>(rhs);
}

std::unique_ptr<OthelloMove> OthelloView::ParseMove(const std::string& strFormat) {
	istringstream iss(strFormat);
	char miscVar;
	int row, col;

	iss >> miscVar >> row >> miscVar >> col >> miscVar;
	unique_ptr<OthelloMove> m = make_unique<OthelloMove>(BoardPosition(row, col));
	return move(m);
}