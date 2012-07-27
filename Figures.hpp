#ifndef FIGURES_HPP
#define FIGURES_HPP
#include "Player.hpp"
typedef int Figure;
class Figures{
	public:
	const static Figure HChecker = -1;
	const static Figure CChecker = 1;
	const static Figure HKing = -2;
	const static Figure CKing = 2;
	const static Figure None = 0;
	static Figure free(){
		return None;
	}
	static bool isChecker(Figure figure){
		if(figure == HChecker || figure == CChecker){
			return true;
		}
		return false;
	}
	static Figure kingOf(Player p){
		if(p == Computer){
			return CKing;
		}
		return HKing;
	}
	static Player playerOf(Figure f){
		if(f > 0){
			return Computer;
		}
		return Human;
	}
};
#endif
