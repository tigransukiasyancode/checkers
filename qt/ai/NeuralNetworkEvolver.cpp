#include "NeuralNetwork.hpp"
#include "../Computer.hpp"
#include "../PossibleMoves.hpp"
#include "../Players.hpp"
#include "BoardSquareIterator.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <memory>
#include <set>
using namespace std;

typedef vector<vector<vector<double> > > Xetta;
typedef vector<vector<double> >  XettaLayer;
typedef vector<double>  XettaNeuron;
struct Individual;

double random_weight();
Individual  getChild(NeuralNetwork*,Xetta*);
void play(Individual& main_player,Individual& oponent);
template<typename T>
T prob(T val){
	return val*(rand()%2);
}

double exp_thetta(){
	double thetta = 0.0839;
	double expo = 2.718281;
	return pow(expo , prob(thetta));
}
struct Individual{
	shared_ptr<NeuralNetwork> neural;
	shared_ptr<Xetta> xetta;
	int score;
	Individual(NeuralNetwork* n , Xetta* x ):neural(n),xetta(x),score(0){}	
};
bool comp(const Individual& first ,const Individual & second){
	return first.score > second.score;
}
class WeightXettaIterator{
	vector<vector<Neuron> >& layers;
	vector<vector<Neuron > >::iterator layer;
	vector<Neuron>::iterator neuron;
	
	Xetta& xetta_net;
	Xetta::iterator xetta_layer;
	XettaLayer::iterator xetta_neuron;
	
	public:
	WeightXettaIterator(NeuralNetwork* network,Xetta* xetta ):
				 layers(network->getLayers())
				,layer(layers.begin())
				,neuron(layer->begin())
				,xetta_net(*xetta)
				,xetta_layer(xetta_net.begin())
				,xetta_neuron(xetta_layer->begin()){
	
	}
	vector<Neuron>::iterator getNeuron(){
		return neuron;
	}
	XettaLayer::iterator getXettaNeuron(){
		return xetta_neuron;
	}
	void next(){
		if(++neuron == layer->end()){
			if(++layer != layers.end()){
				neuron = layer->begin();
			}
		}
		if(++xetta_neuron == xetta_layer->end()){
			if(++xetta_layer != xetta_net.end()){
				xetta_neuron = xetta_layer->begin();	
			}
		}
	}
	bool isEnd(){
		return layer == layers.end();
	}
};
class WeightXettaValueIterator{
	WeightXettaIterator it;
	vector<double> weights;
	vector<double>::iterator weight;
	XettaNeuron::iterator xetta_weight;
	public:
	WeightXettaValueIterator(NeuralNetwork* network , Xetta* xetta)
		:it(network,xetta)
		,weights(it.getNeuron()->getWeights())
		,weight(weights.begin())
		,xetta_weight(it.getXettaNeuron()->begin()){
		
	}
	double getWeight(){
		return *weight;
	}
	double getXettaWeight(){
		return *xetta_weight;
	}
	void next(){
		if(++weight == weights.end()){
			it.next();
			if(!it.isEnd()){
				weights = it.getNeuron()->getWeights();
				weight = weights.begin();
				xetta_weight = it.getXettaNeuron()->begin();
			}
			return;
		}
		++xetta_weight;
	}
	bool isEnd(){
		return it.isEnd();
	}
};
void init_random(NeuralNetwork* network , vector<vector<vector<double> > >* xetta){
	srand(time(0));
	network->setKing(2.0);	
	double b[32];
	vector<vector<Neuron> >& layers = network->getLayers();
	vector<vector<Neuron> >::iterator layer = layers.begin();
	vector<Neuron>::iterator neuron = layer->begin();
	vector<vector <double > > xetta_layer;
	int count = 0;
	for(int i=3;i<=8;i++){
		BoardSquareIterator it(b,i);
		while(!it.isEnd()){
			vector<double> weights;
			int length = it.length()+1;
			vector<double> xetta_neuron(length,0.05);
			xetta_layer.push_back(xetta_neuron);
			while(length--){
				weights.push_back(random_weight());
				count++;
			}
			neuron->setWeights(weights);
			++neuron;
			it.next();
		}
	}
	xetta->push_back(xetta_layer);
	//vector<double> xetta_neuron(92,0.05);
	xetta->push_back( vector<vector<double> >(40,vector<double> (92,0.05)) );
	xetta->push_back( vector<vector<double> >(10,vector<double> (41,0.05)) );
	xetta->push_back( vector<vector<double> >(1,vector<double> (11,0.05)) );
	
	++layer;
	int lengths[] = {92,41,11};
	for(int i=0;layer!=layers.end();++layer,++i){
		for(vector<Neuron>::iterator neuron  = layer->begin(); neuron != layer->end();++neuron){
			vector<double> weights(lengths[i]);
			count+=lengths[i];
			generate(weights.begin(),weights.end(),random_weight);
			neuron->setWeights(weights);
		}
		
	}
	cout<<"count="<<count<<endl;
	
}

int main(){
	vector<Individual>population;
	for(int i=0;i<15;i++){
		NeuralNetwork* n = new NeuralNetwork();
		Xetta* x = new Xetta();
		init_random(n,x);
		population.push_back(Individual(n,x));
	}
	set<int> choosen;
	for(int population_count=0;population_count<5;population_count++){
		int size = population.size();
		for(int i=0;i<size;++i){
			population.push_back(getChild(population[i].neural.get(),population[i].xetta.get()));
		}
		for(int i=0;i<population.size();i++){
			choosen.clear();
			choosen.insert(i);
			for(int j =0 ;j<5;j++){
				int index;
				while( choosen.count(index = rand()%population.size()) ){
					//cout<<index<<endl;
				}
				choosen.insert(index);
				play(population[i],population[index]);
				cout<<"     "<<population[i].score<<endl;
			}
			cout<<population[i].score<<endl;
		}
		//cout<<"sss"<<endl;
		sort(population.begin() , population.end() , comp);
		for(vector<Individual>::iterator it = population.begin();it!=population.end();++it){
			cout<<it->score<<"  ";
			it->score = 0;
		}
		cout<<endl;
		population.erase(population.begin()+15,population.end());
		//cout<<"n"<<endl;
	}
	NeuralNetwork::saveToFile(population.front().neural.get(),"file.txt");
	cout<<"end";
	
}

double random_weight(){
	//srand(time(0));
	return  (20 - rand()%40)/100.0;
}

Individual getChild(NeuralNetwork* parent_neural , Xetta* parent_xetta){
	NeuralNetwork* child_neural = new NeuralNetwork(*parent_neural);
	Xetta* child_xetta = new Xetta(*parent_xetta);
	
	double king = parent_neural->getKing();
	double king_delta[] = {-0.1,0,0.1};
	bool isOk =false;
	while(!isOk){
		double del = king_delta[rand()%3];
		if((king + del) < 3.0 && (king + del) > 1.0){
			child_neural->setKing(king+del);
			isOk = true;
		}
	}
	WeightXettaIterator it(child_neural,child_xetta);
	while(!it.isEnd()){
		vector<Neuron>::iterator neuron = it.getNeuron();
		XettaLayer::iterator xetta_neuron = it.getXettaNeuron();
		vector<double> weights = neuron->getWeights();
		XettaNeuron::iterator xetta_weight = xetta_neuron->begin();
		for(vector<double>::iterator weight = weights.begin() ; weight != weights.end() ;++weight , ++xetta_weight ){
			*xetta_weight = (*xetta_weight) * exp_thetta();
			*weight = *weight + prob(*xetta_weight);  
		}
		neuron->setWeights(weights);
		it.next();
	}
	//cout<<"aaa"<<endl;
	return Individual(child_neural,child_xetta);
}
void play(Individual& main_player,Individual& oponent){
	Computer main(SecondPlayer,main_player.neural);
	Computer op(FirstPlayer,oponent.neural);
	Board board;
	board.init();
	list<Move> avalible;
	for(int i=0;i<100;i++){
		avalible.clear();
		PossibleMoves::getAll(&board , FirstPlayer ,&avalible );
		if(avalible.empty()){
			main_player.score+=1;
			break;
		}
		//cout<<"aaa"<<endl;
		Move m = op.getMove(board);
		board.perform(m);
		//cout<<"ccc"<<endl;
		avalible.clear();
		PossibleMoves::getAll(&board,SecondPlayer,&avalible);
		if(avalible.empty()){
			main_player.score-=2;
			break;
		}
		Move m1 = main.getMove(board);
		board.perform(m1);
		//cout<<"bbb"<<endl;

	}	
	
}
