// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <vector>
#include <map>
#include "boost/variant.hpp"

using namespace std;

const int SQUARE_SIZE = 112;

const int WHITE = 0x00;
const int BLACK = 0x01;

const vector<string> COLORS = {"White", "Black"};

const int LEFT  = 0x00;
const int RIGHT = 0x01;

const vector<string> SIDES = {"left", "right"};

const int PAWN    = 0X00;
const int KING    = 0X01;
const int QUEEN   = 0X02;
const int ROOK    = 0X03;
const int BISHOP  = 0X04;
const int KNIGHT  = 0X05;

const vector<string> PIECES = {"Pawn", "King", "Queen", "Rook", "Bishop", "Knight"};

const int LINEAR      = 0x00;
const int DIAGONALLY  = 0x01;
const int UNKNOWN     = 0x03;

const int SOUTH       = 0x00;
const int NORTH       = 0x01;
const int OUEST       = 0x02;
const int EAST        = 0x03;
const int SOUTH_OUEST = 0x04;
const int SOUTH_EAST  = 0x05;
const int NORTH_OUEST = 0x06;
const int NORTH_EAST  = 0x07;

const int WHITE_KING_INDEX = 4;
const int BLACK_KING_INDEX = 20;
const int L_W_ROOK_INDEX = 0;
const int R_W_ROOK_INDEX = 7;
const int L_B_ROOK_INDEX = 16;
const int R_B_ROOK_INDEX = 23;

const vector<vector<int>> ROOK_INDEXES = {{0,7}, {16, 23}};
const vector<string> CASTLING = {"d", "f"};

const string VALID_X = "abcdefgh";
const string VALID_Y = "12345678";

const vector<map<string, boost::variant<string, int>>> PIECES_DEF = {
  {{"color", WHITE}, {"type", ROOK},    {"coords", "a1"}, {"id", 0}},
  {{"color", WHITE}, {"type", KNIGHT},  {"coords", "b1"}, {"id", 1}},
  {{"color", WHITE}, {"type", BISHOP},  {"coords", "c1"}, {"id", 2}},
  {{"color", WHITE}, {"type", QUEEN},   {"coords", "d1"}, {"id", 3}},
  {{"color", WHITE}, {"type", KING},    {"coords", "e1"}, {"id", 4}},
  {{"color", WHITE}, {"type", BISHOP},  {"coords", "f1"}, {"id", 5}},
  {{"color", WHITE}, {"type", KNIGHT},  {"coords", "g1"}, {"id", 6}},
  {{"color", WHITE}, {"type", ROOK},    {"coords", "h1"}, {"id", 7}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "a2"}, {"id", 8}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "b2"}, {"id", 9}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "c2"}, {"id", 10}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "d2"}, {"id", 11}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "e2"}, {"id", 12}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "f2"}, {"id", 13}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "g2"}, {"id", 14}},
  {{"color", WHITE}, {"type", PAWN},    {"coords", "h2"}, {"id", 15}},
  {{"color", BLACK}, {"type", ROOK},    {"coords", "a8"}, {"id", 16}},
  {{"color", BLACK}, {"type", KNIGHT},  {"coords", "b8"}, {"id", 17}},
  {{"color", BLACK}, {"type", BISHOP},  {"coords", "c8"}, {"id", 18}},
  {{"color", BLACK}, {"type", QUEEN},   {"coords", "d8"}, {"id", 19}},
  {{"color", BLACK}, {"type", KING},    {"coords", "e8"}, {"id", 20}},
  {{"color", BLACK}, {"type", BISHOP},  {"coords", "f8"}, {"id", 21}},
  {{"color", BLACK}, {"type", KNIGHT},  {"coords", "g8"}, {"id", 22}},
  {{"color", BLACK}, {"type", ROOK},    {"coords", "h8"}, {"id", 23}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "a7"}, {"id", 24}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "b7"}, {"id", 25}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "c7"}, {"id", 26}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "d7"}, {"id", 27}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "e7"}, {"id", 28}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "f7"}, {"id", 29}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "g7"}, {"id", 30}},
  {{"color", BLACK}, {"type", PAWN},    {"coords", "h7"}, {"id", 31}},
};

#endif
