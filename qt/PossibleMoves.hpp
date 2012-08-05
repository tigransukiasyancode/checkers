#ifndef POSSIBLE_MOVES_HPP
#define POSSIBLE_MOVES_HPP
#include <list>
#include "Players.hpp"
#include "Move.hpp"
#include "Board.hpp"

class PossibleMoves{
	public:
	static void getAll(Board* , Player , list<Move>* );
	static void getAllForIndex(Board* , int index , list<Move>* );
	static void getCheckerMoves(int , Board* , list<Move>*);
	static void getKingMoves(int , Board* , list<Move>*);
	static void getCheckerJumps(int  , Board* , list<Move>* );
	static void getKingJumps(int  , Board*  , list<Move>* );
	private:
	static void detectCheckerJumpsPaths(int index 
					, Figure figure
					, Board* board 
					, list<Move>* jumps 
					, char* flags 
					, list<Move::CapturingPosition>* path
					, int from );
	static void detectKingJumpPaths(int index 
				, Figure figure 
				, Board* board 
				, list<Move>* jumps 
				, char* flags 
				, list<Move::CapturingPosition>* capture_path 
				, int firom);
};	
#endif
