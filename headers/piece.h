// piece.h
#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "utils.h"
#include "game.h"
#include <iostream>
#include <array>

using namespace std;

class Game;

class Piece {
  protected:
    int color, type, id;
    string coords;

  public:
    Piece();
    Piece(int color, int type, int id, string coords);
    virtual ~Piece();

    virtual bool isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y);
    string getCoords();
    void setCoords(string coords);
    int get_color();
    int getId();
    int getType();
};

class Pawn: public Piece {
  public:
    Pawn(int color, string coords, int id);
    ~Pawn();
    bool isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y);
};
class Knight: public Piece {
  public:
    Knight(int color, string coords, int id);
    ~Knight();
    bool isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y);
};
class Bishop: public Piece {
  public:
    Bishop(int color, string coords, int id);
    ~Bishop();
    bool isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y);
};
class Rook: public Piece {
  public:
    Rook(int color, string coords, int id);
    ~Rook();
    bool isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y);
};
class Queen: public Piece {
  public:
    Queen(int color, string coords, int id);
    ~Queen();
    bool isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y);
};
class King: public Piece {
  public:
    King(int color, string coords, int id);
    ~King();
    bool isValidMove(spriteVector_t figures, Game &game, pieceFinder_t target, char x, char y);
    bool isInCheck(Game &game, char x, char y);
};
#endif
