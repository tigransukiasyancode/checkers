#ifndef FIGURES_HPP
#define FIGURES_HPP
#include <iostream>
using namespace std;
#include "Players.hpp"
typedef int Figure;
class Figures{
	public:
	const static Figure FirstChecker = -1;
	const static Figure SecondChecker = 1;
	const static Figure FirstKing = -2;
	const static Figure SecondKing = 2;
	const static Figure None = 0;
	static Figure free(){
		return None;
	}
	static bool isChecker(Figure figure){
		if(figure == FirstChecker || figure == SecondChecker){
			return true;
		}
		return false;
	}
	static bool isKing(Figure f){
		if(f ==FirstKing || f == SecondKing){
			return true;
		}
		return false;
	}
	static Figure kingOf(Player p){
		if(p == FirstPlayer){
			return FirstKing;
		}
		return SecondKing;
	}
	static Player playerOf(Figure f){
		if(f > 0){
			return SecondPlayer;
		}
		return FirstPlayer;
	}
	static Figures getFiguresOfPlayer(Player player){
		if(player == FirstPlayer){
			return Figures(FirstChecker , FirstKing);
		}
		return Figures(SecondChecker , SecondKing);
	}
	static bool isOponents(Figure f1 , Figure f2){
		//cout<<"figures"<<f1<<"=="<<f2<<endl;
		return (f1*f2 < 0);
		
	}	
	public:
	Figure checker;
	Figure king;
	Figures(Figure c ,Figure k):checker(c),king(k){}
};
#endif
