#include "Computer.hpp"
#include "PossibleMoves.hpp"
#include <iostream>
BoardValue Computer::min_max(Board* board , BoardValue alpha , BoardValue betta , Player player , Depth depth){
	if(depth == min<Depth>()){
		return Evaluator::evaluate(board ,max_player);
	}
	list<Move> moves ;
	PossibleMoves::getAll(board , player , &moves);
	Move result;
	if(moves.enpty()){
		if(player == max_player){
			return -100000;
		}
		return 100000;
	}
	for(list<Move>::iterator it = moves.begin() ; it != moves.end() ; ++it ){
		board->perform(*it);
		BoardValue val =  min_max( board , alpha , betta , Players::oposite(player) , depth-1 );
		if(player == max_player){
			//cout<<"kkk";
			if(val > alpha){
				alpha = val;
			}
		}else{
			
			if(val < betta){
				betta = val;
			}
		}
		board->back();
		if(betta < alpha){
			//std::cout<< alpha<<"  "<<betta<<"   "<<depth<<endl;	
			break;
		}
	}
	if(player == max_player){
		return alpha;
	}
	return betta;
}
Move Computer::getMove(Board board){
	BoardValue alpha = -100000;//min<BoardValue>();
	BoardValue betta = 100000;//max<BoardValue>();
	//cout<<int(betta);
	list<Move> moves;
	PossibleMoves::getAll(&board,max_player,&moves);
	Move result;
	for(list<Move>::iterator it = moves.begin() ; it != moves.end() ; ++it ){
		board.perform(*it);
		BoardValue val =  min_max(&board , alpha , betta , Players::oposite(max_player) , max_depth - 1);
		cout<<"val="<<val<<endl;	
		cout<<"alpha="<<int(alpha)<<endl;	
		if(val > alpha){
			//cout<<"aaaaa"<<endl;
			alpha = val;
			result = *it;
		}
		board.back();
	}
	cout<<result.to()<<endl;
	return result;
}
