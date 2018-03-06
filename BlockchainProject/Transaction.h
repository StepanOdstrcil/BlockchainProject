#pragma once

#include "stdafx.h"

// Predefinitions
class Transaction;

typedef list<Transaction> TransactionList;

class Transaction
{
private:
	string _sender;
	string _recipient;
	int _amount;
public:
	Transaction(string sender, string recipient, int amount);
	~Transaction();
	string ToString();
	string ToFileString();
};
