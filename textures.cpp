// textures.cpp

#include "headers/textures.h"

sf::Texture black_king_texture,black_queen_texture,
black_rook_texture,black_bishop_texture,black_knight_texture,
black_pawn_texture,white_king_texture,white_queen_texture,white_rook_texture,
white_bishop_texture,white_knight_texture,white_pawn_texture;

void setTextures(spriteVector_t &figures) {
  white_pawn_texture.loadFromFile("images/pawn_white.png");
  black_pawn_texture.loadFromFile("images/pawn_black.png");
  white_knight_texture.loadFromFile("images/knight_white.png");
  black_knight_texture.loadFromFile("images/knight_black.png");
  white_bishop_texture.loadFromFile("images/bishop_white.png");
  black_bishop_texture.loadFromFile("images/bishop_black.png");
  white_rook_texture.loadFromFile("images/rook_white.png");
  black_rook_texture.loadFromFile("images/rook_black.png");
  white_queen_texture.loadFromFile("images/queen_white.png");
  black_queen_texture.loadFromFile("images/queen_black.png");
  white_king_texture.loadFromFile("images/king_white.png");
  black_king_texture.loadFromFile("images/king_black.png");
  figures[0].setTexture(white_rook_texture);
  figures[1].setTexture(white_knight_texture);
  figures[2].setTexture(white_bishop_texture);
  figures[3].setTexture(white_queen_texture);
  figures[4].setTexture(white_king_texture);
  figures[5].setTexture(white_bishop_texture);
  figures[6].setTexture(white_knight_texture);
  figures[7].setTexture(white_rook_texture);
  figures[8].setTexture(white_pawn_texture);
  figures[9].setTexture(white_pawn_texture);
  figures[10].setTexture(white_pawn_texture);
  figures[11].setTexture(white_pawn_texture);
  figures[12].setTexture(white_pawn_texture);
  figures[13].setTexture(white_pawn_texture);
  figures[14].setTexture(white_pawn_texture);
  figures[15].setTexture(white_pawn_texture);
  figures[16].setTexture(black_rook_texture);
  figures[17].setTexture(black_knight_texture);
  figures[18].setTexture(black_bishop_texture);
  figures[19].setTexture(black_queen_texture);
  figures[20].setTexture(black_king_texture);
  figures[21].setTexture(black_bishop_texture);
  figures[22].setTexture(black_knight_texture);
  figures[23].setTexture(black_rook_texture);
  figures[24].setTexture(black_pawn_texture);
  figures[25].setTexture(black_pawn_texture);
  figures[26].setTexture(black_pawn_texture);
  figures[27].setTexture(black_pawn_texture);
  figures[28].setTexture(black_pawn_texture);
  figures[29].setTexture(black_pawn_texture);
  figures[30].setTexture(black_pawn_texture);
  figures[31].setTexture(black_pawn_texture);
}
