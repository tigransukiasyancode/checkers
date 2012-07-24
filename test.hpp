class Computer{
	Move getMove(Board*);
	private:
	MinMax<StaticEvaluator> minmax;
};
Move Computer::getMove(Board* board){
	BoardValue alpha = min<BoardValue>();
	BoardValue betta = max<BoardValue>();
	vector<Move> moves = Move::getALL(board,COMPUTER);
	Move result;
	for(vector<Move>::iterator it = moves.begin() ; it != moves.end() ; ++it ){
		board->perform(*it);
		BoardValue val =  minmax(board,alpha,betta,oposite(payer),_depth);
		if(val > alpha){
			alpha = val;
			result = *it;
		}
		board->back(*it);
	}
	return result;	
}
template<class Evaluator>
class MinMax{
	private:
	Evaluator evaluator;
	BoardValue minmax(Board*,BoardValue alpha ,BoardValue betta , PlayerType , Depth);
	public:
	BoardValue operator(Board*,BoardValue alpha ,BoardValue betta , PlayerType , Depth);
};
BoardValue MinMax::minmax(Board* board , BoardValue alpha , BoardValue betta , PlayerType player , Depth depth){
	if(depth == min<Depth>()){
		return evaluator.evaluate(board,player);
	}
	vector<Move> moves = Move::getALL(board,COMPUTER);
	Move result;
	for(vector<Move>::iterator it = moves.begin() ; it != moves.end() ; ++it ){
		board->perform(*it);
		BoardValue val =  minmax(board,alpha,betta,oposite(payer),depth-1);
		if(player == MAX_PLAYER){
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
		board->back(*it);
	}
	return result;
}

