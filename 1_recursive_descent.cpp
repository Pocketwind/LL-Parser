/*
1. S->aS
2. S->bA
3. A->d
4. A->ccA
*/
#include<vector>
#include<iostream>
#include<string>
using namespace std;

void Error();
void Accept();
void pS();
void pA();

string str;
int pivot;
char nextSymbol;
vector<int> parse;

void GetNextSymbol()
{
	pivot++;
	nextSymbol = str[pivot];
}

void pS()
{
	if (nextSymbol == 'a')
	{
		GetNextSymbol();
		parse.push_back(1);
		pS();
	}
	else if (nextSymbol == 'b')
	{
		GetNextSymbol();
		parse.push_back(2);
		pA();
	}
	else
		Error();
}

void pA()
{
	if (nextSymbol == 'd')
	{
		GetNextSymbol();
		parse.push_back(3);
		if (nextSymbol == '$')
			Accept();
		else
			Error();
	}
	else if (nextSymbol == 'c')
	{
		GetNextSymbol();
		if (nextSymbol == 'c')
		{
			parse.push_back(4);
			GetNextSymbol();
			pA();
		}
		else
			Error();
	}
	else
		Error();
}

void Accept()
{
	cout << "Accept" << endl;
}

void Error()
{
	cout << "Reject" << endl;
	exit(1);
}

int main()
{
	cout << "Sentence : ";
	cin >> str;

	pivot = 0;
	nextSymbol = str[pivot];

	pS();

	cout << "Left Parse : ";
	for (int i = 0; i < parse.size(); ++i)
		cout << parse[i];
	cout << endl;

	return 0;
}