#include <iostream>
#include <list>
#include <vector>
using namespace std;
#include "Move.hpp"
#include "Board.hpp"
#include "BoardPositions.hpp"
#include "PossibleMoves.hpp"
#include "Figures.hpp"
void  PossibleMoves::getCheckerMoves(int index , Board* board , list<Move>* moves){
	int length;
	BoardPositions::P_MOV arr;
	BoardPositions::getCheckerNextPositions(Figures::playerOf(board->get(index)) , index , arr , &length);
	for(int i=0 ; i<length ; ++i){
		if(board->isFree((*arr)[i])){
			moves->push_back(Move(index , (*arr)[i] ));
		}
	}
}
void  PossibleMoves::getKingMoves(int index , Board* board , list<Move>* moves){
	BoardPositions::P_SEQ _move_sequences;
	BoardPositions::P_SEQ_LEN _lengths;
	int indexes[2][2];
	int length;
	BoardPositions::getDiagonalSequences(index,_move_sequences,_lengths,indexes,&length);
	BoardPositions::R_SEQ move_sequences = *_move_sequences;
	BoardPositions::R_SEQ_LEN lengths = *_lengths;
	for(int j = 0 ; j<length ; ++j  ){
		int seq_i = indexes[j][0];
		int sqere_i = indexes[j][1];
		int k = sqere_i == 0 ? 0 : sqere_i-1;
		for(; k >= 0 && board->isFree(move_sequences[seq_i][k]) ; --k){
			moves->push_back(Move(index,move_sequences[seq_i][k]));

		}
		k = (sqere_i == lengths[seq_i] - 1) ? sqere_i : (sqere_i+1);
		for(; k < lengths[seq_i] && board->isFree(move_sequences[seq_i][k]) ; ++k){
			moves->push_back(Move(index,move_sequences[seq_i][k]));
		}	
	}
}

void  PossibleMoves::getAll( Board* board, Player player , list<Move>* moves){
	//Board& bor = *board;
	Figures figures  = Figures::of(player);
	//list<Move> simple_moves;
	//list<JumpMove> jumps;
	for(int i = 0 ; i < board->length() ; ++i){
		if(board->get(i) == figures.checker){
			getCheckerMoves(i,board,moves);
			getCheckerJumps(i,board,moves);
		}else if(board->get(i) == figures.king){
			getKingMoves(i,board,moves);	
			getKingJumps(i,board,moves);
		}
	}
}
void  PossibleMoves:: getCheckerJumps(int index ,Board* board , list<Move> * jumps){

	char flags[32] = {0};//list<Move> tmp;
	list<int> path;
	detectCheckerJumpsPaths(index , board->get(index) , board , jumps , flags , &path , index);
	 
}
void  PossibleMoves::detectCheckerJumpsPaths(int index 
						, Figure figure
						, Board* board 
						, list<Move>* jumps 
						, char* flags 
						, list<int>* path
						, int from ){
	bool isEndOfRecursion = true;
	BoardPositions::P_CH_SEQ _seq ;
	int length = 0;
	BoardPositions::getJumpSequencesForChecker(index , _seq , &length);
	BoardPositions::R_CH_SEQ seq = *_seq;
	for(int i =0 ; i<length ; ++i){
		int cap_ind = seq[i][0];
		int to = seq[i][1];
		if(Figures::isOponents(board->get(cap_ind) , figure)
			&& ( board->isFree(to) || flags[to] ) 
			&& !flags[cap_ind] ) 
		{
			isEndOfRecursion = false;
			path->push_back(cap_ind);
			flags[cap_ind] = 1;
			flags[index] = 1;
			detectCheckerJumpsPaths(to , figure , board , jumps , flags , path , from);
			flags[index] = 0;
			flags[cap_ind] = 0;
			path->pop_back();
		}
		
	}
	if(isEndOfRecursion && !path->empty()){
		Move m(from , index , path->begin() , path->end());
		jumps->push_back(m);
	}

}
void PossibleMoves::getKingJumps(int index , Board* board , list<Move>* jumps){
	
	char flags[32] = {0};
	list<int> capture_path;
	detectKingJumpPaths(index , board->get(index) , board , jumps , flags , &capture_path , index);
}

void PossibleMoves::detectKingJumpPaths(int index 
				, Figure figure 
				, Board* board 
				, list<Move>* jumps 
				, char* flags 
				, list<int>* capture_path 
				, int from)
			{
	bool isEndOfRecursion = true;
	BoardPositions::P_SEQ _move_sequences;
	BoardPositions::P_SEQ_LEN _lengths;
	int indexes[2][2];
	int length;
	BoardPositions::getDiagonalSequences(index,_move_sequences,_lengths,indexes,&length);
	BoardPositions::R_SEQ move_sequences =  *_move_sequences;
	BoardPositions::R_SEQ_LEN lengths = * _lengths;
	int last_captured = capture_path->empty()? -1 : capture_path->back();
	for(int i = 0 ; i<length ; ++i){
		int seq_i = indexes[i][0];
		int sqere_i = indexes[i][1];
		const int* sequence = move_sequences[seq_i]; 
		int k = sqere_i == 0 ? 0 : sqere_i-1;
		int seq_len = lengths[seq_i];
		for(; k >= 0 && ( board->isFree(sequence[k]) || flags[sequence[k]] ) && sequence[k] != last_captured ; --k){}
		if( sequence[k] != last_captured && Figures::isOponents(figure , board->get(sequence[k]))){
			int cap_ind = sequence[k];
			k==0 ? k : --k;
			for(; k >= 0 && ( board->isFree(sequence[k]) || flags[sequence[k]] ) ; --k){
				isEndOfRecursion = false;
				int to = sequence[k];
				flags[cap_ind] = 1;
				flags[index] = 1;
				capture_path->push_back(cap_ind);
				detectKingJumpPaths( to , figure , board , jumps , flags , capture_path , from);
				flags[cap_ind] = 0;
				flags[index] = 0;
				capture_path->pop_back();		
			}
		}	
		k = (sqere_i == seq_len - 1) ? seq_len : sqere_i+1;
		for( ; k < seq_len 
			&& ( board->isFree(sequence[k])  || flags[sequence[k]] ) 
			&& sequence[k] != last_captured; ++k);	
		if( sequence[k] != last_captured && Figures::isOponents(figure , board->get(sequence[k]))){
			int cap_ind = sequence[k];
			k==seq_len-1 ? k : ++k;
			for(; k < seq_len &&  ( board->isFree(sequence[k]) || flags[sequence[k]] )  ; ++k){
				isEndOfRecursion = false;
				int to = sequence[k];
				flags[cap_ind] = 1;
				flags[index] = 1;
				capture_path->push_back(cap_ind);
				detectKingJumpPaths( to , figure , board , jumps , flags , capture_path , from);
				flags[cap_ind] = 0;
				flags[index] = 0;
				capture_path->pop_back();			}
		}
	}
	if(isEndOfRecursion && !capture_path->empty()){
		Move m(from , index , capture_path->begin() , capture_path->end());
		jumps->push_back(m);
	}		
}
