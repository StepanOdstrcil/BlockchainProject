// BlockchainProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Blockchain.h"

#include <iostream>


int main()
{
	Blockchain blockchain = Blockchain();

	blockchain.PrintBlockchain();

	blockchain.Mine();

	cout << endl << endl;

	blockchain.PrintBlockchain();

	// END
	getchar();
    return 0;
}

