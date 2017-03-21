// Dylemat_Genetyczny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Prisoner.h"

int main()
{
	string a;
	Prisoner* x = new Prisoner();
	cout << x->getNumberOfMoves() << endl;
	bool* kromka =new bool[2];
	x->setFirstMoves(kromka);


	delete (x);
	cin >> a;
    return 0;
}

