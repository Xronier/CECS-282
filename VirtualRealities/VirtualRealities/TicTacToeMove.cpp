#include "TicTacToeMove.h"
using namespace std;

bool TicTacToeMove::operator==(const GameMove& rhs) const {
	const TicTacToeMove& m = dynamic_cast<const TicTacToeMove&>(rhs);
	return (mPosition == m.mPosition);
}

TicTacToeMove::operator std::string() const {
	ostringstream os;

	os << "(" << (int)mPosition.GetRow() << ", " << (int)mPosition.GetCol() << ")";
	return os.str();
}