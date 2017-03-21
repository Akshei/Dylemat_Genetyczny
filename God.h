#include "stdafx.h"
#include "Prisoner.h"
using namespace std;
#pragma once
class God
{
	vector <Prisoner> actual_population;
	vector <Prisoner> crossing_population;
	int population_size;
	int nr_generation;
	int genetic_algorithm_type;
	int limit;
	int move_count; // Ilosc ruchow przez wiezniow uwzglednianych
	int saved_prisoner_count; // Ile wiezniow wybieramy przy selekcji
	int mutation_count;
	int strategy_moves_count;

	void mutation();
	void selection();
	void crossing();
	void playDillemaOnPrisoners();
	void battle(int first, int second);
	void givePlayerPointsForFirstMoves(int first_player_index, int second_player_index, int first_player_choice, int second_player_choice);
	void givePlayerPointsForStrategies(int first_player_index, int second_player_index, int first_player_choice, int second_player_choice);
	void runTimeLimit();
	void runGenerationLimit();
	void runScoreLimit();
	void chooseGeneticAlgorithm();
	void catchNiggersOnStreet();

	string boolToStr(bool b);

public:
	bool loadGeneration(string file_name);
	bool saveGeneration(string file_name);

	void run();

	vector<Prisoner> getActualPopulation();
	int getNumberGeneration();
	int getPopulationSize();
	int getGeneticAlgorithmType();
	int getLimit();
	int getMoveCount();
	int getSavedPrisonerCount();
	int getMutationCount();
	int getStrategyMovesCount();

	void setActualPopulation(vector<Prisoner> x);
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
	~God();
};

