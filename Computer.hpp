#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include "Board.hpp"
#include "types.hpp"
#include "Move.hpp"
class StaticEvaluator;
class Computer{
	public:
	Move getMove(Board *);
	private:
	typedef StaticEvaluator Evaluator;
	BoardValue min_max(Board* , BoardValue alpha , BoardValue betta , PlayerType , Depth);
};
#endif

