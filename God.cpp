#include "stdafx.h"
#include "God.h"

// 0 to zdrada, 1 to wspó³praca

void God::mutation()
{
	cout << " mutation" << endl;
	if (mutation_count > 0) {
		int mut_cnt;
		int random;
		for (int i = 0; i < population_size; i++) {
			mut_cnt = rand() % mutation_count;
			for (int j = 0; j < mut_cnt; j++) {
				random = rand();
				actual_population[i]->setSpecificStrategyOutput(random, !actual_population[i]->getSpecificStrategyOutput(random));
			}
			mut_cnt = sqrt(mut_cnt);
			for (int j = 0; j < mut_cnt; j++) {
				random = rand();
				actual_population[i]->setSpecificFirstMoves(random, !actual_population[i]->getSpecificFirstMoves(random));
			}
		}
	}
}

void God::selection()
{
	cout << "selection" << endl;
	for (int i = 0; i < crossing_population.size(); i++) {
		delete (crossing_population[i]);
	}
	crossing_population.clear();
	int totalPoints;
	int random;
	for (int i = 0; i < ceil(sqrt(population_size)); i++) {
		totalPoints = 0;
		for (int j = 0; j < actual_population.size(); j++) {
			totalPoints += actual_population[j]->getPoints();
		}
		random = rand() % totalPoints;
		int k = 0;
		while (random >= 0) {
			random -= actual_population[k]->getPoints();
			k++;
		}
		cout << " Przed crossing population push back" << endl;
		cout << "A to jest k : " << k << endl;
		cout << "actual population size: " << actual_population.size() << endl;
		crossing_population.push_back(actual_population[k - 1]);
		cout << "actual population erase" << endl;
		actual_population.erase(actual_population.begin() + (k - 1));
	}
		
}

void God::crossing()
{
	cout << "crossing" << endl;
	for (int i = 0; i < actual_population.size(); i++) {
		delete(actual_population[i]);
	}
	actual_population.clear();
	int crossing_size = crossing_population.size();
	int four_power = pow(4, move_count);
	bool parent_choice;
	for (int i = 0; i < crossing_size && actual_population.size() < population_size; i++) {
		for (int j = 0; j < crossing_size  && actual_population.size() < population_size; j++) {
			Prisoner*  x = new Prisoner(move_count);
			for (int k = 0; k < move_count; k++) {
				if (rand() % 2 == 0) parent_choice = crossing_population[i]->getSpecificFirstMoves(k);
				else parent_choice = crossing_population[j]->getSpecificFirstMoves(k);
				x->setSpecificFirstMoves(k, parent_choice);
			}
			for (int k = 0; k < four_power; k++) {
				if (rand() % 2 == 0) parent_choice = crossing_population[i]->getSpecificStrategyOutput(k);
				else parent_choice = crossing_population[j]->getSpecificStrategyOutput(k);
				x->setSpecificStrategyOutput(k, parent_choice);
			}
			actual_population.push_back(x);
		}
	}
}

void God::playDillemaOnPrisoners()
{
	cout << "playDilemmaOnPrisoners" << endl;
	for (int i = 0; i < actual_population.size(); i++) {
		for (int j = i + 1; j < actual_population.size(); j++) {
			battle(i, j);
		}
	}
}

void God::battle(int first, int second)
{
	string gracz1 = "";
	string gracz2 = "";
	for (int i = 0; i < move_count; i++) {
		gracz1 += boolToStr(actual_population[first]->getSpecificFirstMoves(i));
		gracz2 += boolToStr(actual_population[second]->getSpecificFirstMoves(i));
		givePlayerPointsForFirstMoves(first, second,
			actual_population[first]->getSpecificFirstMoves(i),
			actual_population[second]->getSpecificFirstMoves(i));
	}
	int move1;
	int move2;
	for (int i = 0; i < strategy_moves_count; i++) {
		move1 = 0;
		move2 = 0;
		for (int j = 0; j < 2 * move_count; j++) {
			if (j % 2 == 0) {
				if (gracz1[j / 2] == '1') move1 += pow(2,j);
				if (gracz2[j / 2] == '1') move2 += pow(2, j);
			}
			else {
				if (gracz1[j / 2] == '1') move2 += pow(2, j);
				if (gracz2[j / 2] == '1') move1 += pow(2, j);
			}
		}
		givePlayerPointsForStrategies(first, second,
			actual_population[first]->getSpecificStrategyOutput(move1),
			actual_population[second]->getSpecificStrategyOutput(move2));
		gracz1 += boolToStr(actual_population[first]->getSpecificStrategyOutput(move1));
		gracz2 += boolToStr(actual_population[second]->getSpecificStrategyOutput(move2));
		gracz1.erase(gracz1.begin());
		gracz2.erase(gracz2.begin());
	}

}

void God::givePlayerPointsForFirstMoves(int first_player_index, int second_player_index, int first_player_choice, int  second_player_choice)
{
	// 0 to zdrada, 1 to wspó³praca
	if (first_player_choice == 0 && second_player_choice == 0) {
		actual_population[first_player_index]->addFirstMovesPoints(1);
		actual_population[second_player_index]->addFirstMovesPoints(1);
	}
	else if (first_player_choice == 0 && second_player_choice == 1) {
		actual_population[first_player_index]->addFirstMovesPoints(5);
		actual_population[second_player_index]->addFirstMovesPoints(0);
	}
	else if (first_player_choice == 1 && second_player_choice == 0) {
		actual_population[first_player_index]->addFirstMovesPoints(0);
		actual_population[second_player_index]->addFirstMovesPoints(5);
	}
	else if (first_player_choice == 1 && second_player_choice == 1) {
		actual_population[first_player_index]->addFirstMovesPoints(3);
		actual_population[second_player_index]->addFirstMovesPoints(3);
	}
}

void God::givePlayerPointsForStrategies(int first_player_index, int second_player_index, int first_player_choice, int second_player_choice)
{
	// 0 to zdrada, 1 to wspó³praca
	if (first_player_choice == 0 && second_player_choice == 0) {
		actual_population[first_player_index]->addStrategyPoints(1);
		actual_population[second_player_index]->addStrategyPoints(1);
	}
	else if (first_player_choice == 0 && second_player_choice == 1) {
		actual_population[first_player_index]->addStrategyPoints(5);
		actual_population[second_player_index]->addStrategyPoints(0);
	}
	else if (first_player_choice == 1 && second_player_choice == 0) {
		actual_population[first_player_index]->addStrategyPoints(0);
		actual_population[second_player_index]->addStrategyPoints(5);
	}
	else if (first_player_choice == 1 && second_player_choice == 1) {
		actual_population[first_player_index]->addStrategyPoints(3);
		actual_population[second_player_index]->addStrategyPoints(3);
	}
}

void God::oneCycleEvolution() // makes one cycle of evolution
{
	playDillemaOnPrisoners();
	selection();
	crossing();
	mutation();
}

void God::runTimeLimit()
{
	saveGeneration();
	time_t start = time(0);
	time_t save_delay;
	while (difftime(time(0), start) <= limit) {
		this->nr_generation++;
		oneCycleEvolution();
		saveGeneration();
		save_delay = time(0);
		debugDisplay();
		start -= difftime(time(0), save_delay);
	}
}

void God::runGenerationLimit()
{
	saveGeneration();
	while (this->nr_generation++ < limit) {
		oneCycleEvolution();
		saveGeneration();
		debugDisplay();
	}
}

void God::run()
{
	if (population_size < 2 ) {
		chooseEverything();
	}
	switch (genetic_algorithm_type)
	{
	case 0: runGenerationLimit();
		break;

	case 1: runTimeLimit();
		break;
	default:
		cout << "Zle wybrany typ algroytmu" << endl;
		break;
	}
}


void God::chooseEverything()
{
	cout << "Nazwij proszê swoj gatunek." << endl;
	cin >> species_name;

	cout << "Podaj wielkosc populacji (liczba calkowita):" << endl;
	cin >> population_size;

	cout << "Podaj ograniczenie algorymtu" << endl;
	cout << "0 dla ograniczenia liczby generacji" << endl;
	cout << "1 dla ograniczenia czasowego ( w ramach ograniczenia czasowego nei zawiera siê zapisywanie do pliku)" << endl;
	cin >> genetic_algorithm_type;

	cout << " Podaj limit ograniczenia. Dla ograniczenia czasowego jest on liczony w sekundach" << endl;
	cin >> limit;

	cout << "Podaj ilosc ruchow uwzglednianych przez wiezniow" << endl;
	cin >> move_count;

	cout << "Podaj maksymalna ilosc mutacji" << endl;
	cin >> mutation_count;

	cout << "Podaj ile kolejnych ruchow na podstawie strategii ma wliczaæ siê do punktacji" << endl;
	cin >> strategy_moves_count;

	for (int i = 0; i < population_size; i++) {
		actual_population.push_back(new Prisoner(move_count));
	}
}


string God::boolToStr(bool b)
{
	if (b == true) {
		return "1";
	}
	else {
		return "0";
	}
}


void God::saveGeneration()
{
	fstream file;
	string name = "";
	name = species_name + "_generation_" + to_string(nr_generation) + ".csv";
	file.open(name, ios::out);
	file << "Nazwa gatunku:," << species_name << endl;
	file << "Generacja:," << to_string(nr_generation) << endl;
	file << "Wielkoœæ populacji:," + to_string(population_size) << endl;
	file << "Generacja:," << to_string(nr_generation) << endl;
	file << "Maksymalna iloœæ mutacji:," << to_string(mutation_count) << endl;
	file << "Iloœæ uwzglêdnianych ruchów:," << to_string(move_count) << endl;
	for (int i = 0; i < actual_population.size(); i++) {
		file << endl;
		file << "Nr wiêŸnia w aktualnej populacji:," << to_string(i) << endl;
	
		file << "Pierwsze ruchy,";
		for (int j = 0; j < move_count; j++) {
			file << to_string(j + 1) << ",";
		}
		file << endl;
		file << "Ruchy:,";
		for (int j = 0; j < move_count; j++) {
			if (actual_population[i]->getSpecificFirstMoves(j) == 0) {
				file << "Zdrada,";
			}
			else {
				file << "Wspó³praca,";
			}
		}
		file << endl;

		file << "Strategie,";
		for (int j = 0; j < pow(4, move_count); j++) {
			unsigned int str = j;
			string strat = "";
			for (int k = 0; k < 2 * move_count; k++) {
				if (str % 2 == 0) { strat += 'Z'; }
				else { strat += 'W'; };
				str = str >> 1;
			}
			file << strat << ",";
		}
		file << endl;
		file << ",";
		for (int j = 0; j < pow(4,move_count); j++) {
			if (actual_population[i]->getSpecificStrategyOutput(j) == 0) {
				file << "Zdrada,";
			}
			else {
				file << "Wspó³praca,";
			}
		}
		file << endl;
	}
	int kromka = 0;
	file << endl << endl;
	file << "Statystyka" << endl;
	file << "Pierwsze ruchy,";
	for (int j = 0; j < move_count; j++) {
		file << to_string(j + 1) << ",";
	}
	file << endl;
	
	file << "Wspó³praca: ,";
	for (int i = 0; i < move_count; i++) {
		for (int j = 0; j < actual_population.size(); j++) {
			if (actual_population[j]->getSpecificFirstMoves(i) == 1) kromka++;
		}
		file <<to_string(kromka) +  ",";
		kromka = 0;
	}
	file << endl;
	kromka = 0;
	file << "Zdrada: ,";
	for (int i = 0; i < move_count; i++) {
		for (int j = 0; j < actual_population.size(); j++) {
			if (actual_population[j]->getSpecificFirstMoves(i) == 0) kromka++;
		}
		file << to_string(kromka) + ",";
		kromka = 0;
	}
	file << endl;

	kromka = 0;

	file << endl << endl;
	file << "Strategie,";
	for (int j = 0; j < pow(4, move_count); j++) {
		unsigned int str = j;
		string strat = "";
		for (int k = 0; k < 2 * move_count; k++) {
			if (str % 2 == 0) { strat += 'Z'; }
			else { strat += 'W'; };
			str = str >> 1;
		}
		file << strat << ",";
	}
	file << endl;

	file << "Wspó³praca: ,";
	for (int i = 0; i < pow(4,move_count); i++) {
		for (int j = 0; j < actual_population.size(); j++) {
			if (actual_population[j]->getSpecificStrategyOutput(i) == 1) kromka++;
		}
		file << to_string(kromka) + ",";
		kromka = 0;
	}
	file << endl;
	kromka = 0;
	file << "Zdrada: ,";
	for (int i = 0; i < pow(4, move_count); i++) {
		for (int j = 0; j < actual_population.size(); j++) {
			if (actual_population[j]->getSpecificStrategyOutput(i) == 0) kromka++;
		}
		file << to_string(kromka) + ",";
		kromka = 0;
	}
	file << endl;

	file.close();

}

void God::debugDisplay()
{
	cout << endl << endl <<"____________________________________________\n";
	cout << " Numer generacji: " << nr_generation << endl;
	/*for (int i = 0; i < crossing_population.size(); i++) {
		cout << " NR wieznia: " << i << endl;
		for (int j = 0; j < crossing_population[i]->getFourPower(); j++) {
			cout << " Strategia dla ruchu : " << j << " jest taka: " << crossing_population[i]->getSpecificStrategyOutput(j) << endl;
		}
		for (int j = 0; j < crossing_population[i]->getNumberOfMoves(); j++) {
			cout << " Pierwszy ruch  dla ruchu : " << j << " jest taka: " << crossing_population[i]->getSpecificFirstMoves(j) << endl;
		}
		cout << crossing_population[i]->getPoints() << endl;
	}
	for (int i = 0; i < 1; i++) {
		cout << " NR wieznia: " << i << endl;
		for (int j = 0; j < actual_population[i]->getFourPower(); j++) {
			cout << " Strategia dla ruchu : " << j << " jest taka: " << actual_population[i]->getSpecificStrategyOutput(j) << endl;
		}
		for (int j = 0; j < actual_population[i]->getNumberOfMoves(); j++) {
			cout << " Pierwszy ruch  dla ruchu : " << j << " jest taka: " << actual_population[i]->getSpecificFirstMoves(j) << endl;
		}
		cout << actual_population[i]->getPoints() << endl;
	}*/
}



vector<Prisoner*> God::getActualPopulation()
{
	return this->actual_population;
}

int God::getNumberGeneration()
{
	return this->nr_generation;
}

int God::getPopulationSize()
{
	return this->population_size;
}

int God::getGeneticAlgorithmType()
{
	return this->genetic_algorithm_type;
}

int God::getLimit()
{
	return this->limit;
}

int God::getMoveCount()
{
	return this->move_count;
}

int God::getSavedPrisonerCount()
{
	return this->saved_prisoner_count;
}

int God::getMutationCount()
{
	return this->mutation_count;
}

int God::getStrategyMovesCount()
{
	return this->strategy_moves_count;
}

void God::setActualPopulation(vector<Prisoner*> x)
{
	actual_population.clear();
	this->actual_population = x;
}

void God::setPopulationSize(int size)
{
	this->population_size = size;
}

void God::setNumberGeneration(int number)
{
	this->nr_generation = number;
}

void God::setGeneticAlgorithmType(int type)
{
	this->genetic_algorithm_type = type;
}

void God::setLimit(int limit)
{
	this->limit = limit;
}

void God::setMoveCount(int count)
{
	this->move_count = count;
}

void God::setSavedPrisonerCount(int count)
{
	this->saved_prisoner_count = count;
}

void God::setMutationCount(int count)
{
	this->mutation_count = count;
}

void God::setStrategyMovesCount(int count)
{
	this->strategy_moves_count = count;
}


God::God()
{
	actual_population.clear();
	crossing_population.clear();
	this->population_size = 0;
	this->nr_generation = 0;
	this->genetic_algorithm_type = 0;
	this->limit = 0;
	this -> move_count = 0;
	this->saved_prisoner_count = 0;
	this->mutation_count = 0;
	this->strategy_moves_count = 0;
	species_name = "kromka";
}

God::God(int _population_size,
	int _genetic_algorithm_type,
	int _move_count,
	int _mutation_count,
	int _strategic_move_count,
	int _limit,
	string _species_name) {
	actual_population.clear();
	crossing_population.clear();
	this->population_size = _population_size;
	this->nr_generation = 0;
	this->genetic_algorithm_type = _genetic_algorithm_type;
	this->limit = _limit;
	this->move_count = _move_count;
	this->saved_prisoner_count = 0;
	this->mutation_count = _mutation_count;
	this->strategy_moves_count = _strategic_move_count;
	for (int i = 0; i < population_size; i++) {
		actual_population.push_back(new Prisoner(move_count));
	}
	this->species_name = _species_name;
}


God::~God()
{
	for (int i = 0; i < actual_population.size(); i++) {
		delete (actual_population[i]);
	}
	for (int i = 0; i < crossing_population.size(); i++) {
		delete (crossing_population[i]);
	}
	actual_population.clear();
	crossing_population.clear();
}