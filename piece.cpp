// piece.cpp
#include "headers/piece.h"

Piece::Piece() {}
Piece::~Piece() {}
Piece::Piece(int color, int type, int id, string coords) {
  this->color = color;
  this->type = type;
  this->id = id;
  this->coords = coords;
}
bool Piece::isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y) {
  bool isValid = false;
  bool target_is_occupied = get<bool>(target);
  if (VALID_X.find(x) != string::npos && VALID_Y.find(y) != string::npos) {
    if (!target_is_occupied) {
      isValid = true;
    } else {
      int ti = get<int>(target);
      if ((this->color ^ game.get_board()[ti]->get_color())) { isValid = true; }
    }
  }
  string currentStrPos = this->coords;
  string wantedStrPos = "";wantedStrPos += x;wantedStrPos += y;
  // temporarily set new coords to verify check state
  this->coords = wantedStrPos;
  // Players can't leave their king in chess
  int kingIndex = ((this->color==WHITE)? WHITE_KING_INDEX : BLACK_KING_INDEX);
  King * king = dynamic_cast<King*>(game.get_board()[kingIndex]);
  if (king->isInCheck(game, king->getCoords()[0], king->getCoords()[1])) {
    isValid = false;
  }
  // reset coords
  this->coords = currentStrPos;
  return isValid;
}
int Piece::get_color() { return this->color; }
int Piece::getId() { return this->id; }
int Piece::getType() { return this->type; }
string Piece::getCoords() { return this->coords; }
void Piece::setCoords(string crds) { this->coords = crds;}

Pawn::Pawn(int color, string coords, int id) : Piece(color, PAWN, id, coords) {}
Pawn::~Pawn() {}
bool Pawn::isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y) {
  bool isValid = false;
  bool isValidGeneric = Piece::isValidMove(figures, game, target, x, y);
  char cx = this->coords[0];
  char cy = this->coords[1];
  int max_distance, mov_dir, eat_dir1, eat_dir2;

  if (this->color == WHITE) {
    (cy=='2') ? max_distance = 2 : max_distance = 1;
    mov_dir = NORTH;
    eat_dir1 = NORTH_OUEST;
    eat_dir2 = NORTH_EAST;
  } else {
    (cy=='7') ? max_distance = 2 : max_distance = 1;
    mov_dir = SOUTH;
    eat_dir1 = SOUTH_OUEST;
    eat_dir2 = SOUTH_EAST;
  }

  bool target_is_occupied = get<bool>(target);
  int direction = getDirection(cx, cy, x, y);
  int distance = getDistance(cx, cy, x, y);
  if (!target_is_occupied) {
    if (direction == mov_dir && distance > 0 && distance <= max_distance) {
      isValid = true;
    }
  } else {
    // eating ?
    if ((direction == eat_dir1 || direction == eat_dir2) && distance == 1) {
      isValid = true;
    }
  }
  // todo "en passant"
  // todo "promotion"
  return isValid && isValidGeneric;
}

Knight::Knight(int color, string coords, int id) : Piece(color, KNIGHT, id, coords) {}
Knight::~Knight() {}
bool Knight::isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y) {
  bool isValid = false;
  bool isValidGeneric = Piece::isValidMove(figures, game, target, x, y);
  char cx = this->coords[0];
  char cy = this->coords[1];
  if( (x == cx+1 && (y == cy+2 || y == cy-2)) ||
      (x == cx-1 && (y == cy+2 || y == cy-2)) ||
      (x == cx+2 && (y == cy+1 || y == cy-1)) ||
      (x == cx-2 && (y == cy+1 || y == cy-1)) ) { isValid = true; }

  return isValid && isValidGeneric;
}

Bishop::Bishop(int color, string coords, int id) : Piece(color, BISHOP, id, coords) {}
Bishop::~Bishop() {}
bool Bishop::isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y) {
  bool isValid = false;
  bool isValidGeneric = Piece::isValidMove(figures, game, target, x, y);
  char cx = this->coords[0];
  char cy = this->coords[1];
  pathFinder_t path = getPath(cx, cy, x, y);
  int direction = get<int>(path);
  vector2FVector_t casesOnPath = get<1>(path);
  if( direction == DIAGONALLY ) {
    bool temporaryTrue = true;
    for(auto const& cop: casesOnPath) {
      pieceFinder_t onPath = findPiece(figures, cop);
      temporaryTrue = temporaryTrue && !(get<bool>(onPath));
    }
    isValid = temporaryTrue;
  }
  return isValid && isValidGeneric;
}

Rook::Rook(int color, string coords, int id) : Piece(color, ROOK, id, coords) {}
Rook::~Rook() {}
bool Rook::isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y) {
  bool isValid = false;
  bool isValidGeneric = Piece::isValidMove(figures, game, target, x, y);
  char cx = this->coords[0];
  char cy = this->coords[1];
  pathFinder_t path = getPath(cx, cy, x, y);
  int direction = get<int>(path);
  vector2FVector_t casesOnPath = get<1>(path);
  if(direction == LINEAR) {
    bool temporaryTrue = true;
    for(auto const& cop: casesOnPath) {
      pieceFinder_t onPath = findPiece(figures, cop);
      temporaryTrue = temporaryTrue && !(get<bool>(onPath));
    }
    isValid = temporaryTrue;
  }

  return isValid && isValidGeneric;
}

Queen::Queen(int color, string coords, int id) : Piece(color, QUEEN, id, coords) {}
Queen::~Queen() {}
bool Queen::isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y) {
  bool isValid = false;
  bool isValidGeneric = Piece::isValidMove(figures, game, target, x, y);
  char cx = this->coords[0];
  char cy = this->coords[1];
  pathFinder_t path = getPath(cx, cy, x, y);
  int direction = get<int>(path);
  vector2FVector_t casesOnPath = get<1>(path);
  if( direction == DIAGONALLY || direction == LINEAR) {
    bool temporaryTrue = true;
    for(auto const& cop: casesOnPath) {
      pieceFinder_t onPath = findPiece(figures, cop);
      temporaryTrue = temporaryTrue && !(get<bool>(onPath));
    }
    isValid = temporaryTrue;
  }

  return isValid && isValidGeneric;
}

King::King(int color, string coords, int id) : Piece(color, KING, id, coords) {}
King::~King() {}
bool King::isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y) {
  bool isValid = false;
  bool isValidGeneric = Piece::isValidMove(figures, game, target, x, y);
  char cx = this->coords[0];
  char cy = this->coords[1];
  pathFinder_t path = getPath(cx, cy, x, y);
  int direction = get<int>(path);
  if( (direction == DIAGONALLY || direction == LINEAR) && getDistance(cx, cy, x, y)==1 ) {
    isValid = true;
  }
  // casteling
  if (cx == 'e' && (cy == '1' || cy == '8') && (y == cy && (x == 'g'|| x== 'c'))) {
    vector<string> myp;
    vector2FVector_t casesOnPath;
    pieceFinder_t onPath;
    int side;
    string myc = "";
    if (x == 'g') {
      side = RIGHT;
      myc+='f';myc+=y;myp.push_back(myc);myc="";myc+='g';myc+=y;myp.push_back(myc);
    } else {
      side = LEFT;
      myc+='b';myc+=y;myp.push_back(myc);myc="";myc+='c';myc+=y;myp.push_back(myc);myc="";myc+='d';myc+=y;myp.push_back(myc);
    }
    for(auto c : myp) {
      casesOnPath.push_back(str_to_xy(c[0], c[1]));
    }
    // the king and the rook mustn't have previously moved during the game nor the king have been in check.
    if (!game.doesKingMoved(this->color) && !game.doesRookMoved(this->color, side) && !game.doesKingHasBeenInCheck(this->color)) {
      // the path must be free
      bool temporaryTrue = true;
      for(auto cop: casesOnPath) {
        // There cannot be any pieces between the king and the rook.
        onPath = findPiece(figures, cop);
        temporaryTrue = temporaryTrue && !(get<bool>(onPath));
      }
      // the king cannot be in check,
      temporaryTrue = temporaryTrue && !isInCheck(game, cx, cy);
      // nor can the king pass through squares that are under attack by enemy pieces,
      for(auto const& c : myp) {
        temporaryTrue = temporaryTrue && !isInCheck(game, c[0], c[1]);
      }
      isValid = temporaryTrue;
    }
  }

  // the king cannot move to a square where it would result in a check.
  // TODO: Normaly, this isInCheck is already verified by is valid generic beeing called for the king
  return isValid && isValidGeneric && !isInCheck(game, x, y);
}
// We pass x and y as parameters because we can either call this function for :
// the actual king position (does moving this piece leaves the king in check?)
// or the king's target position (does moving the king here puts him in check?)
bool King::isInCheck(Game &game, char x, char y) {
  bool foundPiece = false;
  piecePtrVector_t all_pieces = game.get_board();
  vector<vector<string>> linear_reachable(4);
  vector<vector<string>> diagonal_reachable(4);
  vector<string> knight_reachable;

  char pos_x, pos_y;
  string coords;
  // linear_reachable
  pos_x = x+1;
  while(pos_x <='h') {
    coords = ""; coords+=pos_x++;coords+=y;
    linear_reachable[0].push_back(coords);
  }
  pos_x = x-1;
  while(pos_x >='a') {
    coords = ""; coords+=pos_x--;coords+=y;
    linear_reachable[1].push_back(coords);
  }
  pos_y = y+1;
  while(pos_y<='8') {
    coords = ""; coords+=x;coords+=pos_y++;
    linear_reachable[2].push_back(coords);
  }
  pos_y = y-1;
  while(pos_y>='1') {
    coords = ""; coords+=x;coords+=pos_y--;
    linear_reachable[3].push_back(coords);
  }
  // diagonal_reachable
  pos_x = x+1; pos_y = y+1;
  while(pos_x <='h' && pos_y<='8') {
    coords = ""; coords+=pos_x++;coords+=pos_y++;
    diagonal_reachable[0].push_back(coords);
  }
  pos_x = x-1; pos_y = y-1;
  while(pos_x >='a' && pos_y>='1') {
    coords = ""; coords+=pos_x--;coords+=pos_y--;
    diagonal_reachable[1].push_back(coords);
  }
  pos_x = x+1; pos_y = y-1;
  while(pos_x <='h' && pos_y>='1') {
    coords = ""; coords+=pos_x++;coords+=pos_y--;
    diagonal_reachable[2].push_back(coords);
  }
  pos_x = x-1; pos_y = y+1;
  while(pos_x >='a' && pos_y<='8') {
    coords = ""; coords+=pos_x--;coords+=pos_y++;
    diagonal_reachable[3].push_back(coords);
  }
  // knight_reachable
  pos_x = x+1; pos_y = y+2;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }
  pos_x = x+1; pos_y = y-2;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }
  pos_x = x-1; pos_y = y+2;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }
  pos_x = x-1; pos_y = y-2;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }
  pos_x = x+2; pos_y = y+1;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }
  pos_x = x+2; pos_y = y-1;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }
  pos_x = x-2; pos_y = y+1;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }
  pos_x = x-2; pos_y = y-1;
  if (VALID_X.find(pos_x) != string::npos && VALID_Y.find(pos_y) != string::npos) {
    coords = ""; coords+=pos_x;coords+=pos_y;
    knight_reachable.push_back(coords);
  }

  // Check lookup
  int i, t_direction, t_distance, t_type, t_color;
  char t_x, t_y;

  for(auto const& reachableDir: diagonal_reachable) {
    for(auto const& reachableCoords: reachableDir) {
      i = 0;
      while (i<32 && !foundPiece) {
        coords = all_pieces[i]->getCoords();
        if(coords == reachableCoords) {
          foundPiece = true;
          t_x = coords[0];
          t_y = coords[1];
          t_direction = getDirection(x, y, t_x, t_y);
          t_distance = getDistance(x, y, t_x, t_y);
          t_type = all_pieces[i]->getType();
          t_color = all_pieces[i]->get_color();
          if((t_color ^ this->color) && (
              (t_type == BISHOP) ||
              (t_type == QUEEN) ||
              (t_type == KING && t_distance == 1) ||
              ((t_type == PAWN && t_distance == 1) && (
              (this->color == BLACK && (t_direction == SOUTH_EAST or t_direction == SOUTH_OUEST)) ||
              (this->color == WHITE && (t_direction == NORTH_EAST or t_direction == NORTH_OUEST)))))
            ) {return true;}
        }
        i++;
      }
      if(foundPiece) { foundPiece=false;break; }
    }
  }
  for(auto const& reachableDir: linear_reachable) {
    for(auto const& reachableCoords: reachableDir) {
      i = 0;
      while (i<32 && !foundPiece) {
        coords = all_pieces[i]->getCoords();
        if(coords == reachableCoords) {
          foundPiece = true;
          t_x = coords[0];
          t_y = coords[1];
          t_direction = getDirection(x, y, t_x, t_y);
          t_distance = getDistance(x, y, t_x, t_y);
          t_type = all_pieces[i]->getType();
          t_color = all_pieces[i]->get_color();
          if((t_color ^ this->color) && (
              (t_type == ROOK) ||
              (t_type == QUEEN) ||
              (t_type == KING && t_distance == 1))
            ) {return true;}
        }
        i++;
      }
      if(foundPiece) { foundPiece=false;break; }
    }
  }
  for(auto const& reachableCoords: knight_reachable) {
    i = 0;
    while (i<32 && !foundPiece) {
      coords = all_pieces[i]->getCoords();
      if(coords == reachableCoords) {
        foundPiece = true;
        t_type = all_pieces[i]->getType();
        t_color = all_pieces[i]->get_color();
        if((t_color ^ this->color) && (t_type == KNIGHT)) {
          return true;
        }
      }
      i++;
    }
    if(foundPiece) { foundPiece=false; }
  }
  // If we reach this statement, we are not in check.
  return false;
}
