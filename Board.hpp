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
#include <cstring>
class Board{
	public:
	int length(){
		return _length;
	}
	bool isFree(int index){
		return get(index) == Figures::free();
	}
	Figure get(int index){
		return squares[index];
	}
	Figure operator[](int index){
		return get(index);
	}
	void init(){
		for(int i = 0;i<12;i++){
			set(i,Figures::HChecker);
			set(31-i ,Figures::CChecker);
		}
		
	}
	void free(int index){
		set(index,Figures::free());
	}
	void set(int index , Figure figure){
		squares[index] = figure;
	}
	private:	
	size_t static const _length = 32; 
	Figure squares[32];
};
#endif
