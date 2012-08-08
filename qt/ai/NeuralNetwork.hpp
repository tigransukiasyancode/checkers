#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP
#include <vector>
#include "../Board.hpp"
#include "../Players.hpp"
#include "Neuron.hpp"
using namespace std;
class NeuralNetwork{
	double king_value;
	typedef vector<Neuron> Layer;
	
	vector<Layer> layers;

	public:
	NeuralNetwork(double king = 0.0):king_value(king){
		vector<Neuron> vec1(91);
		vector<Neuron> vec2(40);
		vector<Neuron> vec3(10);
		vector<Neuron> vec4(1);
		layers.push_back(vec1);
		layers.push_back(vec2);
		layers.push_back(vec3);
		layers.push_back(vec4);
	}
	double getKing() const{
		return king_value;
	}
	void setKing(double king){
		king_value = king;
	}
	double evaluate(Board* board , Player player);
	vector<vector<Neuron> >& getLayers(){
		return layers;
	}
	static void saveToFile(NeuralNetwork * n , const char*);
	static void loadFromFile(NeuralNetwork* n ,const char* );
};
#endif
