#include "figure.h"
#include "board.h"

bool Pawn::LegalMove(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard)
{
    std::string str = "4Pawn";	
    if(x1 < 0 || x1 >= 9 || y1 < 0 || y1 >= 9 || x2 < 0 || x2 >= 9 || y2 < 0 || y2 >= 9) return false;

    if(this->GetColor() == Figure::Color::White){
        if(x1 - x2 == 2 && y2 == y1){
            if(x1 == 6 && currentBoard.board[x1-1][y1]->GetColor() == Figure::Color::None && currentBoard.board[x1-2][y1]->GetColor() == Figure::Color::None){
			setStep(1);
			return true;
		} else {	
			setStep(0);
			return false;
		}
        } else if(x1 - x2 == 1 && y1 == y2){
	    
            if(currentBoard.board[x2][y2]->GetColor() == Figure::Color::None) {
			setStep(0);
			return true;
			}
        }

        else if(x1 - x2 == 1 && (y2 - y1 == 1 || y2 - y1 == -1)) {
            if(currentBoard.board[x2][y2]->GetColor() == Figure::Color::Black) {
               	return true;
		} 
	    else if(currentBoard.board[x2][y2]->GetColor() == Figure::Color::None && typeid(*(currentBoard.board[x2+1][y2])).name() == str && currentBoard.board[x2+1][y2]->GetColor() == Color::Black && (static_cast<Pawn*>(currentBoard.board[x2+1][y2])->getStep()) ) {
			setSpecialDelete(1);
			return true;}
		}
		else 
                    return false;
    }
    else if(this->GetColor() == Figure::Color::Black){
        if(x1 - x2 == -2 && y2 == y1) {
            
            if(x1 == 1 && currentBoard.board[x1+1][y1]->GetColor() == Figure::Color::None && currentBoard.board[x1+2][y1]->GetColor() == Figure::Color::None) {
		setStep(1);
		return true;

            } else { return false;}

        } else if(x1 - x2 == -1 && y1 == y2) {

            if(currentBoard.board[x2][y2]->GetColor() == Figure::Color::None) {		
			setStep(0);
		    	return true;
			}

        }
        else if(x1 - x2 == -1 && (y2 - y1 == 1 || y2 - y1 == -1)) {
         
            if(currentBoard.board[x2][y2]->GetColor() == Figure::Color::White) {
		return true;

            } 
	    
else if(currentBoard.board[x2][y2]->GetColor() == Figure::Color::None && typeid(*(currentBoard.board[x2-1][y2])).name() == str && currentBoard.board[x2-1][y2]->GetColor() == Color::White && (static_cast<Pawn*>(currentBoard.board[x2-1][y2])->getStep()) ) {
			setSpecialDelete(1);
			return true;}
		}
	   
	    else {
                    return false;
			}
        }
    
    return false; 
}

void Pawn::moveFigure(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard, Figure::Color currentColor)
{
	Figure::Color color = currentBoard.board[x1][y1]->GetColor();
	bool twoStep = getStep();
	bool specialDelete = getSpecialDelete();
	delete currentBoard.board[x1][y1];
	delete currentBoard.board[x2][y2];
	currentBoard.board[x1][y1] = new None(Figure::Color::None);
	currentBoard.board[x2][y2] = new Pawn(currentColor);
	static_cast<Pawn*>(currentBoard.board[x2][y2])->setStep(twoStep);
	
	if(color == Figure::Color::Black) {
	if(specialDelete) {
		delete currentBoard.board[x2-1][y2];
		currentBoard.board[x2-1][y2] = new None(Figure::Color::None);
	}
	}
	else if(color == Figure::Color::White) {
	if(specialDelete) {
		delete currentBoard.board[x2+1][y2];
		currentBoard.board[x2+1][y2] = new None(Figure::Color::None);
		}
	}
	currentBoard.PrintBoard();	
}

bool Knight::LegalMove(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,Board& currentBoard)
{
if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::White && currentBoard.board[x2][y2]->GetColor() == Figure::Color::White) {
		return false;

	} else if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::Black && currentBoard.board[x2][y2]->GetColor() == Figure::Color::Black) {
			return false;

	} else {

		if((x1 - x2 == -2 || x1 - x2 == 2) && (y1 - y2 == 1 || y1 - y2 == -1)) {
			return true;
		
		} else if((x1 - x2 == -1 || x1 - x2 == 1 ) && (y1 - y2 == -2 || y1 - y2 == 2)) {
			return true;

		} else return false;
	
			return true;
		}
			return false;
}


void Knight::moveFigure(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard, Figure::Color currentColor)
{
	delete currentBoard.board[x1][y1];
	delete currentBoard.board[x2][y2];
	currentBoard.board[x1][y1] = new None(Figure::Color::None);
	currentBoard.board[x2][y2] = new Knight(currentColor);
}


bool Rook::LegalMove(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard)
{
	char constant = 'x';

	if(x1 == x2) {
		constant = 'x';

	} else if(y1 == y2) {
		constant = 'y';


	} else return false;

	if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::White && currentBoard.board[x2][y2]->GetColor() == Figure::Color::White) {
		return false;

	} else if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::Black && currentBoard.board[x2][y2]->GetColor() == Figure::Color::Black) {
		return false;

	} else if(constant == 'x') {

	int tmp_max = std::max(y1, y2);
	int tmp_min = std::min(y1, y2);

		for(int i = tmp_min + 1; i < tmp_max; ++i) {
			if(currentBoard.board[x2][i]->GetColor() != Figure::Color::None) return false;
		}

	} else if(constant == 'y') {

	int tmp_max = std::max(x1, x2);
	int tmp_min = std::min(x1, x2);

		for(int i = tmp_min + 1; i < tmp_max; ++i) {
			if(currentBoard.board[i][y2]->GetColor() != Figure::Color::None) return false;
		}

	} 
	
		return true;
}


void Rook::moveFigure(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard, Figure::Color currentColor)
{
	delete currentBoard.board[x1][y1];
	delete currentBoard.board[x2][y2];
	currentBoard.board[x1][y1] = new None(Figure::Color::None);
	currentBoard.board[x2][y2] = new Rook(currentColor);
}


bool Bishop::LegalMove(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard)
{

	if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::White && currentBoard.board[x2][y2]->GetColor() == Figure::Color::White) {
		return false;

	} else if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::Black && currentBoard.board[x2][y2]->GetColor() == Figure::Color::Black) {
		return false;
	
	} else {
		bool top_left = (x1 > x2 && y1 > y2);
		bool low_right = (x1 < x2 && y1 < y2);
		bool top_right = (x1 > x2 && y1 < y2);
		bool low_left = (x1 < x2 && y1 > y2);

		int tmp_x1 = x1;
		int tmp_y1 = y1;

		if(top_left || low_right) {
			if(x1 - y1 != x2 - y2) {
				return false;
			} 

		} else if(top_right || low_left) {
			if(x1 + y1 != x2 + y2) {
				return false;
			}
		} 

		while(true) {

			if(top_left) {
				--x1;
				--y1;

			} else if(low_right) {
				++x1;
				++y1;

			} else if(top_right) {
				--x1;
				++y1;

			} else if(low_left) {
				++x1;
				--y1;
			}

			if(x1 == x2 && y1 == y2) {
				break;

			} if(currentBoard.board[x1][y1]->GetColor() != Figure::Color::None) {

				return false;
			}
		}

	}
	return true;
}

void Bishop::moveFigure(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard, Figure::Color currentColor)
{
	delete currentBoard.board[x1][y1];
	delete currentBoard.board[x2][y2];
	currentBoard.board[x1][y1] = new None(Figure::Color::None);
	currentBoard.board[x2][y2] = new Bishop(currentColor);
}

bool Queen::LegalMove(unsigned int x1, unsigned int y1, unsigned x2, unsigned int y2, Board& currentBoard)
{
	if(x1 == x2 && y1 == y2) { return false;}
	bool rook, bishop;
	rook = Rook::LegalMove(x1, y1, x2, y2, currentBoard);
	
	if(!rook)
	bishop = Bishop::LegalMove(x1, y1, x2, y2, currentBoard);
	if(bishop || rook) {
		return true;
	}
	
	return false;

}

void Queen::moveFigure(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard, Figure::Color currentColor)
{
	delete currentBoard.board[x1][y1];
	delete currentBoard.board[x2][y2];
	currentBoard.board[x1][y1] = new None(Figure::Color::None);
	currentBoard.board[x2][y2] = new Queen(currentColor);
}


bool King::LegalMove(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard)
{

	if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::White && currentBoard.board[x2][y2]->GetColor() == Figure::Color::White) {
		return false;

	} else if(currentBoard.board[x1][y1]->GetColor() == Figure::Color::Black && currentBoard.board[x2][y2]->GetColor() == Figure::Color::Black) {
		return false;
	}



	const std::string kingName = "4King";
	const std::string queeneName = "5Queen";
	const std::string rookName = "4Rook";
	const std::string bishopName = "6Bishop";
	const std::string pawnName = "4Pawn";
	const std::string knightName = "6Knight";

	auto currentColor = currentBoard.board[x1][y1]->GetColor();


if(x2 != 0) {
		if(typeid(*(currentBoard.board[x2 - 1][y2])).name() == kingName && currentBoard.board[x2 - 1][y2]->GetColor() != currentColor || typeid((*currentBoard.board[x2 - 1][y2])).name() == kingName && currentBoard.board[x2-1][y2]->GetColor() != currentColor) return false;
	}	
	if(x2 != 0 && y2 + 1 <= 7) {
		if(typeid(*(currentBoard.board[x2 - 1][y2 + 1])).name() == kingName && currentBoard.board[x2 - 1][y2 + 1]->GetColor() != currentColor || typeid((*currentBoard.board[x2 - 1][y2 + 1])).name() == kingName && currentBoard.board[x2-1][y2 + 1]->GetColor() != currentColor) return false;
	
		}
	if(y2 + 1 <= 7)	{
		if(typeid(*(currentBoard.board[x2][y2+1])).name() == kingName && currentBoard.board[x2][y2+1]->GetColor() != currentColor || typeid((*currentBoard.board[x2][y2+1])).name() == kingName && currentBoard.board[x2][y2+1]->GetColor() != currentColor) return false;
	
		}
	if(x2 + 1 <= 7 && y2 + 1 <= 7) {
		if(typeid(*(currentBoard.board[x2+1][y2+1])).name() == kingName && currentBoard.board[x2+1][y2+1]->GetColor() != currentColor || typeid((*currentBoard.board[x2+1][y2+1])).name() == kingName && currentBoard.board[x2+1][y2+1]->GetColor() != currentColor) return false;
	
	}
	if(x2 + 1 <= 7) {
		if(typeid(*(currentBoard.board[x2+1][y2])).name() == kingName && currentBoard.board[x2+1][y2]->GetColor() != currentColor || typeid((*currentBoard.board[x2+1][y2])).name() == kingName && currentBoard.board[x2+1][y2]->GetColor() != currentColor) return false;
	
	}	
	if(x2 + 1 <= 7 && y2 != 0) {
		if(typeid(*(currentBoard.board[x2+1][y2-1])).name() == kingName && currentBoard.board[x2+1][y2-1]->GetColor() != currentColor || typeid((*currentBoard.board[x2+1][y2-1])).name() == kingName && currentBoard.board[x2+1][y2-1]->GetColor() != currentColor) return false;
		
	}
	if(y2 != 0) {
	if(typeid(*(currentBoard.board[x2][y2-1])).name() == kingName && currentBoard.board[x2][y2-1]->GetColor() != currentColor || typeid((*currentBoard.board[x2][y2-1])).name() == kingName && currentBoard.board[x2][y2-1]->GetColor() != currentColor) return false;
	
	}
	if(x2 != 0 && y2 != 0) {
		if(typeid(*(currentBoard.board[x2-1][y2-1])).name() == kingName && currentBoard.board[x2-1][y2-1]->GetColor() != currentColor || typeid((*currentBoard.board[x2-1][y2-1])).name() == kingName && currentBoard.board[x2-1][y2-1]->GetColor() != currentColor) return false;
	
	}

auto opponentColor = currentBoard.board[x1][y1]->GetColor() == Figure::Color::White ? Figure::Color::Black : Figure::Color::White;
std::string rememberFigure;

bool b = false;

	if(currentBoard.board[x2][y2]->GetColor() == opponentColor) {
		b = true;
		rememberFigure = typeid(*currentBoard.board[x2][y2]).name();
		delete currentBoard.board[x2][y2];
		currentBoard.board[x2][y2] = new None(Figure::Color::None);
		for(int i = 0; i < 8; ++i) {
			for(int j = 0; j < 8; ++j) {
				if(currentBoard.board[i][j]->GetColor() == opponentColor) {
						
					if(currentBoard.board[i][j]->LegalMove(i, j, x2, y2, currentBoard)) {

	if(rememberFigure == "4Pawn") currentBoard.board[x2][y2] = new Pawn(opponentColor);

	 else if(rememberFigure == "6Knight") currentBoard.board[x2][y2] = new Knight(opponentColor);
	  
	   else if(rememberFigure == "6Bishop") currentBoard.board[x2][y2] = new Bishop(opponentColor);
	   
	      else if(rememberFigure == "5Queen") currentBoard.board[x2][y2] = new Queen(opponentColor);
	      
	      	else if(rememberFigure == "4King") currentBoard.board[x2][y2] = new King(opponentColor);

		  else if(rememberFigure == "4Rook") currentBoard.board[x2][y2] = new Rook(opponentColor);

						return false;

					} 

				}
			}
		}
	}
	if(b) {

	if(rememberFigure == "4Pawn") currentBoard.board[x2][y2] = new Pawn(opponentColor);

	 else if(rememberFigure == "6Knight") currentBoard.board[x2][y2] = new Knight(opponentColor);
	  
	   else if(rememberFigure == "6Bishop") currentBoard.board[x2][y2] = new Bishop(opponentColor);
	   
	      else if(rememberFigure == "5Queen") currentBoard.board[x2][y2] = new Queen(opponentColor);
	      
	      	else if(rememberFigure == "4King") currentBoard.board[x2][y2] = new King(opponentColor);

		  else if(rememberFigure == "4Rook") currentBoard.board[x2][y2] = new Rook(opponentColor);
	}



delete currentBoard.board[x1][y1];
currentBoard.board[x1][y1] = new None(Figure::Color::None);



		for(int i = 0; i < 8; ++i) {
			for(int j = 0; j < 8; ++j) {
				if(currentBoard.board[i][j]->GetColor() == opponentColor) {
					if(currentBoard.board[i][j]->LegalMove(i, j, x2, y2, currentBoard)) {
						delete currentBoard.board[x1][y1];
						currentBoard.board[x1][y1] = new King(currentColor);
						return false;
					}
				}
			}
		}
	delete currentBoard.board[x1][y1];
	currentBoard.board[x1][y1] = new King(currentColor);

	if((x1 == x2 && y1 == y2 + 1) || (x1 == x2 && y1 == y2 - 1)) return true;

	 else if(y1 == y2 && (x1 == x2 + 1 || x1 == x2 - 1)) return true;

	  else if(y1 == y2 + 1 && x1 == x2 + 1) return true;

	   else if(y1 == y2 + 1 && x1 == x2 - 1) return true;

	    else if(y1 == y2 - 1 && x1 == x2 - 1) return true;

	     else if(y1 == y2 - 1 && x1 == x2 + 1) return true;


	return false;
}

void King::moveFigure(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Board& currentBoard, Figure::Color currentColor)
{
	delete currentBoard.board[x1][y1];
	delete currentBoard.board[x2][y2];

	currentBoard.board[x1][y1] = new None(Figure::Color::None);
	currentBoard.board[x2][y2] = new King(currentColor);
}
