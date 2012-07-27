#include "Board.hpp"

void Board::perform(Move& m){
	migrate(m.to() , m.from());
}
void Board::back(Move& move){
	set(move.from(),move.figure());
	free(move.to());
}
void Board::perform(JumpMove& jump){
	free(jump.over());
	if(!jump.next()){
		migrate(jump.from(),jump.to());//Figure figure = jump.figure();
	}else{
		set(jump.to(),jump.figure());
		free(jump.from());
		perform(*jump.next());
	}
}
void Board::back(JumpMove& jump){
	JumpMove* jmp = &jump;
	set(jump.from(),jump.figure());
	while(jmp){
		set(jmp->over(),jmp->prey());
		free(jmp->to());
		jmp = jmp->next();
	}
}
void Board::migrate(int from , int to ){
	Figure figure = get(from);
	Player p = Figures::playerOf(figure);
	if(Figures::isChecker(figure) && BoardPositions::isInKingSequence(to,p)){
		set(to , Figures::kingOf(p));
	}else{
		set(to , figure);
	}
	free(from);
}
