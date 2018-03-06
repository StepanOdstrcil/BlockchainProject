#include "stdafx.h"
#include "Block.h"
#include "picosha2.h"

#include <chrono>
#include <fstream>
#include <vector>


Block::Block(int index, string previousHash, TransactionList transactions, int nonce) :
	_index(index), _previousHash(previousHash), _transactions(transactions),
	_timeStamp(chrono::system_clock::to_time_t(chrono::system_clock::now())), _nonce(nonce)
{
	this->_hash = picosha2::hash256_hex_string(this->ToString());
}

Block::Block(string fileName)
{
	string line;
	ifstream file(fileName);
	
	if (file.is_open())
	{
		getline(file, line);
		this->_index = stoi(line);

		getline(file, line);
		this->_timeStamp = stoi(line);

		getline(file, line);
		this->_previousHash = line;

		getline(file, line);
		this->_hash = line;

		// TODO: Maybe delete?
		getline(file, line);
		this->_nonce = stoi(line);

		this->_transactions = TransactionList();
		while (getline(file, line))
		{
			int start = 0;
			int end = line.find(';');
			string sender = line.substr(start, end);

			start = end + 1;
			end = line.rfind(';');
			string recipient = line.substr(start, end);

			int amount = stoi(line.substr(end + 1));

			this->_transactions.push_back(Transaction(sender, recipient, amount));
		}

		// Close the file
		file.close();
	}
}

Block::~Block()
{
}

int Block::GetIndex()
{
	return this->_index;
}

string Block::GetHash()
{
	return this->_hash;
}

bool Block::Save(string directory, int number)
{
	ofstream blockFile(directory + "/block_" + to_string(number) + ".txt");

	if (blockFile.is_open())
	{
		blockFile << to_string(this->_index) + "\n";
		blockFile << to_string(this->_timeStamp) + "\n";
		blockFile << this->_previousHash + "\n";
		blockFile << this->_hash + "\n";
		blockFile << to_string(this->_nonce) + "\n"; // TODO: Maybe delete?
		// All transactions
		for (TransactionList::iterator it = this->_transactions.begin(); it != this->_transactions.end(); it++)
		{
			blockFile <<  it->ToFileString();
		}
		
		blockFile.close();
	}
	else
	{
		return false;
	}
	return true;
}

string Block::ToString()
{
	string blockString = "{\n";

	blockString += "\tindex:" + to_string(this->_index) + "\n";
	blockString += "\ttime stamp:" + to_string(this->_timeStamp) + "\n";
	blockString += "\tprevious hash:" + this->_previousHash + "\n";
	blockString += "\thash:" + this->_hash + "\n";
	blockString += "\tnonce:" + to_string(this->_nonce) + "\n";
	for (TransactionList::iterator it = this->_transactions.begin(); it != this->_transactions.end(); it++)
	{
		blockString += it->ToString();
	}

	blockString += "}\n";

	return blockString;
}
