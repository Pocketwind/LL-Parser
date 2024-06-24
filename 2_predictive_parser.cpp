/*
1. S->aS
2. S->bA
3. A->d
4. A->ccA
	a	b	c	d	$
S	1	2				
A			4	3	
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void Accept();
void Error();
void Push(char);
void Pop();
void GetNextSymbol();
void pS();
char GetTop();
void Parsing();
void GetAction(char, char);
void Rules(int);
bool isTerminal(char);
bool isNonTerminal(char);
void Print();

vector<char> terminals;
vector<char> nonTerminals;
vector<char> stack;
int pivot;
char nextSymbol;
string str;
vector<int> parse;
int** table;

void Parsing()
{
	while (GetTop() != '$')
	{
		Print();

		if (isTerminal(GetTop()))
		{
			if (nextSymbol == GetTop())
			{
				Pop();
				GetNextSymbol();
			}
			else
				Error();
		}
		else if (isNonTerminal(GetTop()))
		{
			GetAction(GetTop(), nextSymbol);
		}
		else
			Error();
	}
	Accept();
}

void Print()
{
	cout << "Stack : ";
	for (int i = 0; i < stack.size(); ++i)
		cout << stack[i];
	cout << "\t\t";
	cout << "Input : ";
	for (int i = pivot; i < str.size(); ++i)
		cout << str[i];
	cout << endl;
}

bool isTerminal(char in)
{
	for (int i = 0; i < terminals.size(); ++i)
		if (terminals[i] == in)
			return true;
	return false;
}

bool isNonTerminal(char in)
{
	for (int i = 0; i < nonTerminals.size(); ++i)
		if (nonTerminals[i] == in)
			return true;
	return false;
}

void GetAction(char left, char right)
{
	int row, col;
	for (int i = 0; i < nonTerminals.size(); ++i)
		if (nonTerminals[i] == left)
			row = i;
	for (int i = 0; i < terminals.size(); ++i)
		if (terminals[i] == right)
			col = i;
	Rules(table[row][col]);
}

void Rules(int p)
{
	switch (p)
	{
	case 1:
		parse.push_back(1);
		Pop();
		Push('S');
		Push('a');
		break;
	case 2:
		parse.push_back(2);
		Pop();
		Push('A');
		Push('b');
		break;
	case 3:
		parse.push_back(3);
		Pop();
		Push('d');
		break;
	case 4:
		parse.push_back(4);
		Pop();
		Push('A');
		Push('c');
		Push('c');
		break;
	default:
		Error();
	}
}

char GetTop()
{
	return stack[stack.size() - 1];
}

void GetNextSymbol()
{
	pivot++;
	nextSymbol = str[pivot];
}

void Push(char in)
{
	stack.push_back(in);
}

void Pop()
{
	stack.pop_back();
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

	terminals = { 'a','b','c','d','$' };
	nonTerminals = { 'S','A' };
	table=new int*[nonTerminals.size()];
	for(int i = 0; i < nonTerminals.size(); ++i)
		table[i] = new int[terminals.size()];
	table[0][0] = 1;
	table[0][1] = 2;
	table[1][2] = 4;
	table[1][3] = 3;

	stack.push_back('$');
	stack.push_back('S');

	pivot = 0;
	nextSymbol = str[pivot];

	Parsing();

	cout << "Left Parse : ";
	for (int i = 0; i < parse.size(); ++i)
		cout << parse[i];
	cout << endl;

	for(int i = 0; i < nonTerminals.size(); ++i)
		delete[] table[i];
	delete[] table;

	return 0;
}