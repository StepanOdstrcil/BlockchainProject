#pragma once

#include "stdafx.h"
#include "Block.h"
#include "Transaction.h"


class Blockchain
{
private:
	BlockList _chain;
	TransactionList _currentTransactions;
	string _blockchainDirectoryName = "../blochchain_data";
	const int _numberOfZeros = 4;

	void MineWithHash(string prviousHash);
	list<string> GetFileNames(string path);
	wstring s2ws(const string& s);
	bool IsBlockValid(Block* b);

	//bool DirectoryExists(LPCTSTR szPath);
	//list<string> GetFileNames(string path);
public:
	Blockchain();
	~Blockchain();
	void Sync();
	void PrintBlockchain();
	void Mine();
};

