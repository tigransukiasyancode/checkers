#ifndef NEURON_HPP
#define NEURON_HPP
#include <vector>
#include <math.h>
using std::vector;
class Neuron{
	public:
	vector<double> getWeights(){
		return weights;
	}
	void setWeights(const vector<double>& w){
		weights = w;
	}
	double output(const vector<double>& input , double input_without_weight = 0.0){
		double sum = 0;
		for(int i=0 ; i<input.size() ; ++i){
			sum+=weights[i]*input[i];
		}
		sum-=*weights.rend();
		sum+=input_without_weight;
		return sigmoid(sum);
	}
	virtual ~Neuron(){}
	private:
	double sigmoid(double x){
		double expo = 2.718281;
		return (pow(expo,2*x)-1)/(pow(expo,2*x)+1);  
	}
	vector<double> weights; 
};
#endif
