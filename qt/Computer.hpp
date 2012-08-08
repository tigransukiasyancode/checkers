#ifndef COMPUTER_HPP
#define COMPUTER_HPP
#include "StaticEvaluator.hpp"
#include "Board.hpp"
#include "types.hpp"
#include "Move.hpp"
#include <memory>
#include "ai/NeuralNetwork.hpp"
class Computer{
	public:
	Computer(Player max , std::shared_ptr<NeuralNetwork> neural_net ,  Depth depth = 3):max_player(max)
									,max_depth(depth)
									,neural_network(neural_net){}
	Computer(Player max , Depth depth = 3):max_player(max)
					,max_depth(depth)
					,neural_network(new NeuralNetwork()){
		NeuralNetwork::loadFromFile(neural_network.get(),"file.txt");
	}
	Move getMove(Board );
	
	private:
	Player max_player;
	Depth max_depth;
	std::shared_ptr<NeuralNetwork> neural_network;
	//typedef StaticEvaluator Evaluator;
	BoardValue min_max(Board* , BoardValue alpha , BoardValue betta , Player , Depth);
};
#endif

