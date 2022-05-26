#ifndef _BOARD_H
#define _BOARD_H

class Figure;

#include "figure.h"

class Board
{
    public:
        Board();
	~Board();
        void PrintBoard() const;
		std::pair<bool, std::pair<unsigned int, unsigned int>> isChess(Figure::Color);
		bool isMate(unsigned int x1, unsigned int y1);
		bool isStalemate(Figure::Color);	
		bool shortCastle(Figure::Color);
		bool longCastle(Figure::Color);
		void changeFigure(unsigned int, unsigned int, Figure::Color);

	friend class Pawn;
	friend class Knight;
	friend class Gamer;
	friend class Rook;
	friend class Bishop;
	friend class Queen;
	friend class King;

    private:
        char symbols[8]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        int numbers[8] {8, 7, 6, 5, 4, 3, 2, 1};
        Figure* board[12][12];
	std::string figures[4]{"Knight", "Bishop", "Rook", "Queen"};
};
#endif // _BOARD_H
