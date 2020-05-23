#include "BoardPosition.h"

using namespace std;

BoardPosition::BoardPosition()
	: mRow(0), mCol(0) {
}

BoardPosition::BoardPosition(const char& row, const char& col)
	: mRow(row), mCol(col) {
}



BoardPosition::operator std::string() const{
	ostringstream os;

	os << "(" << (int)mRow << ", " << (int)mCol << ")";
	return os.str();
}

std::ostream& operator<<(std::ostream& lhs, BoardPosition rhs) {
	lhs << static_cast<string>(rhs);
	return lhs;
}

std::istream& operator>>(std::istream& lhs, BoardPosition& rhs) {
	char miscvar;

	lhs >> miscvar >> rhs.mRow >> miscvar >> rhs.mCol >> miscvar;
	return lhs;
}

bool BoardPosition::operator==(BoardPosition rhs) {
	return (mRow == rhs.mRow) && (mCol == rhs.mCol);
}

bool BoardPosition::operator<(BoardPosition rhs) {
	if (mRow == rhs.mRow) {
		return mCol < rhs.mCol;
	}
	return mRow < rhs.mRow;
}

bool BoardPosition::InBounds(int boardSize) {
	return (mRow < boardSize && mRow >= 0 && mCol < boardSize && mCol >= 0);
}

bool BoardPosition::InBounds(int rows, int columns) {
	return (mRow <= rows && mRow >= 0 && mCol <= columns && mCol >= 0);
}

std::vector<BoardPosition> BoardPosition::GetRectangularPositions(int rows, int columns) {
	vector<BoardPosition> board;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			board.push_back(BoardPosition(i, j));
		}
	}
	return board;
}

BoardPosition BoardPosition::operator+(BoardDirection dir) {
	return BoardPosition(mRow + dir.getRowChange(), mCol + dir.getColChange());
}