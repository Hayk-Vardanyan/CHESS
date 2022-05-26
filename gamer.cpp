#include "gamer.h"
#include "board.h"

void Gamer::PlayGame() const
{
  std::string rookName = "4Rook";
  std::string knightName = "6Knight";
  std::string bishopName = "6Bishop";
  std::string queenName = "5Queen";

   Figure::Color currentColor{Figure::Color::White};
   Figure::Color opponentColor;

   bool whiteKingMoved = false;
   bool blackKingMoved = false;
   const std::string kingName = "4King";
   std::string from, to{};
   unsigned int x1;
   unsigned int y1;
   unsigned int x2;
   unsigned int y2;
    Board gameBoard;
    std::string pawnName = "4Pawn";

    while(true) {

	do {
		system("clear");

		std::cout << "Your move ";
		(currentColor == Figure::Color::White ? std::cout << "White" : std::cout << "Black");
		opponentColor = (currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White);

		std::cout << '\n';
        	gameBoard.PrintBoard();
        	std::cin >> from;

			if(from != "O-O-O" && from != "O-O") {
			std::cin >> to;
		}

	if(from.size() > 2 || to.size() > 2) { continue; }

	if((from[0] >= 'a' && from[0] <= 'h') && (from[1] >= 49 && from[1] <= 56)) {
        	y1 = from[0] - 'a';
        	x1 = 8 - (from[1] - 48);
        	y2 = to[0] - 'a';
        	x2 = 8 - (to[1] - 48);

	} else { continue; }

				if(from == "O-O-O") {
					if((currentColor == Figure::Color::White && !whiteKingMoved) || currentColor == Figure::Color::Black && !blackKingMoved) {
				if(gameBoard.longCastle(currentColor)) {

				currentColor = (currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White);
				continue;
				
				} else continue;

					}

			} else if(from == "O-O") {
				if((currentColor == Figure::Color::White && !whiteKingMoved) || (currentColor == Figure::Color::Black && !blackKingMoved)) {
					if(gameBoard.shortCastle(currentColor)) {

						currentColor = (currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White);
						continue;

				} else continue;
				}
			}

	if(whiteKingMoved == false && currentColor == Figure::Color::White) {
		if(typeid(*(gameBoard.board[x1][y1])).name() == kingName && (gameBoard.board[x1][y1]->LegalMove(x1, y1, x2, y2, gameBoard))) {
			whiteKingMoved = true;
		}

	} else if(blackKingMoved == false && currentColor == Figure::Color::Black) {
		if(typeid(*(gameBoard.board[x1][y1])).name() == kingName && (gameBoard.board[x1][y1]->LegalMove(x1, y1, x2, y2, gameBoard))) {
			blackKingMoved = true;
		}

	}

	} while(!(gameBoard.board[x1][y1]->GetColor() == currentColor) || !(gameBoard.board[x1][y1]->LegalMove(x1, y1, x2, y2, gameBoard)));	
	
			std::string rememberFigure = typeid(*gameBoard.board[x2][y2]).name();
			gameBoard.board[x1][y1]->moveFigure(x1, y1, x2, y2, gameBoard, currentColor);
			if((typeid(*(gameBoard.board[x2][y2])).name() == pawnName) &&  (x2 == 0 || x2 == 7)) {
					gameBoard.changeFigure(x2, y2, currentColor);
			}
					
		
			if(gameBoard.isChess((currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White)).first) {
			gameBoard.board[x2][y2]->moveFigure(x2, y2, x1, y1, gameBoard, currentColor);
			
			if(rememberFigure == pawnName) gameBoard.board[x2][y2] = new Pawn(opponentColor);	
			else if(rememberFigure == knightName) gameBoard.board[x2][y2] = new Knight(opponentColor);	
			if(rememberFigure == bishopName) gameBoard.board[x2][y2] = new Bishop(opponentColor);	
			if(rememberFigure == queenName) gameBoard.board[x2][y2] = new Queen(opponentColor);	
			if(rememberFigure == rookName) gameBoard.board[x2][y2] = new Rook(opponentColor);	
			continue;
			}

			std::pair<bool, std::pair<unsigned int, unsigned int> > chessPosition = gameBoard.isChess(currentColor);
			if (chessPosition.first) {
				if (gameBoard.isMate(chessPosition.second.first, chessPosition.second.second)) {
					std::cout << "The winner is " << (currentColor == Figure::Color::White ? "White" : "Black") << '\n';
					gameBoard.PrintBoard();
					break;
				}

			} else {

				if(gameBoard.isStalemate((currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White))) {
					gameBoard.PrintBoard();
					std::cout << "There are no moves for " << (currentColor == Figure::Color::White ? "Black" : "White") << '\t';
					std::cout << "Stalemate\n";
					break;
				}
			}
		currentColor = (currentColor == Figure::Color::White ? Figure::Color::Black : Figure::Color::White);
	}
}
