// factories.cpp

#include "headers/factories.h"

Piece* PieceFactory::make(int color, int type, string coords, int id) {
  Piece* piece;
  switch(type) {
    case KING   : piece = new King(color, coords, id)   ; break;
    case QUEEN  : piece = new Queen(color, coords, id)  ; break;
    case ROOK   : piece = new Rook(color, coords, id)   ; break;
    case BISHOP : piece = new Bishop(color, coords, id) ; break;
    case KNIGHT : piece = new Knight(color, coords, id) ; break;
    case PAWN   : piece = new Pawn(color, coords, id)   ; break;
  }
  return piece;
}
