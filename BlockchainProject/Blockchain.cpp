#include "stdafx.h"
#include "Blockchain.h"

#include <windows.h>
#include <fstream>
#include <iostream>


Blockchain::Blockchain()
{
	// Create directory that stores blocks
	if ((CreateDirectory(s2ws(this->_blockchainDirectoryName).c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()))
	{
		list<string> fileNames = GetFileNames(this->_blockchainDirectoryName);
		
		if (fileNames.empty()) // if (FindNextFile(new string(this->_blockchainDirectoryName), NULL))
		{
			this->MineWithHash("legacy block");
		}
	} // else Failed to create directory.

	this->Sync();
}

Blockchain::~Blockchain()
{
}

void Blockchain::Sync()
{
	this->_chain = BlockList();

	if ((CreateDirectory(s2ws(this->_blockchainDirectoryName).c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()))
	{
		list<string> fileNames = this->GetFileNames(this->_blockchainDirectoryName);

		for (string fileName : fileNames)
		{
			Block b(this->_blockchainDirectoryName + "/" + fileName);
			this->_chain.push_back(b);
		}
	} // else Failed to create directory.
}

void Blockchain::PrintBlockchain()
{
	cout << "-----\nStart of Blockchain:\n-----\n";
	for (BlockList::iterator it = this->_chain.begin(); it != this->_chain.end(); it++)
	{
		cout << it->ToString();
	}
	cout << "-----\nEnd of Blockchain\n-----\n";
}

void Blockchain::Mine()
{
	this->MineWithHash(this->_chain.back().GetHash());
}

/// Helpfull private methods

void Blockchain::MineWithHash(string prviousHash)
{
	int nonce = 0;
	Block* b = NULL;

	do
	{
		delete b;
		b = new Block(this->_chain.size(), prviousHash, this->_currentTransactions, nonce++);
	} while (!this->IsBlockValid(b));

	this->_currentTransactions = TransactionList();

	b->Save(this->_blockchainDirectoryName, this->_chain.size());
	this->_chain.push_back(*b);

	delete b;
}

list<string> Blockchain::GetFileNames(string path)
{
	list<string> names;
	string search_path = path + "\\*.txt";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(s2ws(search_path).c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			char ch[260];
			char DefChar = ' ';
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				WideCharToMultiByte(CP_ACP, 0, fd.cFileName, -1, ch, 260, &DefChar, NULL);
				names.push_back(string(ch));
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

wstring Blockchain::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

bool Blockchain::IsBlockValid(Block* b)
{
	return b->GetHash().substr(b->GetHash().length() - 4) == string(this->_numberOfZeros, '0');
}
