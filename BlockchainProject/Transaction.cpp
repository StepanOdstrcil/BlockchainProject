#include "stdafx.h"
#include "Transaction.h"


Transaction::Transaction(string sender, string recipient, int amount) :
	_sender(sender), _recipient(recipient), _amount(amount)
{
}


Transaction::~Transaction()
{
}

string Transaction::ToString()
{
	return "{\n\tsender:" + this->_sender + "\n\trecipient:" + this->_recipient + "\n\tamount:" + to_string(this->_amount) + "\n}";
}

string Transaction::ToFileString()
{
	return this->_sender + ";" + this->_recipient + ";" + to_string(this->_amount) + "\n";
}
