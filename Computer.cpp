#include "Computer.hpp"
#include "StaticEvaluator.hpp"

BoardValue Computer::minmax(Board* board , BoardValue alpha , BoardValue betta , PlayerType player , Depth depth){
	if(depth == min<Depth>()){
		return Evaluator::evaluate(board);
	}
	list<Move> moves ;
	MoveGenerator::getAll(player , moves);
	Move result;
	for(list<Move>::iterator it = moves.begin() ; it != moves.end() ; ++it ){
		board->perform(*it);
		BoardValue val =  minmax( board , alpha , betta , Players::oposite(payer) , depth-1 );
		if(player == COMPUTER){
			if(val > alpha){
				alpha = val;
			}
		}else{
			if(val < betta){
				betta = val
			}
		}
		if(betta < alpha){
			break;
		}
		board->back();
	}
	return result;
}
