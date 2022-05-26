#ifndef _FIGURE_H
#define _FIGURE_H

#include <iostream>

class Board;

class Figure 
{
    public:
        enum class Color;
        Figure(Color color) : _color(color){}
        virtual ~Figure(){}

        enum class Color{White, Black, None};
        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) = 0;
	virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) = 0;
        virtual std::string GetName() const = 0;
        virtual void PrintFigure() const = 0;
        
        Color GetColor() const {return _color;}

    private:
        Color _color;
};

class Pawn : public Figure
{
    public:
        Pawn(Color color) : Figure(color){}
	void changeFigure(unsigned int, unsigned int, Color, Board);
        
        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) override;
		virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) override;
        virtual std::string GetName() const override {return "Pawn";}
	void setStep(bool twoStep) { this->twoStep = twoStep; }
	bool getStep() const { return this->twoStep; }
	void setSpecialDelete(bool specialDelete) { this->specialDelete = specialDelete; }
	bool getSpecialDelete() const { return this->specialDelete; }

	virtual void PrintFigure() const override
	{
            if(GetColor() == Color::White) {
                std::cout << "\u2659 ";
            } else
                    std::cout << "\u265F ";
        }

    private:
	bool twoStep{};
	bool specialDelete{};

};


class Knight : public Figure
{
    public:
        Knight(Color color) : Figure(color){}
        
        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) override;
		virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) override;
        virtual std::string GetName() const override {return "Knight";}
        virtual void PrintFigure() const override {
            if(GetColor() == Color::White) { 
                std::cout << "\u2658 ";
            } else
                    std::cout << "\u265E ";
        }

};

class Bishop : virtual public Figure
{
    public:
        Bishop(Color color) : Figure(color){}

        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) override;
		virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) override;
        virtual std::string GetName() const override {return "Bishop";}
        virtual void PrintFigure() const override {
            if(GetColor() == Color::White){
                std::cout << "\u2657 ";
            } else
                    std::cout << "\u265D ";
        }
};

class Rook : virtual public Figure
{
    public:
        Rook(Color color) : Figure(color){}
        
        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) override;
		virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) override;
        virtual std::string GetName() const override {return "Rook";}
        virtual void PrintFigure() const override {
            if(GetColor() == Color::White){
                std::cout << "\u2656 ";
            } else
                    std::cout << "\u265C ";
        }
};

class Queen : virtual public Figure, Rook,  Bishop
{
    public:
        Queen(Color color) : Figure(color), Rook(color), Bishop(color){};

        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) override;
		virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) override;
        virtual std::string GetName() const override {return "Queen";}
        virtual void PrintFigure() const override {
            if(GetColor() == Color::White){
                std::cout << "\u2655 ";
            } else
                    std::cout << "\u265B ";
        }
};

class King : public Figure
{
    public:
        King(Color color) : Figure(color){}
        
        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) override;
		virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) override;
        virtual std::string GetName() const override {return "King";}
        virtual void PrintFigure() const override {
            if(GetColor() == Color::White){
                std::cout << "\u2654 ";
            } else
                    std::cout << "\u265A ";
        }
};

class None : public Figure
{
    public:
        None(Color color) : Figure(color){}
        
        virtual bool LegalMove(unsigned int, unsigned int, unsigned int, unsigned int, Board&) override{return false;}
		virtual void moveFigure(unsigned int, unsigned int, unsigned int, unsigned int, Board&, Figure::Color) override {};
        virtual std::string GetName() const override {return "None";}
        virtual void PrintFigure() const override {
                std::cout << "  ";
    }
};
#endif // _FIGURE_H
