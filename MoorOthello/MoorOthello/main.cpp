#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

int main(int argc, char* argv[]) {
	//// Initialization
	//auto board = std::make_shared<OthelloBoard>(); // the state of the game board
	//OthelloView v(board); // a View for outputting the board via operator<<
	//string userInput; // a string to hold the user's command choice



	//// Start with this DEBUGGING CODE to make sure your basic OthelloMove and 
	//// OthelloBoard classes work, then remove it when you are ready to work
	//// on the real main.
	//cout << "Initial board:" << endl;
	//cout << v << endl;
	//unique_ptr<OthelloMove> m{ v.ParseMove("(3, 2)") };
	//cout << "Applying the move " << *m << endl;
	//board->ApplyMove(std::move(m));
	//cout << endl << v << endl; // should show a changed board.

	//
	//m = v.ParseMove("(4, 2)");
	//cout << "Applying the move " << *m << endl;
	//board->ApplyMove(std::move(m));
	//cout << endl << v << endl;

	//m = v.ParseMove("(5, 2)");
	//cout << "Applying the move " << *m << endl;
	//board->ApplyMove(std::move(m));
	//cout << endl << v << endl;

	//// END OF DEBUGGING CODE

	//// Main loop
	//do {
	//	// Print the game board using the OthelloView object

	//   // Print all possible moves

	//   // Ask to input a command

	//   // Command loop:
	//	  // move (r,c)
	//	  // undo n
	//	  // showValue
	//	  // showHistory
	//	  // quit

	//} while (true); // you may want to change the condition

	std::shared_ptr<OthelloBoard> board = std::make_shared<OthelloBoard>();
	OthelloView view(board);
	cout << view;

	while (!board->IsFinished()) {
		string turn = board->GetCurrentPlayer() == OthelloBoard::Player::BLACK ? "Black" : "White";

		cout << endl << turn << "'s move: " << endl;
		cout << "Possible Moves: " << endl;

		auto possibleMoves = board->GetPossibleMoves();
		for (int i = 0; i < possibleMoves.size(); i++) {
			if (*possibleMoves[i] == BoardPosition(-1, -1)) {
				cout << "pass";
			}
			else {
				cout << *possibleMoves[i];
			}
		}
		cout << endl;

		string userInput;
		cout << "Make a choice: ";
		getline(cin, userInput);
				cout << endl;

		if (userInput.substr(0, 4) == "move") {
			bool validMove = false;
			if (userInput.substr(5) == "pass") {
				board->ApplyMove(std::make_unique<OthelloMove>());
				validMove = true;
			}
			std::unique_ptr<OthelloMove> userMove = view.ParseMove(userInput.substr(5, 11));
			for (int i = 0; i < possibleMoves.size(); i++) {
				if (*userMove == *possibleMoves[i]) {
					board->ApplyMove(std::move(userMove));
					validMove = true;
					break;
				}
			}
			if (!validMove) {
				cout << "Not a valid move" << endl << endl;
			}
			cout << view;
		}

		else if (userInput == "showValue") {
			cout << endl << "The board value is: " << board->GetValue() << endl;
		}

		else if (userInput == "showHistory") {
			cout << endl;
			OthelloBoard::Player player = board->GetCurrentPlayer();
			string playerStr = "";

			for (int i = board->GetMoveHistory().size() - 1; i >= 0; i--) {
				if (player == OthelloBoard::Player::BLACK) {
					player = OthelloBoard::Player::WHITE;
					playerStr = "White";
				}
				else {
					player = OthelloBoard::Player::BLACK;
					playerStr = "Black";
				}
				if (*board->GetMoveHistory()[i] == OthelloMove(BoardPosition(-1, -1))) {
					cout << playerStr << ": " << "pass" << endl;;
				}
				else {
					cout << playerStr << ": " << *board->GetMoveHistory()[i] << endl;

				}
				cout << endl;
			}
		}

		else if (userInput.substr(0, 4) == "undo") {
			stringstream s(userInput.substr(5));
			int undoAmount = 0;

			s >> undoAmount;
			if (!(undoAmount > board->GetMoveHistory().size())) {
				for (int i = 0; i < undoAmount; i++) {
					board->UndoLastMove();
				}
			}
			else {
				cout << "History not long enough for that length of undo" << endl << endl;
			}
			cout << view;
		}

		else if (userInput == "q") {
			break;
		}
	}

	if (board->GetValue() > 0) {
		cout << "Game over. Black wins!";
	}
	else if (board->GetValue() < 0) {
		cout << "Game over. White wins!";
	}
	else {
		cout << "Game over. We have a tie!";
	}
}