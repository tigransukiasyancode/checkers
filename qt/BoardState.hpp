#ifndef BOARD_STATE_HPP
#define BOARD_STATE_HPP
class BoardState{
	public:
	bool gameIsOver();
	Player getWinner();
	int countFiguresOfPlayer(Player);
	int countFigure(Figure);
	getAllMoves(Player);
	getJumps(Player);
	
};
#endif
