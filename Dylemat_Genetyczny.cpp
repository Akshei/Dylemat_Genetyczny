// Dylemat_Genetyczny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Prisoner.h"
#include "God.h"
int main()
{
	srand(time(NULL));
	string a;
	God* x = new God(10, 1, 4, 2, 16,10000);
	x->runGenerationLimit();
	delete(x);
	cin >> a;
    return 0;
}

