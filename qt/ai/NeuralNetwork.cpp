#include "NeuralNetwork.hpp"
#include "../Players.hpp"
#include "../Figures.hpp"
#include "../Board.hpp"
#include "../BoardPositions.hpp"
#include "BoardSquareIterator.hpp"
#include <fstream>
#include <algorithm>
#include <iterator>
double NeuralNetwork::evaluate(Board* board , Player player){
	double board_values[32];
	Figures figures  = Figures::getFiguresOfPlayer(SecondPlayer);
	Figures op_figures = Figures::getFiguresOfPlayer(FirstPlayer);
	double  sum = 0.0;
	for(int i=0;i<32;i++){
		Figure f = board->get(i);
		if(f == figures.king){
			board_values[i] = king_value;
		}else if(f == figures.checker){
			board_values[i] = 1;
		}else if(f == op_figures.king){
			board_values[i] = (-1)*king_value;
		}else if(f == op_figures.checker){
			board_values[i] = -1;
		}else{
			board_values[i] = 0.0;
		}
		sum+=board_values[i];
		
	}
	vector<double> inputs;
	vector<double> outputs;
	for(vector<Layer>::iterator layer = layers.begin();layer!=layers.end();++layer){
		if(layer == layers.begin()){
			vector<Neuron>::iterator neuron = layer->begin();
			for(int i=3;i<=8;++i){
				BoardSquareIterator square(board_values,i);
				while(!square.isEnd()){
					vector<double> vec = square.getValues();
					double out = neuron->output(vec);
					outputs.push_back(out);
					square.next();
					++neuron;
				}
			}
		}else{
			inputs = outputs;
			outputs.clear();
		
			for(vector<Neuron>::iterator neuron = layer->begin(); neuron != layer->end();++neuron){
				double out;
				if(layer->size() == 1){
					out = neuron->output(inputs,sum);
				}else{ 
					out = neuron->output(inputs);
				}
				outputs.push_back(out);
			}
		}
	}
	//cout<<outputs.size()<<"---------------------"<<endl;
	double out = outputs.front();
	return player == SecondPlayer ? out : (-1)*out;
}
void NeuralNetwork::saveToFile(NeuralNetwork * n ,const char* name){
 	ofstream outfile(name);
	outfile<<n->getKing();
	vector<vector<Neuron> >& layers = n->getLayers();
	outfile<<" ";
	for(vector<vector<Neuron> >::iterator layer = layers.begin();layer!=layers.end();++layer){	
		for(vector<Neuron>::iterator neuron = layer->begin();neuron!=layer->end();++neuron){
			vector<double> weights = neuron->getWeights();
			outfile<<weights.size()<<"\n";
			copy(weights.begin(),weights.end(),ostream_iterator<double>(outfile," "));
			outfile<<"\n";
		}
	}
	outfile.close();	
}
void NeuralNetwork::loadFromFile(NeuralNetwork* n ,const char* name){
	ifstream infile(name);
	double king;
	infile>>king;
	n->setKing(king);
	vector<vector<Neuron> >& layers = n->getLayers();
	for(vector<vector<Neuron> >::iterator layer = layers.begin();layer!=layers.end();++layer){	
		for(vector<Neuron>::iterator neuron = layer->begin();neuron!=layer->end();++neuron){
			int size;
			infile>>size;
			vector<double> weights(size);
			for(int i=0;i<size;++i){
				double w;
				infile>>w;
				weights[i] = w;
			}
			neuron->setWeights(weights);
			//copy_n(istream_iterator<double>(infile),size,weights.begin());	
			//copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
			//cout<<endl<<size<<endl;
			//infile>>king;
			//cout<<king;
			//outfile<<"\n";
		}
	}
	infile.close();	
	
}
