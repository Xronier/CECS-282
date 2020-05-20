#include "OthelloMove.h"
using namespace std;

bool OthelloMove::operator==(const GameMove &rhs) const {
	const OthelloMove& m = dynamic_cast<const OthelloMove&>(rhs);
	return (mPosition == m.mPosition);
}

OthelloMove::operator std::string() const {
	ostringstream os;

	os << "(" << (int)mPosition.GetRow() << ", " << (int)mPosition.GetCol() << ")";
	return os.str();
}

bool OthelloMove::IsPass() const {
	if (mPosition.GetRow() == -1 && mPosition.GetCol() == -1) {
		cout << "\nPassing turn\n";
		return true;
	}
	return false;
}