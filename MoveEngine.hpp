class MoveEngine{
	public:
	MoveEngine(Board);
	void perform(Move);
	void perform(JumpMove);
	void back();
	class HistoryIterator{
	}
	private:
	Board* board;
	hash_map<int,MoveHistory> move_history;
	hash_map<int,JumpHistory> jump_history;
};
class Board{
	operator[];
	set(int position,Figure)
};
class Move{
	int from;
	int to;
};
class JumpMove{
	int from;
	int to;
	JumpMove* next;	
};
class MoveGenerator{
	getAllMoves(list<Move>,list<JumpMove>,Player);
};
class Evaluator{
	evaluate();
};
min_max()
