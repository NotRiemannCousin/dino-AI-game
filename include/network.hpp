#include "matrix.hpp"
#include <vector>
#include <random>
#include <ctime>

using std::vector;
using std::string;
using std::time;

template<int x, int y, int z> // quant. de neurônios no input, nas intermediárias e no output
class network{
	//int &size_input, &size_inter, &size_output;

	static std::default_random_engine rand_gen;
	static std::uniform_real_distribution<float> dist;

	int layers_size;
	int fitness;

	matrix<x, 1> input;
	matrix<y, x> weights_input;

	vector<matrix<y, 1>> neurons;
	vector<matrix<y, y>> weights;

	matrix<z, y> weights_output;
	matrix<z, 1> output;

// 	void alternative_calc()
// 	{
// 		neurons[0] = weights_input * input;
// 		neurons[0].ReLu();

// 		fitness++;

// 		output = weights_output * neurons[0];
// 		output.boolean();
// 		output.print();
// 	} 
 	  public:
	// network() : layers_size(),
 	// input(), weights_input(), neurons(layers_size, matrix<y, 1>()),
 	// weights_output(), output(){}
 	network(int l_size) : layers_size(l_size),
 	input(), weights_input(), neurons(layers_size, matrix<y, 1>()),
 	weights_output(), output()
	{
		if(l_size != 1)
			weights = vector<matrix<y, y>>(max(layers_size - 1, 0));

		
		for(int i = 0; i < x; i++)
			for(int j = 0; j < y; j++)
				weights_input[j][i] = dist(rand_gen);

		
		weights.reserve(layers_size);
		for(int k = 0; k < layers_size; k++)
			weights.push_back(matrix<y, y>());
		for(int i = 0; i < y; i++)
		 	for(int j = 0; j < y; j++)
		 		for(int k = 0; k < layers_size; k++)
		 			weights.at(k)[j][i] = dist(rand_gen);


		for(int i = 0; i < z; i++)
			for(int j = 0; j < y; j++)
				weights_output[i][j] = dist(rand_gen);
	}

	void calc(matrix<x, 1> input_values)
	{
		input = input_values;

		if(layers_size == 1){
			//alternative_calc();
			return;
		}
		neurons[0] = weights_input * input;
		neurons[0].ReLu();

		for(int k = 1; k < layers_size; k++)
		{
			neurons[k] = weights[k-1] * neurons[k-1];
			neurons[k].ReLu();
		}
		fitness++;

		output = weights_output * neurons[layers_size - 1];
		output.boolean();

//		cout << "\t>> ";
//		output.print();
	}

	matrix<y, 1> getMatrixOutput()
	{
		return output;
	}
	array<float, z> getOutput()
	{
		return output.transpose()[0];
	}

	string print()
	{
		string str = weights_input.print();
		for(auto &p : weights)
			str.append(p.print());
		str.append(weights_output.print());
		return str;
	}

	int getFitness()
	{
		return fitness;
	}
};
template<int x, int y, int z>
std::default_random_engine network<x, y, z>::rand_gen(time(0));
template<int x, int y, int z>
std::uniform_real_distribution<float> network<x, y, z>::dist(-1000, 1000);