#include <iostream>
#include <list>
#include <vector>
using namespace std;
#include "Move.hpp"
#include "Board.hpp"
#include "BoardPositions.hpp"
#include "PossibleMoves.hpp"
#include "Figures.hpp"
void static PossibleMoves::getChecherMoves(int index , Board* board , list<Move>* moves){
	int length;
	BoardPositions::P_MOV arr;
	BoardPositions::getChekerNextPositions(player , index , arr , &length);
	for(int j=0;j<length;++j){
		if(board->isFree(arr[j])){
			moves->push_back(Move(i , (*arr)[j] ));
		}
	}
}
void static PossibleMoves::getKingJumps(int index , Board* board , list<Move>* moves){
	BoardPositions::P_SEQ _move_sequences;
	BoardPositions::P_SEQ_LEN _lengths;
	int indexes[2][2];
	int length;
	getSequences(i,_move_sequences,_lengths,indexes,&length);
	BoardPositions::R_SEQ move_sequences = *_move_sequences;
	BoardPositions::R_SEQ_LEN lengths = *_lengths;
	for(int j = 0 ; j<length ; ++j  ){
		int seq_i = indexes[j][0];
		int sqere_i = indexes[j][1];
		int k = sqere_i == 0 ? 0 : sqere_i-1;
		for(; k >= 0 && board->isFree(move_sequences[seq_i][k]) ; --k){
			moves->push_back(Move(i,move_sequences[seq_i][k]));
		}
		k = (sqere_i == lengths[seq_i] - 1) ? sqere_i : sqere_i+1;
		for(; k < lengths[seq_i] && board->isFree(move_sequences[seq_i][k]) ; ++k){
			moves->push_back(Move(i,move_sequences[seq_i][k]));
		}	
	}
}

void static PossibleMoves::getAll( Board* board, Player player , listr<Move>* moves){
	//Board& bor = *board;
	Figures figures  = Figures::of(player);
	//list<Move> simple_moves;
	//list<JumpMove> jumps;
	for(int i = 0 ; i < board->length() ; ++i){
		if(bor[i] == figures.checker){
			getChecherMoves(i,board,moves);
			getCheckerJumps(i,board,moves);
		}else if(bor[i] == figures.king){
			getKingMoves(i,board,moves);	
			getKingJumps(i,board,moves);
		}
	}
}
void static PossibleMoves:: getCheckerJumps(int index ,Board* board , list<Move> * jumps){

	char flags[32] = {0};//list<Move> tmp;
	list<int> path;
	detectCheckerJumpsPaths(index , board , jumps , flags , &path , index);
	 //recursion(ind,board,jumps,flags,path);
	/*BoardPositions::P_CH_SEQ _seq ;
	int length = 0;
	getJumpSequencesForChecker(ind , _seq , &length);
	BoardPositions::R_CH_SEQ& seq = *_seq;
	for(int i =0 ; i<length ; ++i){
		if(isOponents(board->get(seq[i][0]),board->get(ind))  && board->isFree(seq[i][1]) && !flags[seq[i][0]] ){
			JumpMove m(ind , seq[i][1] ,board->get(ind), seq[i][0] , board->get(seq[i][0]));
			board->perform(m);
			getCheckerJumps(seq[i][1],board,&tmp);
			board->back(m);
			for(list<JumpMove>::iterator it = tmp.begin() ; it != tmp.end() ; ++it){
				jumps->push_back(JumpMove(ind , seq[i][1] ,board->get(ind) , seq[i][0] , board->get(seq[i][0]),*it));
			}
			tmp.clear();
		}
		
	}*/
}
void static PossibleMoves::detectCheckerJumpsPaths(int index 
						, Board* board 
						, list<Move>* jumps 
						, int* flags 
						, list<int>* path
						, int from ){
	bool isEndOfRecursion = true;
	BoardPositions::P_CH_SEQ _seq ;
	int length = 0;
	getJumpSequencesForChecker(ind , _seq , &length);
	BoardPositions::R_CH_SEQ seq = *_seq;
	for(int i =0 ; i<length ; ++i){
		if(Figures::isOponents(board->get(seq[i][0]),board->get(index))  && board->isFree(seq[i][1]) && !flags[seq[i][0]] ){
			isEndOfRecursion = false;
			path->push_back(seq[i][0]);
			flags[seq[i][0]] = 1;
			detectCheckerJumpsPaths(seq[i][1],board,jumps,flags,path , from);
			flags[seq[i][0]] = 0;
			path->pop_back();
			
			/*JumpMove m(ind , seq[i][1] ,board->get(ind), seq[i][0] , board->get(seq[i][0]));
			board->perform(m);
			getCheckerJumps(seq[i][1],board,&tmp);
			board->back(m);
			for(list<JumpMove>::iterator it = tmp.begin() ; it != tmp.end() ; ++it){
				jumps->push_back(JumpMove(ind , seq[i][1] ,board->get(ind) , seq[i][0] , board->get(seq[i][0]),*it));
			}
			tmp.clear();*/
		}
		
	}
	if(isEndOfRecursion && !path->empty()){
		Move m(from , index , path->begin() , path->end());
		jumps->push_back(m);
	}

}
/*void getKingJumps(int ind , Board* board , list<JumpMove>* jumps){
	SEQ* _move_sequences;
	SEQ_LEN* _lengths;
	int indexes[2][2];
	int length;
	getSequences(ind,_move_sequences,_lengths,indexes,&length);
	SEQ& move_sequences =  *_move_sequences;
	SEQ_LEN& lengths = * _lengths;
	list<JumpMove> tmp;
	for(int i = 0 ; i<length ; ++i){
		int seq_i = indexes[i][0];
		int sqere_i = indexes[i][1];
		int k = sqere_i == 0 ? 0 : sqere_i-1;
		for(; k >= 0 && board->isFree(move_sequences[seq_i][k]) ; --k){}
		if(isOponents(board->get(ind) , board->get(move_sequences[seq_i][k]))){
			int pos = move_sequences[seq_i][k];
			k==0 ? k : --k;
			for(; k >= 0 && board->isFree(move_sequences[seq_i][k]) ; --k){
				JumpMove m(ind , move_sequences[seq_i][k] , board->get(ind) , pos , board->get(pos));
				board->perform(m);
				getKingJumps(m.to(),board,&tmp);
				board->back(m);
				for(list<JumpMove>::iterator it = tmp.begin() ; it!= tmp.end() ; ++it){
					jumps->push_back(JumpMove(m.from(),m.to(),board->get(m.from()),pos,board->get(pos),*it));
				}
				tmp.clear();
			}
		}	
		k = (sqere_i == lengths[seq_i] - 1) ? lengths[seq_i] : sqere_i+1;
		for( ; k < lengths[seq_i] && board->isFree(move_sequences[seq_i][k]) ; ++k){}	
		if(isOponents(board->get(ind) , board->get(move_sequences[seq_i][k]))){
			int pos = move_sequences[seq_i][k];
			k==lengths[seq_i]-1 ? k : ++k;
			for(; k <lengths[seq_i] && board->isFree(move_sequences[seq_i][k]) ; ++k){
				JumpMove m(ind , move_sequences[seq_i][k] , board->get(ind) , pos , board->get(pos) );
				board->perform(m);
				getKingJumps(m.to(),board,&tmp);
				board->back(m);
				for(list<JumpMove>::iterator it = tmp.begin() ; it!= tmp.end() ; ++it){
					jumps->push_back(JumpMove(m.from(),m.to(),board->get(m.from()),pos,board->get(pos) ,*it));
				}
				tmp.clear();
			}
		}
	}
}*/

