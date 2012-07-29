//typedef int Piece;
#ifndef MOVE_HPP
#define MOVE_HPP
#include "Figures.hpp"
#include <list>
using namespace std;
class Move{
	public:
	Move(int from , int to):_from(from) , _to(to){
	}
	template<typename iterator>	
	Move(int from , int to , iterator begin , iterator end):_from(from) , _to(to) ,  capturing_positions{
	}
	int from()const{return _from;}
	int to()const{return _to;}
	capturing_positions_iterator beginCapturinPositions();
	capturing_positions_iterator endCapturinPositions();
	
	private:
	list<int> _capturing_positions;
	int _from;
	int _to;
};
/*class JumpMove{
	public:	
	JumpMove(int from,int to, int over ,const JumpMove& next):_from(from)
								,_to(to)
								,_over(over)
								,_next(new JumpMove(next))
								{
	}	
	JumpMove(int from,int to , int over):_from(from)
					,_to(to)
					,_over(over)
					,_next(0){
	}
	JumpMove(const JumpMove& jump):_from(jump._from)
					,_to(jump._to)
					,_over(jump._over)
					,_next(0){
		if(jump._next){
			_next = new JumpMove(*jump._next);
		}
		
	}
	JumpMove& operator=(const JumpMove& jump){
		_to = jump._to;
		_from = jump._from;
		_over = jump._over;
		if(_next){
			delete _next;
		}
		if(jump._next){
			_next = new JumpMove(*jump._next);
		}
	}
	~JumpMove(){
		if(_next){
			delete _next;
		}
	}
	int from()const{return _from;}
	int to()const{return _to;}
	int over()const{return _over;}
	JumpMove* next()const{return _next;}	
	private:
	int _from;
	int _to;
	int _over;
	JumpMove* _next;
};*/
class MoveHistory{
	public:
	struct Prey{
		Prey(int p , Figure f):position(p),prey(f){
		}
		Prey(){}
		int position;
		Figure prey;
	};
	
	typedef list<Prey>::const_iterator prey_iterator;
	
	MoveHistory(int from ,int to , Figure figure):_from(from),_to(to),_figure(figure){
	}
	
	MoveHistory(){
	}
	
	void addPrey(int position , Figure prey){
		pray_list.push_back(Prey(position,prey));
	}
	
	int to()const{return _to;}
	
	int from()const{return _from;}
	
	Figure figure()const {return _figure;}
	
	void setTo(int to){_to = to;}
	
	void setFrom(int from){_from = from;}
	
	void setFigure(Figure& figure){_figure = figure; }
	
	
	prey_iterator preyBegin()const{
		return pray_list.begin();
	}
	
	prey_iterator preyEnd()const{
		return pray_list.end();
	}
	

	private:
	int _to;
	int _from;
	Figure _figure;
	list<Prey> pray_list;
};
#endif
