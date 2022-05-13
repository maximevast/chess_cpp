// game.h
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "factories.h"
#include "constants.h"
#include "utils.h"

using namespace std;

class Game {
  private:
    piecePtrVector_t board;
    bool lastPlayStore;
    vector<bool> kingHasMoved;
    vector<bool> kingHasBeenInCheck;
    vector<vector<bool>> rookHasMoved;

  public:
    Game();
    void draw();
    piecePtrVector_t get_board();
    bool didWhitePlayed();
    void whitePlayed(bool didThey);
    bool isCheckMate(spriteVector_t figures, Game &game, int color);

    bool doesKingMoved(int color);
    void kingMoved(int color);
    bool doesKingHasBeenInCheck(int color);
    void kingBeenInCheck(int color);
    bool doesRookMoved(int color, int side);
    void rookMoved(int color, int side);
};

#endif
