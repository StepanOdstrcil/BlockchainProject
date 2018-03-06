#pragma once

#include "Transaction.h"

// Predefinitions
class Block;

typedef list<Block> BlockList;

class Block
{
private:
	int _index;
	time_t _timeStamp;
	string _previousHash;
	string _hash;
	TransactionList _transactions;
	int _nonce;
public:
	Block(int index, string previousHash, TransactionList transactions, int nonce);
	Block(string fileName);
	~Block();
	int GetIndex();
	string GetHash();
	bool Save(string directory, int number);
	string ToString();
};

