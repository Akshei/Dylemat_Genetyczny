#include "stdafx.h"
#include "Prisoner.h"
using namespace std;
#pragma once
class God
{
	// 0 to zdrada, 1 to wspó³praca
	vector <Prisoner*> actual_population;
	vector <Prisoner*> crossing_population;
	int population_size;
	int nr_generation;
	int genetic_algorithm_type;
	int limit;
	int move_count; // Ilosc ruchow przez wiezniow uwzglednianych
	int saved_prisoner_count; // Ile wiezniow wybieramy przy selekcji DO WYWALENIA
	int mutation_count;
	int strategy_moves_count;
	string species_name;

	void mutation();
	void selection();
	void crossing();
	void playDillemaOnPrisoners();
	void battle(int first, int second);
	void givePlayerPointsForFirstMoves(int first_player_index, int second_player_index, int first_player_choice, int second_player_choice);
	void givePlayerPointsForStrategies(int first_player_index, int second_player_index, int first_player_choice, int second_player_choice);
	
	void chooseEverything();

	string boolToStr(bool b);
	void saveGeneration();
	void oneCycleEvolution();
	void debugDisplay();

	void runTimeLimit();
	void runGenerationLimit();
public:
	void run();

	vector<Prisoner*> getActualPopulation();
	int getNumberGeneration();
	int getPopulationSize();
	int getGeneticAlgorithmType();
	int getLimit();
	int getMoveCount();
	int getSavedPrisonerCount();
	int getMutationCount();
	int getStrategyMovesCount();

	void setActualPopulation(vector<Prisoner*> x);
	void setPopulationSize(int size);
	void setNumberGeneration(int number);
	void setGeneticAlgorithmType(int type);
	void setLimit(int limit);
	void setMoveCount(int count);
	void setSavedPrisonerCount(int count); 
	void setMutationCount(int count);
	void setStrategyMovesCount(int count);


public:
	God();
	God(int _population_size,
		int _genetic_algorithm_type,
		int _move_count,
		int _mutation_count,
		int _strategic_move_count,
		int _limit,
		string _species_name);
	~God();
};

