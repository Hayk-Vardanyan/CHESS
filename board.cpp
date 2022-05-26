#include "board.h"

Board::Board()
{
	for(int j = 0; j < 8; ++j) {
        board[1][j] = new Pawn(Figure::Color::Black);
        board[6][j] = new Pawn(Figure::Color::White);
    }
    board[0][0] = new Rook(Figure::Color::Black);
    board[0][1] = new Knight(Figure::Color::Black);
    board[0][2] = new Bishop(Figure::Color::Black);
    board[0][3] = new Queen(Figure::Color::Black);
    board[0][4] = new King(Figure::Color::Black);
    board[0][5] = new Bishop(Figure::Color::Black);
    board[0][6] = new Knight(Figure::Color::Black);
    board[0][7] = new Rook(Figure::Color::Black);

    for(int i = 2; i < 6; ++i) {
        for(int j = 0; j < 8; ++j) {
            board[i][j] = new None(Figure::Color::None);
        }
    }
    
    board[7][0] = new Rook(Figure::Color::White);
    board[7][1] = new Knight(Figure::Color::White);
    board[7][2] = new Bishop(Figure::Color::White);
    board[7][3] = new Queen(Figure::Color::White);
    board[7][4] = new King(Figure::Color::White);
    board[7][5] = new Bishop(Figure::Color::White);
    board[7][6] = new Knight(Figure::Color::White);
    board[7][7] = new Rook(Figure::Color::White);

  }

Board::~Board()
{
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			delete board[i][j];
		}
	}
}

std::pair<bool, std::pair<unsigned int, unsigned int> >Board::isChess(Figure::Color currentColor)
{
	const std::string kingName = "4King";
	unsigned int kingPosx1{};
	unsigned int kingPosy1{};
	std::pair<bool, std::pair<unsigned int, unsigned int>> p;

	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {

			if(typeid(*board[i][j]).name() == kingName && board[i][j]->GetColor() != currentColor) {
				kingPosx1 = i;
				kingPosy1 = j;
				break;
			}
		}
	}
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {

			if(typeid(*board[i][j]).name() != kingName && board[i][j]->GetColor() == currentColor) {
				if(this->board[i][j]->LegalMove(i, j, kingPosx1, kingPosy1, *this)) {
					p.first = true;
					p.second.first = i;
					p.second.second = j;
					return p;
				}
			}
		}
	}
	p.first = false;
	p.second.first = -1;
	p.second.second = -1;
	return p;
}




void Board::PrintBoard() const
{
    std::cout << "    ";
    for(int i = 0; i < 8; ++i) {
        std::cout << symbols[i];
        std::cout << "  ";
    }
    std::cout << "\n";
    
    for(int i = 0; i < 8; ++i) {
        std::cout << "____________________________";
        std::cout << '\n';
        std::cout << numbers[i];
        std::cout << "  ";
        
        for(int j = 0; j < 8; ++j) { 
             std::cout << "|";
            board[i][j]->PrintFigure();
        }
        std::cout << "\n";
    }

}

bool Board::isMate(unsigned int x1, unsigned int y1) 
{

	bool eatChessFigure = false;

	const std::string queenName = "5Queen";
	const std::string bishopName = "6Bishop";
	const std::string rookName = "4Rook";
	const std::string pawnName = "4Pawn";
	const std::string kingName = "4King";

	bool aroundKing = false;


	auto opponentColor = (board[x1][y1]->GetColor() == Figure::Color::White ? Figure::Color::Black : Figure::Color::White);

	unsigned int x2, y2{};

	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			if(board[i][j]->GetColor() == opponentColor && (i != x1 && j != y1)) {
				if(board[i][j]->LegalMove(i, j, x1, y1, *this)) {
					eatChessFigure = true;
				}
			}
		}
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (typeid(*board[i][j]).name() == kingName && board[i][j]->GetColor() == opponentColor) {
				x2 = i;
				y2 = j;
				break;	
			}
		}		
	}

	if(x2 - 1 >= 0) {
		if(x1 == x2 - 1 && y1 == y2) aroundKing = true;
	}
	if(x2 - 1 >= 0 && y2 + 1 <= 7) {
		if(x1 == x2 - 1 && y1 == y2 + 1) aroundKing = true;

	} if(y2 + 1 <= 7) {
		if(x2 == x1 && y1 == y2 + 1) aroundKing = true;

	} if(x2 + 1 <= 7 && y2 + 1 <= 7) {
		if(x1 == x2 + 1 && y1 == y2 + 1) { aroundKing = true;}
	}
	if(x2 + 1 <= 7) {
		if(y1 == y2 && x1 == x2 + 1) aroundKing = true;
	}
	if(x2 + 1 <= 7 && y2 - 1 >= 0) {
		if(x1 == x2 + 1 && y1 == y2 - 1) aroundKing = true;
	}
	if(y2 - 1 >= 0) {
		if(x2 == x1 && y1 == y2 - 1) aroundKing = true;
	} 
	if(x2 - 1 >= 0 && y2 - 1 >= 0) {
		if(x1 == x2 - 1 && y1 == y2 - 1) aroundKing = true;
	}

if(!aroundKing) {
	if(typeid(*board[x1][y1]).name() == queenName || typeid(*board[x1][y1]).name() == bishopName || typeid(*board[x1][y1]).name() == rookName) {
		if(x1 == x2) {
			int tmp_max = std::max(y1, y2);
			int tmp_min = std::min(y1, y2);

				for(int i2 = 0; i2 < 8; ++i2) {
					for(int j2 = 0; j2 < 8; ++j2) {
						if(board[i2][j2]->GetColor() == opponentColor) {
							for(int i = tmp_min + 1; i < tmp_max; ++i) {
								if(board[i2][j2]->LegalMove(i2, j2, x1, i, *this))  { return false; }
						}
					}
				}
		}

		} else if(y1 == y2) {
			
			int tmp_max = std::max(x1, x2);
			int tmp_min = std::min(x1, x2);

			for(int i2 = 0; i2 < 8; ++i2) {
				for(int j2 = 0; j2 < 8; ++j2) {
				
					if(board[i2][j2]->GetColor() == opponentColor) {
					
						for(int i = tmp_min + 1; i < tmp_max; ++i) {
							if(board[i2][j2]->LegalMove(i2, j2, i, y1, *this)) { return false; }

						}
					}
				}
			}

		} else {
		bool top_left = (x1 > x2 && y1 > y2);
		bool low_right = (x1 < x2 && y1 < y2);
		bool top_right = (x1 > x2 && y1 < y2);
		bool low_left = (x1 < x2 && y1 > y2);
		int tmp_x1 = x1;
		int tmp_y1 = y1;	
			

		while (true) {
			if(top_left) {
				--tmp_x1;
				--tmp_y1;

			} else if(low_right) {
				++tmp_x1;
				++tmp_y1;

			} else if(top_right) {
				--tmp_x1;
				++tmp_y1;

			} else if(low_left) {
				++tmp_x1;
				--tmp_y1;
		}

			if(tmp_x1 == x2 && tmp_y1 == y2) {
				break;

			} 
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
		
			if (board[i][j]->GetColor() == opponentColor) {
			if(board[i][j]->LegalMove(i, j, tmp_x1, tmp_y1, *this)){ return false; }
			}
				}
			}
			}
		}
	}
		
}
 
	if(eatChessFigure) return false;
	if(x2 != 0) {
		if(board[x2][y2]->LegalMove(x2, y2, x2 - 1, y2, *this)) return false;
	}	
	if(x2 != 0 && y2 + 1 <= 7) {
			if(board[x2][y2]->LegalMove(x2, y2, x2 - 1, y2 + 1, *this)) return false;
		}	if(y2 + 1 <= 7)	{
			if(board[x2][y2]->LegalMove(x2, y2, x2, y2 + 1, *this)) return false;
		}
	if(x2 + 1 <= 7 && y2 + 1 <= 7) {
			if(board[x2][y2]->LegalMove(x2, y2, x2 + 1, y2 + 1, *this)) return false;
	}
	if(x2 + 1 <= 7) {
			if(board[x2][y2]->LegalMove(x2, y2, x2 + 1, y2, *this)) return false;
	}	
	if(x2 + 1 <= 7 && y2 != 0) {
			if(board[x2][y2]->LegalMove(x2, y2, x2 + 1, y2 - 1, *this)) return false;
	}
	if(y2 != 0) {
			if(board[x2][y2]->LegalMove(x2, y2, x2, y2 - 1, *this)) return false;
	}
	if(x2 != 0 && y2 != 0) {
		if(board[x2][y2]->LegalMove(x2, y2, x2 - 1, y2 - 1, *this)) return false;
	}

	return true;
}

bool Board::isStalemate(Figure::Color currentColor)  
{
	unsigned int x2;
	unsigned int y2;
	auto opponentColor = (currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White);
	std::string kingName = "4King";
	std::string pawnName = "4Pawn";
	std::string noneName = "4None";
	std::string rookName = "4Rook";
	std::string queenName = "5Queen";
	std::string knightName = "6Knight";
	std::string bishopName = "6Bishop";

	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			if(board[i][j]->GetColor() == currentColor) {
				for(int i2 = 0; i2 < 8; ++i2) {
					for(int j2 = 0; j2 < 8; ++j2) {
						if(board[i2][j2]->GetColor() != currentColor) {
						if(board[i][j]->LegalMove(i,j, i2, j2, *this)) 
						{
							std::string rememberFigure = typeid(*(board[i2][j2])).name();
							board[i][j]->moveFigure(i, j, i2, j2, *this, currentColor);
							if(!isChess(currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White).first) {
							board[i2][j2]->moveFigure(i2, j2, i, j, *this, currentColor);
									
			if(rememberFigure == pawnName) board[i2][j2] = new Pawn(opponentColor);	
			else if(rememberFigure == knightName) board[i2][j2] = new Knight(opponentColor);	
			if(rememberFigure == bishopName) board[i2][j2] = new Bishop(opponentColor);	
			if(rememberFigure == queenName) board[i2][j2] = new Queen(opponentColor);	
			if(rememberFigure == rookName) board[i2][j2] = new Rook(opponentColor);	
							return false;
							}
			
			if(rememberFigure == pawnName) board[i2][j2] = new Pawn(opponentColor);	
			else if(rememberFigure == knightName) board[i2][j2] = new Knight(opponentColor);	
			if(rememberFigure == bishopName) board[i2][j2] = new Bishop(opponentColor);	
			if(rememberFigure == queenName) board[i2][j2] = new Queen(opponentColor);	
			if(rememberFigure == rookName) board[i2][j2] = new Rook(opponentColor);
							board[i2][j2]->moveFigure(i2, j2, i, j, *this, currentColor);
							
						}
						}
					}
				}
			}
		}
	}
	return true;
}

bool Board::longCastle(Figure::Color currentColor)
{
const std::string kingName = "4King";
const std::string rookName = "4Rook";

if(currentColor == Figure::Color::White) {
	if((typeid(*board[7][4]).name() != kingName && board[7][4]->GetColor() != currentColor) && (typeid(*board[7][0]).name() != rookName && board[7][0]->GetColor() != currentColor)) {
		return false;
	}

		for(int i = 0; i < 8; ++i) {
			for(int j = 0; j < 8; ++j) {
				if(board[i][j]->GetColor() == Figure::Color::Black) {

					for(int i2 = 2; i2 <= 3; ++i2) {
						if(board[7][i2]->GetColor() != Figure::Color::None || board[i][j]->LegalMove(i, j, 7, i2, *this) || board[i][j]->LegalMove(i, j, 7, 4, *this)) {
							return false;
						}
					}
				}
			}
		}

	board[7][0]->moveFigure(7, 0, 7, 3, *this, currentColor);
	board[7][4]->moveFigure(7, 4, 7, 2, *this, currentColor);
	return true;

} else if(currentColor == Figure::Color::Black) {

		if((typeid(*board[0][4]).name() != kingName && board[0][4]->GetColor() != currentColor) && (typeid(*board[0][0]).name() != rookName && board[0][0]->GetColor() != currentColor)) {
			return false;
		}
			for(int i = 0; i < 8; ++i) {
				for(int j = 0; j < 8; ++j) {
					if(board[i][j]->GetColor() == Figure::Color::White) {

						for(int i2 = 2; i2 <= 3; ++i2) {
							if(board[0][i2]->GetColor() != Figure::Color::None || board[i][j]->LegalMove(i, j, 0, i2, *this) || board[i][j]->LegalMove(i, j, 0, 4, *this)) return false;
						}
					}
				}
			}
	
	board[0][0]->moveFigure(0, 0, 0, 3, *this, currentColor);
	board[0][4]->moveFigure(0, 4, 0, 2, *this, currentColor);
	return true;
}

	return true;
}


bool Board::shortCastle(Figure::Color currentColor)
{
const std::string kingName = "4King";
const std::string rookName = "4Rook";

if(currentColor == Figure::Color::White) {
	if((typeid(*board[7][4]).name() != kingName && board[7][4]->GetColor() != currentColor) && (typeid(*board[7][7]).name() != rookName && board[7][7]->GetColor() != currentColor)) {
	return false;
	}
		for(int i = 0; i < 8; ++i) {
			for(int j = 0; j < 8; ++j) {
				if(board[i][j]->GetColor() == Figure::Color::Black) {

					for(int i2 = 5; i2 < 7; ++i2) {
						if(board[7][i2]->GetColor() != Figure::Color::None || board[i][j]->LegalMove(i, j, 7, i2, *this) || board[i][j]->LegalMove(i, j, 7, 4, *this)) return false;
					}
				}
			}
		}
	board[7][7]->moveFigure(7, 7, 7, 5, *this, currentColor);
	board[7][4]->moveFigure(7, 4, 7, 6, *this, currentColor);
	return true;

} else if(currentColor == Figure::Color::Black) {
		if((typeid(*board[0][4]).name() != kingName && board[0][4]->GetColor() != currentColor) && (typeid(*board[0][7]).name() != rookName && board[0][7]->GetColor() != currentColor)) {
		return false;
		}

			for(int i = 0; i < 8; ++i) {
				for(int j = 0; j < 8; ++j) {
					if(board[i][j]->GetColor() == Figure::Color::White) {

						for(int i2 = 5; i2 < 7; ++i2) {
							if(board[0][i2]->GetColor() != Figure::Color::None || board[i][j]->LegalMove(i, j, 0, i2, *this) || board[i][j]->LegalMove(i, j, 0, 4, *this)) { 
								return false;} 
						}
					}
				}
			}
	
	board[0][7]->moveFigure(0, 7, 0, 5, *this, currentColor);
	board[0][4]->moveFigure(0, 4, 0, 6, *this, currentColor);
	return true;

}
	return true;
}



void Board::changeFigure(unsigned int x1, unsigned int y1, Figure::Color currentColor) 
{
	std::cout << "Choose figure to replace Pawn\n";
	for(int i = 0; i < 4; ++i) {
		std::cout << figures[i] << " ";
	}
	std::string replacedFigure{};
	std::cin >> replacedFigure;

	if(replacedFigure == "Rook") {
		delete board[x1][y1];
		board[x1][y1] = new Rook(currentColor);
	}else if(replacedFigure == "Knight") {
		delete board[x1][y1];
		board[x1][y1] = new Knight(currentColor);
	}  else if(replacedFigure == "Bishop") {
		delete board[x1][y1];
		board[x1][y1] = new Bishop(currentColor);
	} else if(replacedFigure == "Queen") {
		delete board[x1][y1];
		board[x1][y1] = new Queen(currentColor);
	} 
}


