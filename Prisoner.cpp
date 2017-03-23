#include "stdafx.h"
#include "Prisoner.h"


bool * Prisoner::getStrategyOutput()
{
	return this->strategy_output;
}

bool Prisoner::getSpecificStrategyOutput(int index)
{
	return this->strategy_output[index%this->four_power];
}

bool * Prisoner::getFirstMoves()
{
	return this->first_moves;
}

bool Prisoner::getSpecificFirstMoves(int index)
{
	return this->first_moves[index%this->nr_of_moves];
}

int Prisoner::getPoints()
{
	return this->strategy_points + this->first_moves_points;
}

int Prisoner::getFirstMovesPoints()
{
	return this->first_moves_points;
}

int Prisoner::getStrategyPoints()
{
	return this->strategy_points;
}

int Prisoner::getNumberOfMoves()
{
	return this->nr_of_moves;
}

int Prisoner::getFourPower()
{
	return this->four_power;
}

void Prisoner::setStrategyOutput(bool * _array)
{
	delete(this->strategy_output);
	this->strategy_output = _array;
}

void Prisoner::setSpecificStrategyOutput(int index, bool value)
{
	this->strategy_output[index%four_power] = value;
}

void Prisoner::setFirstMoves(bool * _array)
{
	delete(this->first_moves);
	this->first_moves = _array;
}

void Prisoner::setSpecificFirstMoves(int index, bool value)
{
	this->first_moves[index%nr_of_moves] = value;
}

void Prisoner::setStrategyPoints(int value)
{
	this->strategy_points = value;
}

void Prisoner::setFirstMovesPoints(int value)
{
	this->first_moves_points = value;
}


void Prisoner::setNumberOfMoves(int number)
{
	this->nr_of_moves = number;
	// dont do it, plyz
	// plyz
	// stahp 
}

void Prisoner::setFourPower(int number)
{
	this->four_power = number;
}

void Prisoner::addFirstMovesPoints(int number)
{
	this->first_moves_points += number;
}

void Prisoner::addStrategyPoints(int number)
{
	this->strategy_points += number;
}


Prisoner::Prisoner()
{
	// kromka
}


Prisoner::Prisoner(int _nr_of_moves)
{
	this->strategy_points = 0;
	this->first_moves_points = 0;
	this->four_power = pow(4, _nr_of_moves);
	this->nr_of_moves = _nr_of_moves;
	this->first_moves = new bool[_nr_of_moves];
	for (int i = 0; i < _nr_of_moves; i++) {
		first_moves[i] = rand() % 2;
	}
	this->strategy_output = new bool[four_power];
	for (int i = 0; i < four_power; i++) {
		strategy_output[i] = rand() % 2;
	}
}

Prisoner::~Prisoner()
{
	delete first_moves;
	delete strategy_output;
}
