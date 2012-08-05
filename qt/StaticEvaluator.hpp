#ifndef STATIC_EVALUATOR_HPP
#define STATIC_EVALUATOR_HPP
#include "types.hpp"
#include "Board.hpp"
#include "Players.hpp"
class StaticEvaluator{
	public:
	static BoardValue evaluate(Board* board, Player player);
};
#endif
