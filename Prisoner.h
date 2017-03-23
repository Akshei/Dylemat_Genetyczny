#pragma once
using namespace std; 
class Prisoner
{
	bool *strategy_output;
	bool *first_moves;
	int strategy_points;
	int first_moves_points;
	int nr_of_moves;
	int four_power;
public:

	bool* getStrategyOutput();
	bool getSpecificStrategyOutput(int index);
	bool* getFirstMoves();
	bool getSpecificFirstMoves(int index); 
	int getPoints();
	int getFirstMovesPoints();
	int getStrategyPoints();
	int getNumberOfMoves();
	int getFourPower();
	
	void setStrategyOutput(bool* _array);
	void setSpecificStrategyOutput(int index, bool value);
	void setFirstMoves(bool* _array);
	void setSpecificFirstMoves(int index, bool value);
	void setStrategyPoints(int value);
	void setFirstMovesPoints(int value);
	void setNumberOfMoves(int number);
	void setFourPower(int number);

	void addFirstMovesPoints(int number);
	void addStrategyPoints(int number);

	Prisoner(int _nr_of_moves);
	Prisoner();
	~Prisoner();
};

