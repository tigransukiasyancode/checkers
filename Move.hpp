//typedef int Piece;
#ifndef MOVE_HPP
#define MOVE_HPP
#include "Figures.hpp"
class Move{
	public:
	Move(int from,int to, Figure figure):_from(from) , _to(to) , _figure(figure){
	}	
	int from(){return _from;}
	int to(){return _to;}
	Figure figure(){return _figure;}
	private:
	int _from;
	int _to;
	Figure _figure;
};
class JumpMove{
	public:	
	JumpMove(int from,int to,Figure figure , int over , Figure prey,const JumpMove& next):_from(from)
											,_to(to)
											,_figure(figure)
											,_over(over)
											,_prey(prey)
											{
		_next = new JumpMove(next);
	}	
	JumpMove(int from,int to,Figure figure , int over,Figure prey):_from(from)
								,_to(to)
								,_figure(figure)
								,_over(over)
								,_prey(prey)
								,_next(0){

		
	}
	JumpMove(const JumpMove& jump):_from(jump._from)
					,_to(jump._to)
					,_over(jump._over)
					,_figure(jump._figure)
					,_prey(jump._prey)
					,_next(0){
		if(jump._next){
			_next = new JumpMove(*jump._next);
		}
		
	}
	JumpMove& operator=(const JumpMove& jump){
		_to = jump._to;
		_from = jump._from;
		_over = jump._over;
		_figure = jump._figure;
		_prey = jump._prey;
		delete _next;
		if(jump._next){
			_next = new JumpMove(*jump._next);
		}
	}
	~JumpMove(){
		if(_next){
			delete _next;
		}
	}
	int from(){return _from;}
	int to(){return _to;}
	int over(){return _over;}
	Figure figure(){return _figure;}
	Figure prey(){return _prey;}
	JumpMove* next(){return _next;}	
	private:
	int _from;
	int _to;
	int _over;
	Figure _figure;
	Figure _prey;
	JumpMove* _next;
};
#endif
