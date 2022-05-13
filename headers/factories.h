// factories.h
#ifndef FACTORIES_H
#define FACTORIES_H

#include "constants.h"
#include "piece.h"

using namespace std;


class PieceFactory {
  public:
    static Piece* make(int color, int type, string coords, int id);
};

#endif
