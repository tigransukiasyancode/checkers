#include "StaticEvaluator.hpp"
#include <cstdlib>
BoardValue StaticEvaluator::evaluate(Board* board , Player max_player){
	Figures f = Figures::getFiguresOfPlayer(max_player);
	int max_figures = 0;
	int min_figures = 0;
	int max_kings = 0;
	int min_kings = 0;
	for(int i = 0;i<board->length();i++){
		Figure ch = board->get(i);
		if(Figures::playerOf(ch) == max_player){
			++max_figures;
			if(ch == f.king ){
				++max_kings;
			}
		}else if(ch != Figures::None){
			++min_figures;
			if(Figures::isKing(ch)){
				++min_kings;
			}	
		}	
	}
	float eval = (max_figures - min_figures);
	eval+= 20*(max_kings - min_kings);
	return eval;
}
