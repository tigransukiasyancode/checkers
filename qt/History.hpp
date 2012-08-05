#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <deque>
#include "Move.hpp"
using namespace std;
class History{
	private:
	typedef deque<MoveHistory> history_stack;
	
	public:
	typedef history_stack::const_iterator iterator;	
	const MoveHistory& top() const{
		return data.back();
	}
	
	void pop(){
		data.pop_back();
	}
	
	void push(const MoveHistory& m){
		data.push_back(m);
	}
	
	bool empty(){
		return data.empty();
	}
	
	iterator begin()const {
		return data.begin();
	}
	
	iterator end()const{
		return data.end();
	}
	private:
	history_stack data;
	
};
#endif
