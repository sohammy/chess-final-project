#include "human.h"
using namespace std;


Human::Human() {}

void Human::makeMove(Board& gameBoard) { // add colour to this so that we can only move the right pieces
    string pieceSelected, destination;
    bool foundMove = false;

    while(!foundMove){
        cin >> pieceSelected >> destination;
        Move moveAttempted = Move(pieceSelected, destination, gameBoard.getBoard());

        Square* start = &gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()]; 
        Piece* piece = start->getPiece();
        piece->calculateMoves();

        int successIndex = 0;
        vector<Move> possibleMoves = piece->getMoves();
        for(Move m : possibleMoves) {
            if (moveAttempted.isEqual(m)) { 
                foundMove = true;
                break;
            }
            ++successIndex;
        }
        
        if(foundMove) {
            Move successfulMove = possibleMoves[successIndex];
            Square* dest = successfulMove.getSquare();

            if(dest->getPiece() != nullptr) {
                dest->removePiece();
            }
            dest->addPiece(piece);
            piece->setSquare(dest);
            start->removePiece();
            piece->pieceMoved();
            dest->notifyDisplayObservers();
            start->notifyDisplayObservers();
            // cout << "error is in start->notifyPieceObservers" << endl;
            // start->notifyPieceObservers();
            // cout << "nvm error is in dest->notifyPieceObservers" << endl;
            // dest->notifyPieceObservers();
        } else {
            cout << "Please make a valid move" << endl;
        }
    }
}
