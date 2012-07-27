#ifndef MOVE_ENGINE_HPP
#define MOVE_ENGINE_HPP
#include "History.hpp"
#include "Board.hpp"
#include "Move.hpp"
using namespace std;
class MoveEngine{
	public:
	typedef History::iterator history_iterator;
	MoveEngine(const Board&);
	void perform(const Move&);
	void perform(const JumpMove&);
	void back();
	private:
	void migrate(int from , int to );
	void place(Figure figure ,int to);
	Board board;
	History history;
};

#endif
