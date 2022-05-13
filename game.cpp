// game.cpp

#include "headers/game.h"

Game::Game() {
  this->board.resize(32);
  this->lastPlayStore = false;
  this->kingHasBeenInCheck = {false, false};
  this->kingHasMoved = {false, false};
  this->rookHasMoved = {{false, false}, {false, false}};
}
PieceFactory piece_factory = PieceFactory();
void Game::draw() {
    for(int i=0; i<32; i++) {
      int color = boost::get<int>(PIECES_DEF[i].find("color")->second);
      int type = boost::get<int>(PIECES_DEF[i].find("type")->second);
      string coords = boost::get<string>(PIECES_DEF[i].find("coords")->second);
      int id = boost::get<int>(PIECES_DEF[i].find("id")->second);
      this->board[i] = piece_factory.make(color, type, coords, id);
    }
}

piecePtrVector_t Game::get_board() {
  return this->board;
}

bool Game::didWhitePlayed() {
  return this->lastPlayStore;
}

void Game::whitePlayed(bool didThey) {
  this->lastPlayStore = didThey;
}

bool Game::doesKingMoved(int color) {
  return this->kingHasMoved[color];
}
void Game::kingMoved(int color) {
  this->kingHasMoved[color] = true;
}
bool Game::doesKingHasBeenInCheck(int color) {
  return this->kingHasBeenInCheck[color];
}
void Game::kingBeenInCheck(int color) {
  this->kingHasBeenInCheck[color] = true;
}
bool Game::doesRookMoved(int color, int side) {
  return this->rookHasMoved[color][side];
}
void Game::rookMoved(int color, int side) {
  this->rookHasMoved[color][side] = true;
}

bool Game::isCheckMate(spriteVector_t figures, Game &game, int color) {
  string coords;
  int i;
  char t_x, t_y;
  bool isCheckMate = true;
  piecePtrVector_t player_pieces;
  pieceFinder_t target_finder;
  vector<string> all_cases;
  if (color == WHITE) {
    player_pieces.assign(this->board.begin(), this->board.begin() + 16);
  } else {
    player_pieces.assign(this->board.begin() +16, this->board.end());
  }
  for(i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      coords = ""; coords+=VALID_X[i];coords+=VALID_Y[j];
      all_cases.push_back(coords);
    }
  }
  for(auto const& pc: player_pieces) {
    i = 0;
    while(i<64 && isCheckMate) {
      t_x = all_cases[i][0];
      t_y = all_cases[i][1];
      target_finder = findPiece(figures, str_to_xy(t_x, t_y));
      if(pc->isValidMove(figures, game, target_finder, t_x, t_y)) {
        isCheckMate = false;
      }
      i++;
    }
    if (!isCheckMate) { break; }
  }

  if(isCheckMate) {
    cout<< COLORS[color] << "s are CheckMate!";
  }

  return isCheckMate;
}
