#ifndef CHECKERS_GAME_WIDGET_HPP
#define CHECKERS_GAME_WIDGET_HPP
#include <QWidget>
#include "Players.hpp"
#include "Computer.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include <vector>
#include "QtBoard.hpp"
class QtBoard;
class CheckersGameWidget:public QWidget{
	Q_OBJECT
	public:
		CheckersGameWidget();
		void start();
	public slots:
		void figureSelected(int index);
	private:
	void move(Move m){
		board.perform(m);
		
		std::vector<QtBoard::State> s( 32 , QtBoard::NONE);
		for(Move::capturing_iterator it = m.beginCapturing() ; it != m.endCapturing() ; ++it ){
			s[it->position] = QtBoard::CAPTURED;
			s[it->to] = QtBoard::MID;
		}
		s[m.from()] = QtBoard::FROM;
		Figures white_fig = Figures::getFiguresOfPlayer(white_player);
		Figures black_fig = Figures::getFiguresOfPlayer(Players::oposite(white_player));
		for(int i = 0 ; i < 32 ; ++i){
			Figure figure = board[i];
			if(figure == white_fig.checker){
				s[i] = QtBoard::WHITE;
			}else if(figure  == white_fig.king ){
				s[i] = QtBoard::WHITEKING;
			}else if(figure == black_fig.checker){
				s[i] = QtBoard::BLACK;	
			}else if(figure == black_fig.king){
				s[i] = QtBoard::BLACKKING;
			}
		}
		qt_board->draw(s);
	}
	std::vector<QtBoard::State> getStateVector(){
		
		std::vector<QtBoard::State> s( 32 , QtBoard::NONE);
		Figures white_fig = Figures::getFiguresOfPlayer(white_player);
		Figures black_fig = Figures::getFiguresOfPlayer(Players::oposite(white_player));
		for(int i = 0 ; i < 32 ; ++i){
			Figure figure = board[i];
			if(figure == white_fig.checker){
				s[i] = QtBoard::WHITE;
			}else if(figure  == white_fig.king ){
				s[i] = QtBoard::WHITEKING;
			}else if(figure == black_fig.checker){
				s[i] = QtBoard::BLACK;	
			}else if(figure == black_fig.king){
				s[i] = QtBoard::BLACKKING;
			}
		}
		return s;
	}
	void moveComputer();
	list<Move> possible_moves;
	bool is_player_moving;
	Player white_player;
	Player player; 
	Computer computer;
	Board board;
	QtBoard* qt_board;

};
#endif
