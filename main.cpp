// main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>

#include "headers/piece.h"
#include "headers/game.h"
#include "headers/utils.h"
#include "headers/textures.h"
#include <fstream>
#include <string>

using namespace std;

Game g =  Game();
spriteVector_t figures(32);
sf::Texture board_texture;

void updateBoard() {
  piecePtrVector_t board = g.get_board();
  for(auto const& piece : board) {
      figures[piece->getId()].setPosition(str_to_xy(piece->getCoords()[0], piece->getCoords()[1]));
  }
}

void tryToMove(string coord) {
  char cx, cy, tx, ty;
  cx = coord[0];
  cy = coord[1];
  tx = coord[2];
  ty = coord[3];
  pieceFinder_t current_finder = findPiece(figures, str_to_xy(cx,cy));
  pieceFinder_t target_finder = findPiece(figures, str_to_xy(tx,ty));

  bool pieceExist = get<bool>(current_finder);
  if (pieceExist) {
    int ci = get<int>(current_finder);
    int color = g.get_board()[ci]->get_color();
    bool wp = g.didWhitePlayed();
    bool moveIsValid = g.get_board()[ci]->isValidMove(figures, g, target_finder, tx, ty);
    bool twiceInARow = (((color==BLACK && !wp) || (color==WHITE && wp))? true : false );

    if (moveIsValid && !twiceInARow) {
      string t_pos = "";t_pos += tx;t_pos += ty;
      g.get_board()[ci]->setCoords(t_pos);

      cout << "Moving " << COLORS[color] << " " << PIECES[g.get_board()[ci]->getType()] << " from " << cx << ":" << cy << " to "  << tx << ":" << ty << " ..." << endl;

      // casteling
      if (cx == 'e' && (cy == '1' || cy == '8') && (ty == cy && (tx == 'g'|| tx== 'c'))) {
        int side = ((tx == 'g') ? RIGHT : LEFT);
        g.get_board()[ROOK_INDEXES[color][side]]->setCoords(CASTLING[side] + cy);
        cout << "Castling to the  " << SIDES[side]  << "." << endl;
      }

      // eating
      if(get<bool>(target_finder)) {
        // move eaten piece out of the board
        int t_index = get<int>(target_finder);
        g.get_board()[t_index]->setCoords("i9");
        cout << "Capturing opponent " << PIECES[g.get_board()[t_index]->getType()]  << " !" << endl;
      }

      // avoids unauthorized castling
      int opponentKingIndex = ((color==WHITE)? BLACK_KING_INDEX : WHITE_KING_INDEX);
      // isInCheck is only a member of child class King, we need to cast the Piece ptr to a King ptr
      King * oppKing = dynamic_cast<King*>(g.get_board()[opponentKingIndex]);
      string oppKCoords = oppKing->getCoords();
      int oppKColor = oppKing->get_color();
      if (oppKing->isInCheck(g, oppKCoords[0], oppKCoords[1])) {
        cout << COLORS[oppKColor] << " king is in Check!"<<endl;
        g.kingBeenInCheck(oppKColor);
      }
      if(ci == WHITE_KING_INDEX) {g.kingMoved(WHITE);}
      else if(ci == BLACK_KING_INDEX) {g.kingMoved(BLACK);}
      else if(ci == L_W_ROOK_INDEX) {g.rookMoved(WHITE, LEFT);}
      else if(ci == R_W_ROOK_INDEX) {g.rookMoved(WHITE, RIGHT);}
      else if(ci == L_B_ROOK_INDEX) {g.rookMoved(BLACK, LEFT);}
      else if(ci == R_B_ROOK_INDEX) {g.rookMoved(BLACK, RIGHT);}

      updateBoard();
      g.whitePlayed((color == WHITE));
      cout << endl;
    } else {
      cout << "Invalid mov :(";
      if (twiceInARow) {
        cout << " You can't play twice in a row!";
      }
    }
  }
}

int main(int argc, char *argv[]) {
  g.draw();
  sf::RenderWindow window(sf::VideoMode(900, 900), "P00400 : Chess in c++");
  board_texture.loadFromFile("images/board.png");
  sf::Sprite board_sprite(board_texture);
  setTextures(figures);

  piecePtrVector_t board = g.get_board();
  for (int i =0; i<32; i++) {
    figures[i].setPosition(str_to_xy(board[i]->getCoords()[0], board[i]->getCoords()[1]));
  }

  if(argc == 2) {
    ifstream file(argv[1]);
    string str;
    window.draw(board_sprite);
    window.display();
    while (getline(file, str)) {
      tryToMove(str);
      g.isCheckMate(figures, g, BLACK);
      g.isCheckMate(figures, g, WHITE);
      window.clear();
      window.draw(board_sprite);
      for(auto const& piece_sprite: figures) {
        window.draw(piece_sprite);
      }
     	window.display();
      sf::sleep(sf::milliseconds(500));
    }
    getchar();
  } else {
    string pos = "";
    while (window.isOpen()) {
      sf::Event e;
      while (window.pollEvent(e)) {

        if (e.type == sf::Event::Closed) {
          window.close();
        }
        if (e.type == sf::Event::TextEntered) {
          if (e.text.unicode < 128) {
            if( e.text.unicode == 13 ) {
              tryToMove(pos);
              g.isCheckMate(figures, g, BLACK);
              g.isCheckMate(figures, g, WHITE);
              pos = "";
            } else if( e.text.unicode == 8 ) {
              if( pos.size() > 0 ) pos.resize( pos.size() - 1 );
            } else {
              pos+=static_cast<char>(e.text.unicode);
            }
            cout << pos << endl;
          }
        }
      }

    window.clear();
    window.draw(board_sprite);
    for(auto const& piece_sprite: figures)
      window.draw(piece_sprite);
   	window.display();
    }
  }
  return 0;
}
