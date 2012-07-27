#include "MoveEngine.hpp"
MoveEngine::MoveEngine(const Board& initial_board):board(initial_board){
}
void MoveEngine::perform(const Move& m){
	int from = m.from();
	int to = m.to();
	MoveHistory h(from , to , board.get(from));
	migrate(from , to);
	history.push(h);
}
void MoveEngine::back(){
	if(history.empty()){
		return;
	}
	const MoveHistory& m = history.top();
	board.free(m.to());
	board.set(m.from(),m.figure());
	for(MoveHistory::prey_iterator it = m.preyBegin() ; it != m.preyEnd() ; ++it){
		board.set(it->position , it->prey);	
	}
	history.pop();
}
void MoveEngine::perform(const JumpMove& jump){
	int from = jump.from();
	Figure figure = board.get(from);
	int to ;
	MoveHistory h;
	const JumpMove* jmp = &jump;
	board.free(from);
	while(jmp){
		int over = jmp->over();
		h.addPrey(over,board.get(over));
		board.free(over);
		to = jmp->to();
		jmp = jmp->next();		
	}
	place(figure,to);
	h.setFrom(from);
	h.setTo(to);
	h.setFigure(figure);
	history.push(h);
}
void MoveEngine::migrate(int from , int to ){
	Figure figure = board.get(from);
	place(figure,to);
	board.free(from);
}
void MoveEngine::place(Figure figure ,int to){
	Player p = Figures::playerOf(figure);
	if(Figures::isChecker(figure) && BoardPositions::isInKingSequence(to,p)){
		board.set(to , Figures::kingOf(p));
	}else{
		board.set(to , figure);
	}
}
