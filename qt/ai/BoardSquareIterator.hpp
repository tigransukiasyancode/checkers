#ifndef BOARD_SQUARE_ITERATOR_HPP
#define BOARD_SQUARE_ITERATOR_HPP
#include "../BoardPositions.hpp"
#include <vector>
using namespace std;
class BoardSquareIterator{
	double *board ;
	int size;
	int row;
	int col;
	public:
	BoardSquareIterator(double* b,int s):board(b)
					,size(s)
					,row(0)
					,col(0)	
	{
		
	}
	void next(){
		if(++col + size > 8){
			if(++row + size <= 8){
				col = 0;
			}
		}
	}
	bool isEnd(){
		return row+size > 8;
	}
	vector<double> getValues(){
		BoardPositions::R_BOARD board_indexes = BoardPositions::getBoard();	
		vector<double> res;
		for(int i = row;i<row+size;i++){
			for(int j = col ; j<col+size;++j ){
				if(board_indexes[i][j] >= 0){
					res.push_back(board[board_indexes[i][j]]);
				}
			}
		}
		return res;
	}
	int length(){
		int count = 0 ;
		BoardPositions::R_BOARD board_indexes = BoardPositions::getBoard();	
		for(int i = row;i<row+size;i++){
			for(int j = col ; j<col+size;++j ){
				if(board_indexes[i][j] >= 0){
					++count;
				}
			}
		}
		return count;
	}
};
#endif
