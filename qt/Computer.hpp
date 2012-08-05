#ifndef COMPUTER_HPP
#define COMPUTER_HPP
#include "StaticEvaluator.hpp"
#include "Board.hpp"
#include "types.hpp"
#include "Move.hpp"
class Computer{
	public:
	Computer(Player max , Depth depth = 3):max_player(max),max_depth(depth){}
	Move getMove(Board );
	private:
	Player max_player;
	Depth max_depth;
	typedef StaticEvaluator Evaluator;
	BoardValue min_max(Board* , BoardValue alpha , BoardValue betta , Player , Depth);
};
#endif

