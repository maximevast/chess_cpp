// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include "constants.h"

using namespace std;

class Piece;

typedef vector<sf::Sprite> spriteVector_t;
typedef vector<Piece*> piecePtrVector_t;
typedef vector<sf::Vector2f> vector2FVector_t;

typedef tuple<bool, int> pieceFinder_t;
typedef tuple<int, vector2FVector_t> pathFinder_t;

sf::Vector2f str_to_xy(char x, char y);
string xy_to_str(sf::Vector2f xy_pos);
pathFinder_t getPath(int old_x, int old_y, int new_x, int new_y);
pieceFinder_t findPiece(spriteVector_t figures, sf::Vector2f pos);
int getDistance(int old_x, int old_y, int new_x, int new_y);
int getDirection(int old_x, int old_y, int new_x, int new_y);

#endif
