#include "GameBoard.h"
#include "GameMove.h"
#include "GameView.h"
#include "OthelloBoard.h"
#include "OthelloMove.h"
#include "OthelloView.h"
#include "ConnectFourBoard.h"
#include "ConnectFourMove.h"
#include "ConnectFourView.h"
#include "TicTacToeBoard.h"
#include "TicTacToeMove.h";
#include "TicTacToeView.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

int main(int argc, char* argv[]) {
    shared_ptr<GameBoard> board;
    unique_ptr<GameView> view;
    bool endGame = false;

    while (endGame != true) {
        string gameChoice;
        cout << "What game would you like to play?\n"
            << "1) Othello 2) TicTacToe 3) Connect Four 4) Nothing\n";
        getline(cin, gameChoice);

        // Othello creation
        if (gameChoice == "1") {
            auto oBoard = make_shared<OthelloBoard>();
            view = make_unique<OthelloView>(oBoard);
            board = oBoard;
            cout << "\nCommands: \n";
            cout << "move (r, c)\n"
                << "undo #\n"
                << "showValue\n"
                << "showHistory\n"
                << "quit" << "\n\n";
        }
        // TicTacToe creation
        else if (gameChoice == "2") {
            auto tBoard = make_shared<TicTacToeBoard>();
            view = make_unique<TicTacToeView>(tBoard);
            board = tBoard;
            cout << "\nCommands: \n";
            cout << "move (r, c)\n"
                << "undo #\n"
                << "showValue\n"
                << "showHistory\n"
                << "quit" << "\n\n";
        }
        // Connect Four creation
        else if (gameChoice == "3") {
            auto cBoard = make_shared<ConnectFourBoard>();
            view = make_unique<ConnectFourView>(cBoard);
            board = cBoard;
            cout << "\nCommands: \n";
            cout << "move C\n"
                << "undo #\n"
                << "showValue\n"
                << "showHistory\n"
                << "quit" << "\n\n";
        }
        // User wants to end program
        else if (gameChoice == "4") {
            cout << "alright chief";
            break;
        }

        // Game loop
        while (!board->IsFinished()) {
            string turn = view->GetPlayerString(board->GetCurrentPlayer());

            cout << *view;
            cout << turn << "'s move:\n";
            cout << "Possible Moves:\n";
            // Create vector of possible moves
            std::vector<std::unique_ptr<GameMove>> possibleMoves = board->GetPossibleMoves();
            for (int i = 0; i < possibleMoves.size(); i++) {
                    cout << static_cast<string>(*possibleMoves[i]);
            }
            cout << "\n";

            // Get user's command
            string userInput;
            cout << "Make a choice: ";
            getline(cin, userInput);

            // User wants to move
            if (userInput.substr(0, 4) == "move") {
                bool validMove = false;
                std::unique_ptr<GameMove> userMove = view->ParseMove(userInput.substr(5));

                // Check if userMove is in the possibleMoves vector
                for (int i = 0; i < possibleMoves.size(); i++) {
                    if (*userMove == *possibleMoves[i]) {
                        board->ApplyMove(std::move(userMove));
                        validMove = true;
                        break;
                    }
                }

                if (!validMove) {
                    cout << "Not a valid move\n";
                }
            }

            // User wants to show who's winning
            else if (userInput == "showValue") {
                cout << "\nThe board value is: " << board->GetValue() << "\n";
            }

            // User wants to see game history
            else if (userInput == "showHistory") {
                cout << "\n";
                if (board->GetMoveHistory().size() == 0) {
                    cout << "No history exists\n";
                }
                else {
                    string player = board->GetCurrentPlayer() == 2 ? view->GetPlayerString(2) : view->GetPlayerString(1);

                    for (int i = board->GetMoveHistory().size() - 1; i >= 0; i--) {
                        // Since previous player is the first to show up in move history, make player string the other player
                        if (player == view->GetPlayerString(1)) {
                            player = view->GetPlayerString(2);
                        }
                        else {
                            player = view->GetPlayerString(1);
                        }

                        cout << player << ": " << static_cast<string>(*board->GetMoveHistory()[i]) << "\n";
                    }
                }
            }

            // User wants to undo move
            else if (userInput.substr(0, 4) == "undo") {
                stringstream s(userInput.substr(5));
                int undoAmount = 0;

                s >> undoAmount;
                if (undoAmount > board->GetMoveHistory().size()) {
                    cout << "\nHistory not long enough for that length of undo\n";
                }
                else {
                    for (int i = 0; i < undoAmount; i++) {
                        board->UndoLastMove();
                    }
                }
            }
            // User wants to quit the current game
            else if (userInput == "quit") {
                break;
            }

            else {
                cout << "\nInvalid command\n";
            }

            cout << "\n";
        }

        // Get winner of current game
        if (board->GetValue() > 0) {
            cout << *view;
            cout << "Game over. " << view->GetPlayerString(1) << " wins!\n";
        }
        else if (board->GetValue() < 0) {
            cout << *view;
            cout << "Game over. " << view->GetPlayerString(2) << " wins!\n";
        }
        else {
            cout << *view;
            cout << "Game over. We have a tie!\n";
        }
        cout << "\n";
    }
}