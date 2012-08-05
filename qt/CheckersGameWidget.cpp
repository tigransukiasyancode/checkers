#include "CheckersGameWidget.hpp"
#include "QtBoard.hpp"
#include "Figures.hpp"
#include "PossibleMoves.cpp"
#include <QDebug>
CheckersGameWidget::CheckersGameWidget():QWidget(NULL)
					,computer(Players::oposite(player))
					,player(FirstPlayer)
					,white_player(FirstPlayer)
					,is_player_moving(false){
	board.init();
	//board.set(1, Figures::FirstKing);
	//board.set(2, Figures::SecondKing);
	std::vector<QtBoard::State> st = getStateVector();
	qt_board = new QtBoard(this,st);
	connect(qt_board, SIGNAL(boardPresed(int)), this, SLOT(figureSelected(int)));
	qt_board->show();	
	
	resize(320,320);
}
void CheckersGameWidget::figureSelected(int index){
	qDebug()<<index<<"ssss";
	if(!is_player_moving){	
		if(Figures::playerOf(board[index]) == player){
			PossibleMoves::getAllForIndex(&board,index,&possible_moves);
			is_player_moving = true;
			qDebug()<<"moving";
		}
	}else{
		list<Move>::iterator it = possible_moves.begin();
		for(;it != possible_moves.end(); ){
			if(index == it->to()){
				break;
			}
			Move::capturing_iterator cap_it = it->beginCapturing();
			for( ; cap_it != it->endCapturing() ;++cap_it){
				if(index == cap_it->to){
					break;
				}
			}
			if(cap_it == it->endCapturing() ){
				it = possible_moves.erase(it);
			}else{
				++it;
			}
		}
		if(possible_moves.empty()){
			is_player_moving =false;
			qDebug()<<"disable";
		}
		if(it != possible_moves.end()){
			is_player_moving = false;
			Move m(*it);
			possible_moves.clear();
			move(m);
			moveComputer(); 
		}
		
	}
}
void CheckersGameWidget::start(){
	if(player != white_player ){
		moveComputer();
	}	
	/*vector<QtBoard::State> st(32,QtBoard::NONE) ;
	st[3] = QtBoard::WHITE;
	qt_board->draw(st); */
	/*if(white_player != player){
		Move m = computer.getMove(board);
	}*/
}
void CheckersGameWidget::moveComputer(){
	Move m = computer.getMove(board);
	move(m);
 
}
