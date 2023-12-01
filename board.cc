#include "board.h"
#include <memory>
using namespace std;

unique_ptr<Piece> makePiece (char pieceChar) {
    pieceChar = toupper(pieceChar);
    if (pieceChar == 'K') {
        return make_unique<King>();
    } else if (pieceChar == 'Q') {
        return make_unique<Queen>();
    } else if (pieceChar == 'R') {
        return make_unique<Rook>();
    } else if (pieceChar == 'B') {
        return make_unique<Bishop>();
    } else if (pieceChar == 'N') {
        return make_unique<Knight>();
    } else if (pieceChar == 'P') {
        return make_unique<Pawn>();
    }
    return nullptr;
}


bool Board::containsWhiteKing() {
    for (Piece* p : availableWhites) {
        if (dynamic_cast<King*>(p) != nullptr) {
            return true;
        }
    }
    return false;
}

bool Board::containsBlackKing() {
    for (Piece* p : availableBlacks) {
        if (dynamic_cast<King*>(p) != nullptr) {
            return true;
        }
    }
    return false;
}

void Board::clearBoard() {
    theBoard.clear();
}

void Board::initializeBoard() {
    clearBoard();
    int boardSize = 8;

    theBoard.resize(boardSize); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < boardSize; ++i) {
        theBoard[i].resize(boardSize);
    }

    theBoard[0][0].addPiece (make_unique<Rook>().get());
    theBoard[0][1].addPiece (make_unique<Knight>().get());
    theBoard[0][2].addPiece (make_unique<Bishop>().get());
    theBoard[0][3].addPiece (make_unique<Queen>().get());
    theBoard[0][4].addPiece (make_unique<King>().get());
    theBoard[0][5].addPiece (make_unique<Bishop>().get());
    theBoard[0][6].addPiece (make_unique<Knight>().get());
    theBoard[0][7].addPiece (make_unique<Rook>().get());

    for (int i = 0; i < boardSize; ++i) {
        theBoard[0][i].getPiece()->setColour('b');
    }

    theBoard[7][0].addPiece (make_unique<Rook>().get());
    theBoard[7][1].addPiece (make_unique<Knight>().get());
    theBoard[7][2].addPiece (make_unique<Bishop>().get());
    theBoard[7][3].addPiece (make_unique<Queen>().get());
    theBoard[7][4].addPiece (make_unique<King>().get());
    theBoard[7][5].addPiece (make_unique<Bishop>().get());
    theBoard[7][6].addPiece (make_unique<Knight>().get());
    theBoard[7][7].addPiece (make_unique<Rook>().get());

    for (int i = 0; i < boardSize; ++i) {
        theBoard[7][i].getPiece()->setColour('w');
    }

    for (int i = 0; i < 7; ++i) {
        theBoard[1][i].addPiece(make_unique<Pawn>().get());
        theBoard[1][i].getPiece()->setColour('b');
        theBoard[6][i].addPiece(make_unique<Pawn>().get());
        theBoard[6][i].getPiece()->setColour('w');
    }

}

void Board::setup() {
    clearBoard();
    int boardSize = 8;

    theBoard.resize(boardSize); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < boardSize; ++i) {
        theBoard[i].resize(boardSize);
    }

    string input;
    while (cin >> input) {
        if (input == "done") {
            if (containsBlackKing() && containsWhiteKing()) {
                break;
            }
        } else if (input == "+") {
            char piece;
            string place;
            cin >> piece >> place;
            Move placement = Move(place, place, *this);

            bool white = false;
            if (65 <= piece && piece <= 90) {
                white = true;
            }

            theBoard[placement.getInitX()][placement.getInitY()].addPiece(makePiece(piece).get());
            
            if (white) {
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('w');
            } else {
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('b');
            }

        } else if (input == "-") {
            string place;
            cin >> place;
            Move placement = Move(place, place, *this);
            theBoard[placement.getInitX()][placement.getInitY()].removePiece();
        }
    }
}

void Board::incrMoveCounter() {
    ++moveCounter;
}

vector<vector<Square>> Board::getBoard() {
    return theBoard;
}
