#include <iostream>
using namespace std;
#include "BoardPositions.hpp"
void BoardPositions::getCheckerNextPositions(Player player , int ind , P_MOV& arr , int* length){
	static MOV moves [2][32]= {
		//computer
		{
			 /*0*/ {}	,/*1*/{}	, /*2*/{}     , /*3*/{}
			, /*4*/{0,1}	, /*5*/{1,2}	, /*6*/{2,3}	, /*7*/{3}
			, /*8*/{4}	, /*9*/{4,5}	, /*10*/{5,6}	, /*11*/{6,7}
			, /*12*/{8,9}	, /*13*/{9,10}	, /*14*/{10,11}	, /*15*/{11}
			, /*16*/{12}	, /*17*/{12,13}	, /*18*/{13,14}	, /*19*/{14,15}
			, /*20*/{16,17}	, /*21*/{17,18}	, /*22*/{18,19}	, /*23*/{19}
			, /*24*/{20}	, /*25*/{20,21}	, /*26*/{21,22}	, /*27*/{22,23}
			, /*28*/{24,25}	, /*29*/{25,26}	, /*30*/{26,27}	, /*31*/{27}
		},
		//human
		{	
			 /*0*/ {4}	,/*1*/{4,5}	, /*2*/{5,6}     , /*3*/{6,7}
			, /*4*/{8,9}	, /*5*/{9,10}	, /*6*/{10,11}	, /*7*/{11}
			, /*8*/{12}	, /*9*/{12,13}	, /*10*/{13,14}	, /*11*/{15}
			, /*12*/{16,17}	, /*13*/{17,18}	, /*14*/{18,19}	, /*15*/{19}
			, /*16*/{20}	, /*17*/{20,21}	, /*18*/{21,22}	, /*19*/{22,23}
			, /*20*/{24,25}	, /*21*/{25,26}	, /*22*/{26,27}	, /*23*/{27}
			, /*24*/{28}	, /*25*/{28,29}	, /*26*/{29,30}	, /*27*/{30,31}
			, /*28*/{}	, /*29*/{}	, /*30*/{}	, /*31*/{}
		}
	};
	static int lengths[32] ={0,0,0,0,2,2,2,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1};
	int player_index = getIndex(player);
	arr =& moves[player_index][ind];
	*length =( ( player_index == 1) ? lengths[31-ind]:lengths[ind]); 		
}
void BoardPositions::getDiagonalSequences(int ind , P_SEQ& move_sequences ,P_SEQ_LEN& lengths ,int (*indexes) [2] , int* length ){
	static SEQ sequences = {
	/*0*/	 {24,28}      
	/*1*/	,{16,20,25,29}
	/*2*/	,{8,12,17,21,26,30}
	/*3*/	,{0,4,9,13,18,22,27,31}
	/*4*/	,{1,5,10,14,19,23}
	/*5*/	,{2,6,11,15}
	/*6*/	,{3,7}
	/*7*/	,{23,27,30}
	/*8*/	,{15,19,22,26,29}
	/*9*/	,{7,11,14,18,21,25,28}
	/*10*/	,{3,6,10,13,17,20,24}
	/*11*/	,{2,5,9,12,16}
	/*12*/	,{1,4,8}};
	static SEQ_LEN sequence_lengths = {2,4,6,8,6,4,2,3,5,7,7,5,3};
	/*	
		squere_indexes = {
			indexes=>{
				sequence index;
				squere index in sequence
				-1(end of array)
			}
		}
	*/
	static int squere_indexes[32][5] = {
	 /*0*/  {3,0,-1}	,/*1*/ {4,0,12,0,-1}  ,/*2*/ {5,0,11,0,-1}  ,/*3*/ {6,0,10,0,-1}
	,/*4*/	{3,1,12,1,-1}   ,/*5*/ {4,1,11,1,-1}  ,/*6*/ {5,1,10,1,-1}  ,/*7*/ {6,1,9,0,-1}
	,/*8*/	{2,0,12,2,-1}   ,/*9*/ {3,2,11,2,-1}  ,/*10*/{4,2,10,2,-1}  ,/*11*/{5,2,9,1,-1}
	,/*12*/	{2,1,11,3,-1}   ,/*13*/{3,3,10,3,-1}  ,/*14*/{4,3,9,2,-1}   ,/*15*/{5,3,8,0,-1}
	,/*16*/	{1,0,11,4,-1}   ,/*17*/{2,2,10,4,-1}  ,/*18*/{3,4,9,3,-1}   ,/*19*/{4,4,8,1,-1}
	,/*20*/	{1,1,10,5,-1}   ,/*21*/{2,3,9,4,-1}   ,/*22*/{3,5,8,2,-1}   ,/*23*/{4,5,7,0,-1}
	,/*24*/	{0,0,10,6,-1}   ,/*25*/{1,2,9,5,-1}   ,/*26*/{2,4,8,3,-1}   ,/*27*/{3,6,7,1,-1}
	,/*28*/	{0,1,9,6,-1}    ,/*29*/{1,3,8,4,-1}   ,/*30*/{2,5,7,2,-1}   ,/*31*/{3,7,-1}
	};
	int l = 0;
	int i = 0;
	while( squere_indexes[ind][i] >= 0 ){
		indexes[l][0] = squere_indexes[ind][i];
		indexes[l][1] = squere_indexes[ind][i+1];
		i+=2;++l;
	}
	
	*length = l;
	move_sequences =& sequences;
	lengths =& sequence_lengths;
}
void BoardPositions::getJumpSequencesForChecker(int ind , P_CH_SEQ & seq , int* length){
	static int jumps[32][4][2] = {
		 /*0*/{{4,9},{},{},{}} ,/*1*/{{4,8},{5,10},{},{}} ,/*2*/{{5,9},{6,11},{},{}} ,/*3*/{{6,10},{},{},{}} 
		,/*4*/{{9,13},{},{},{}} ,/*5*/{{9,12},{10,14},{},{}} ,/*6*/{{10,13},{11,15},{},{}} ,/*7*/{{11,14},{},{},{}} 
		,/*8*/{{12,17},{},{},{}} ,/*9*/{{4,0},{5,2},{12,16},{13,18}} ,/*10*/{{5,1},{6,3},{13,17},{14,19}} ,/*11*/{{6,2},{14,18},{},{}} 
		,/*12*/{{9,5},{17,21},{},{}} ,/*13*/{{9,4},{10,6},{17,20},{18,22}} ,/*14*/{{10,5},{11,7},{18,21},{19,23}} ,/*15*/{{11,6},{19,22},{},{}} 
		,/*16*/{{12,9},{20,25},{},{}} ,/*17*/{{12,8},{13,10},{20,24},{21,26}} ,/*18*/{{13,9},{14,11},{21,25},{22,27}} ,/*19*/{{14,10},{22,26},{},{}} 
		,/*20*/{{17,13},{25,29},{},{}} ,/*21*/{{17,12},{18,14},{25,28},{26,30}} ,/*22*/{{18,13},{19,15},{26,29},{27,31}} ,/*23*/{{19,14},{27,30},{},{}} 
		,/*24*/{{20,17},{},{},{}} ,/*25*/{{20,16},{21,18},{},{}} ,/*26*/{{21,17},{22,19},{},{}} ,/*27*/{{22,18},{},{},{}} 
		,/*28*/{{25,21},{},{},{}} ,/*29*/{{25,20},{26,22},{},{}} ,/*30*/{{26,21},{27,23},{},{}} ,/*31*/{{27,22},{},{},{}} 
			
	};
	static int lengths[32] = {1,2,2,1,1,2,2,1,1,4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,1,2,2,1,1,2,2,1};
	seq = &jumps[ind];
	*length  = lengths[ind];
}
bool BoardPositions::isInKingSequence(int index , Player player){
	static int king_sequence[2][4] = {
						//computer
						{0,1,2,3}
					       ,{28,29,30,31} 
					};
	int ind = getIndex(player);
	for(int i = 0 ; i<4 ; ++i){
		if(king_sequence[ind][i] == index ){
			return true;
		}
		return false;
	}
}
