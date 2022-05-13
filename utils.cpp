// utils.cpp
#include "headers/utils.h"
#include <iostream>

sf::Vector2f str_to_xy(char x, char y) {
   return sf::Vector2f((int(x)-97)*SQUARE_SIZE,(56-int(y))*SQUARE_SIZE);
}

string xy_to_str(sf::Vector2f xy_pos) {
  string str = "";
  str += char(xy_pos.x/SQUARE_SIZE+97);
  str += char(7-xy_pos.y/SQUARE_SIZE+49);
  return str;
}

pieceFinder_t findPiece(spriteVector_t figures, sf::Vector2f pos) {
  int i = 0;
  bool found = false;
  while(i<32 && !found ) {
    if (figures[i].getPosition()==pos)
      found = true;
    else
      i++;
  }
  return { found, i };
}

pathFinder_t getPath(int old_x, int old_y, int new_x, int new_y) {
  int pathDirection = UNKNOWN;
  vector2FVector_t piecesOnPath;

  int x_min = min(old_x, new_x);
  int x_max = max(old_x, new_x);
  int y_min = min(old_y, new_y);
  int y_max = max(old_y, new_y);
  switch (getDirection(old_x, old_y, new_x, new_y)) {
    case NORTH :
    case SOUTH :
      pathDirection = LINEAR;
      for (int i=y_min+1; i<y_max; i++)
        piecesOnPath.push_back(str_to_xy(old_x, i));
    break;
    case EAST  :
    case OUEST :
      pathDirection = LINEAR;
      for (int i=x_min+1; i<x_max; i++)
        piecesOnPath.push_back(str_to_xy(i, old_y));
    break;
    case SOUTH_OUEST :
    case NORTH_EAST  :
      pathDirection = DIAGONALLY;
      for (int i=y_min+1, j=x_min+1; i<y_max; i++,j++)
        piecesOnPath.push_back(str_to_xy(j, i));
    break;
    case NORTH_OUEST :
    case SOUTH_EAST  :
      pathDirection = DIAGONALLY;
      for (int i=y_max-1, j=x_min+1; i>y_min; i--, j++)
        piecesOnPath.push_back(str_to_xy(j, i));
    break;
  }

  return { pathDirection, piecesOnPath };
}

int getDistance(int old_x, int old_y, int new_x, int new_y) {
  int distance = 0;
  (new_x == old_x) ? distance = abs(new_y - old_y) : distance = abs(new_x - old_x);
  return distance;
}

int getDirection(int old_x, int old_y, int new_x, int new_y) {
  int direction;
  if(old_x == new_x) {
    if (old_y > new_y) {
      direction = SOUTH;
    } else if (old_y < new_y){
      direction = NORTH;
    } else {
      direction = -1;
    }
  } else if (old_x > new_x) {
    if (old_y == new_y) {
      direction = OUEST;
    } else if (old_y > new_y && (old_x-new_x == old_y-new_y)) {
      direction = SOUTH_OUEST;
    } else if (old_y < new_y && (old_x-new_x == new_y-old_y)) {
      direction = NORTH_OUEST;
    } else {
      direction = -1;
    }
  } else {
    if (old_y == new_y) {
      direction = EAST;
    } else if (old_y > new_y && (new_x-old_x == old_y-new_y)) {
      direction = SOUTH_EAST;
    } else if (old_y < new_y && (new_x-old_x == new_y-old_y)) {
      direction = NORTH_EAST;
    } else {
      direction = -1;
    }
  }
  return direction;
}
