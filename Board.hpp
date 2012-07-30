/*
		+----+----+----+----+----+----+----+----+
		|    | 28 |    | 29 |    | 30 |    | 31 |
		+----+----+----+----+----+----+----+----+
		| 24 |    | 25 |    | 26 |    | 27 |    |
		+----+----+----+----+----+----+----+----+
		|    | 20 |    | 21 |    | 22 |    | 23 |
		+----+----+----+----+----+----+----+----+
		| 16 |    | 17 |    | 18 |    | 19 |    |
		+----+----+----+----+----+----+----+----+
		|    | 12 |    | 13 |    | 14 |    | 15 |
		+----+----+----+----+----+----+----+----+
		| 8  |    | 9  |    | 10 |    | 11 |    |
		+----+----+----+----+----+----+----+----+
		|    | 4  |    | 5  |    | 6  |    | 7  |
		+----+----+----+----+----+----+----+----+
		| 0  |    | 1  |    | 2  |    | 3  |    |
		+----+----+----+----+----+----+----+----+
		
*/
#ifndef BOARD_HPP
#define BOARD_HPP
#include "Move.hpp"
#include "Figures.hpp"
#include "BoardPositions.hpp"
#include "History.hpp"
#include <cstring>
class Board{
	public:
	Board(){
		for(int i=0;i<_length;i++){
			set(i,Figures::None);
		}
	}
	int length(){
		return _length;
	}
	bool isFree(int index){
		return get(index) == Figures::free();
	}
	Figure get(int index){
		return figures[index];
	}
	Figure operator[](int index){
		return get(index);
	}
	void init(){
		
		for(int i = 0;i<12;i++){
			set(i,Figures::FirstChecker);
			set(31-i ,Figures::SecondChecker);
		}
		
	}
	void free(int index){
		set(index,Figures::free());
	}
	void set(int index , Figure figure){
		figures[index] = figure;
	}
	void perform(Move& move){
		Figure figure = get(move.from());
		//int to  = get(move.to());
		MoveHistory h(move.from() , move.to() , get(move.from()));
		for(Move::capturing_iterator it = move.beginCapturing() ;it !=move.endCapturing() ; ++it){
			h.addCaptured(*it ,get(*it));
			free(*it);
		}
		place(get(move.from()),move.to());
		free(move.from());
		history.push(h);
	}
	void back(){
		if(history.empty()){
			return;
		}
		const MoveHistory& m = history.top();
		free(m.to());
		set(m.from(),m.figure());
		for(MoveHistory::captured_iterator it = m.beginCaptured() ; it != m.endCaptured() ; ++it){
			set(it->position , it->figure);	
		}
		history.pop();

	}
	private:
	void place(Figure figure ,int to){
		Player p = Figures::playerOf(figure);
		if(Figures::isChecker(figure) && BoardPositions::isInKingSequence(to,p)){
			set(to , Figures::kingOf(p));
		}else{
			set(to , figure);
		}
	}
	size_t static const _length = 32; 
	Figure figures[32];
	History history;
};
#endif
