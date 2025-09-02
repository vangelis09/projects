
/*
Брутфорс
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <tuple>
#include <fstream>


#define UNIT vector<char>

using namespace std;

int MAX_LENGTH = 1;
double TOURNAMENT_SIZE = 0.5;
int POPULATION_SIZE = 500;
double MUTATION_RATE = 0.4;
int word_length;

UNIT random_unit(const int& length)
{
	UNIT tmp_pwd;
	for (size_t i = 0; i < length; i++)
	{
		tmp_pwd.push_back(char(rand() % 94 + 32));
	}
	return tmp_pwd;
}

char random_last_char()
{
	char a = rand() % 94 + 32;
	return a;
}

UNIT get_password()
{
	ifstream fin("source.txt");
	UNIT pwd;
	if (!fin.is_open())
	{
		return {};
	}
	char c;
	while(fin >> c)
	{
		pwd.push_back(c);
	}
	return pwd;
}
UNIT target = get_password();
vector<UNIT> initialize_population(const UNIT& bs, const int& length)
{
	vector<UNIT> population;
	if (!bs.empty()) population.push_back(bs);
	UNIT tmp_pwd;

	for (size_t j = 1; j < POPULATION_SIZE; j++)
	{
		tmp_pwd = random_unit(length);
		population.push_back(tmp_pwd);
		tmp_pwd.clear();
	}
	
	return population;

}
void mutate(UNIT& pwd, const bool& flag)
{	
	for (auto i : pwd)
	{
		int p = rand() % 10;
		if (p / 10 <= MUTATION_RATE)
		{
			i = rand() % 94 + 32;
		}
		
	}
	if (flag)
	{
		pwd.back() = random_last_char();
	}
	return;

}
UNIT crossover(const UNIT& p1, const UNIT& p2, const int& length)
{
	UNIT child;
	for (size_t i = 0; i < length; i++)
	{
		int p = rand() % 2;
		if (p == 0)
		{
			child.push_back(p1[i]);
		}
		else
		{
			child.push_back(p2[i]);
		}
	}
	return child;
}
pair<UNIT, UNIT> roulette_selection(const vector<UNIT>& population)
{
	int index1 = 0, index2 = 0;
	int pool = POPULATION_SIZE - 1;
	int rotate_count = rand() % 5;
	
	int pr = rand() % pool;
	for (size_t i = 0; i < rotate_count; i++)
	{
		int rotation = rand() % 6;
		index2 = pr + rotation;
		if (index2 > 30) index2 -= 30;
	}
	//cout << index1 << '\t' << index2 << endl;
	pair<UNIT,UNIT> parents = {population[index1], population[index2]};
	return parents;
}

int fitness(const UNIT& unit)
{
	if (unit == target) return unit.size();
	else
	{
		int fitness = 0;
		for (size_t i = 0; i < unit.size(); i++)
		{
			if (unit[i] == target[i]) fitness++;
		}
		return fitness;
	}
}

bool sort_unit(const UNIT& a, const UNIT& b)
{
	return fitness(a) > fitness(b);
}

void fit_population(vector<UNIT>& population, vector<int>& fitnesses, const int& length)
{
	fitnesses.clear();
	sort(population.begin(), population.end(), sort_unit);

	bool norm = false;
	while (norm == false && population.size() != POPULATION_SIZE)
	{
		if (population.size() > POPULATION_SIZE || fitness(population.back()) == 0)
		{
			population.pop_back();
		}
		if (population.size() < POPULATION_SIZE)
		{
			population.push_back(random_unit(length));
		}
		if (population.size() == POPULATION_SIZE && fitness(population.back()) > 0) norm = true;

	}
	//population.erase(remove(population.begin(), population.end(), 0), population.end());
	

	for (auto i: population)
	{
		fitnesses.push_back(fitness(i));
	}
	return;
}
void print_unit(const UNIT& pwd)
{
	for (auto j : pwd)
	{
		cout << j << ' ';
	}
	cout << endl;
}
void print_population(const vector<UNIT>& population, vector<int>& fitnesses, int num = 0)
{

	if (fitnesses.empty())
	{
		for (size_t i = 0; i < population.size(); i++)
		{
			fitnesses.push_back(-1);
		}
	}

	cout << "Population №" << num << ": " << endl;
	for (size_t i = 0; i < population.size(); i++)
	{
		for (auto j : population[i])
		{
			cout << j << ' ';
		}
		cout << "\tFitness = " << fitnesses[i] << "; " << endl;

	}
	cout << "_______________" << endl;

	return;
}

pair<UNIT, int> generic_algorithm(const UNIT& bs, const int& bf = 0, const int& length = 1)
{
	
	UNIT best_solution;
	
	if (bs.empty()) {
		
		for (int i = 0; i < length; i++)
		{
			best_solution.push_back('0');
		}
	}
	else best_solution = bs;
	vector<UNIT> population = initialize_population(best_solution, length);

	int best_fitness;
	int count_generations = 0;
	vector<int> fitnesses;
	int prev_bf = bf;
	int bf_staying_count = 0;
	bool fit_growing_stopped = false;
	while (1)
	{
		count_generations++;
		vector<int> fitnesses;
		for (int i = 0; i < POPULATION_SIZE/2; i++)
		{
			pair<UNIT, UNIT> parents = roulette_selection(population);
			UNIT child = crossover(parents.first, parents.second, length);
			mutate(child, fit_growing_stopped);
			population.push_back(child);
		}
		

		fit_population(population, fitnesses, length);
		print_population(population, fitnesses);
		best_solution = population.at(0);
		best_fitness = fitnesses.at(0);
		
		if (best_fitness == prev_bf)
		{
			bf_staying_count++;
		}
		else
		{
			bf_staying_count = 0;
			fit_growing_stopped = false;
		}
		if (bf_staying_count > 5)
		{
			fit_growing_stopped = true;
		}

		system("cls");
		cout << "Generation №: " << count_generations << " Best solution: ";
		print_unit(best_solution);
		cout << " fitness = " << best_fitness << endl;
		if (best_solution == target || best_fitness == length) break;
	}
	pair<UNIT, int> result = { best_solution, best_fitness };
	return result;
}
int main()
{
	setlocale(LC_ALL, "rus");
	
	UNIT answer;
	word_length = MAX_LENGTH;
	int best_fitness = 0;
	pair<UNIT, int> result;
	auto start = std::chrono::high_resolution_clock::now();
	while (answer != target)
	{
		result = generic_algorithm(answer, best_fitness, word_length);
		answer = result.first;
		if (result.second == word_length && answer != target)
		{
			word_length++;
			answer = result.first;
			answer.push_back('a');
			best_fitness = result.second;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	system("cls");
	cout << "Final solution: ";
	print_unit(result.first);
	cout << "Fitness: " << result.second << endl;
	cout << "Time: " << duration.count() << endl;
	

	return 0;
}
