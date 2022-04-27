#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
 
// structure of token
struct token
{
	int token_num;
	string lexeme;
	int lineNo;
};
 
static token createToken(int token_num, string lex, int line)
{
	token tok;
	tok.token_num = token_num;
	tok.lexeme = lex;
	tok.lineNo = line;
	return tok;
}
 
vector<token> token_list;
map<int, string> symbol_table;
vector<string> keywords = {"main", "int", "float", "string", "bool", "for", "while", "return", "var", "if", "elsif", "else", "print"};
 
// error for stray character
void throw_error(char ch, int lineNo)
{
	cout << "Lexical error: stray "
		 << "\'" << ch << "\'"
		 << " in program at line number = " << lineNo << endl;
}
// error for stray lexeme
void throw_error(string lex, int *idx, int lineNo)
{
	cout << "Lexical error: stray "
		 << "\'" << lex << "\'"
		 << " in program at line number = " << lineNo << endl;
	(*idx)++;
}
// ignore comments while reading input file
void skipComments(string line, int *idx, int lineNo)
{
	(*idx)++;
	if (line[*idx] == '%')
	{
		while (line[*idx])
		{
			(*idx)++;
		}
	}
	else
	{
		(*idx)--;
		throw_error("%", idx, lineNo);
		return;
	}
}
 
// dfa for relational operators
void scanRelOp(string line, int *idx, int lineNo)
{
	switch (line[*idx])
	{
	case '<':
		(*idx)++;
		if (line[*idx] == '=')
		{
			token_list.push_back(createToken(600, "<=", lineNo));
			symbol_table[600] = "<=";
		}
		else
		{
			(*idx)--;
			token_list.push_back(createToken(601, "<", lineNo));
			symbol_table[601] = "<";
		}
		break;
	case '>':
		(*idx)++;
		if (line[*idx] == '=')
		{
			token_list.push_back(createToken(602, ">=", lineNo));
			symbol_table[602] = ">=";
		}
		else
		{
			(*idx)--;
			token_list.push_back(createToken(603, ">", lineNo));
			symbol_table[603] = ">";
		}
		break;
	case '=':
		(*idx)++;
		if (line[*idx] == '=')
		{
			token_list.push_back(createToken(604, "==", lineNo));
			symbol_table[604] = "==";
		}
		else if (line[*idx] == ' ')
		{
			throw_error("=", idx, lineNo);
			return;
		}
		else
		{
			(*idx)--;
			throw_error("=", idx, lineNo);
			return;
		}
		break;
	}
	(*idx)++;
}
 
// dfa for assignment op
void scanAssignOp(string line, int *idx, int lineNo)
{
	(*idx)++;
	if (line[*idx] == '=')
	{
		token_list.push_back(createToken(700, ":=", lineNo));
		symbol_table[700] = ":=";
	}
	else if (line[*idx] == ' ')
	{
		throw_error(":", idx, lineNo);
		return;
	}
	else
	{
		(*idx)--;
		throw_error(":", idx, lineNo);
		return;
	}
	(*idx)++;
}
 
// dfa for scanning numbers (integer/float)
void scanNumberToken(string line, int *idx, int lineNo)
{
	int state = 0; // start state
	string lexeme = "";
 
	if (line[*idx] < '0' || line[*idx] > '9')
	{
		state = 5;
		throw_error(line[*idx], lineNo);
		(*idx)--;
		return;
	}
 
	if (state == 0)
	{
		if (line[*idx] >= '1' && line[*idx] <= '9')
		{
			state = 2;
			lexeme += line[*idx];
			(*idx)++;
		}
		else if (line[*idx] == '0')
		{
			state = 1;
			lexeme += line[*idx];
			(*idx)++;
		}
		else if (line[*idx] < '0' || line[*idx] > '9')
		{
			state = 5;
			throw_error(lexeme, idx, lineNo);
			(*idx)--;
			return;
		}
	}
	if (state == 1)
	{
		if (line[*idx] == '.')
		{
			state = 3;
			lexeme += line[*idx];
			(*idx)++;
		}
		else
		{
			token_list.push_back(createToken(100, lexeme, lineNo));
			symbol_table[100] = "num";
		}
	}
	if (state == 2)
	{
		while (line[*idx] >= '0' && line[*idx] <= '9')
		{
			lexeme += line[*idx];
			(*idx)++;
		}
		if (line[*idx] == '.')
		{
			state = 3;
			lexeme += line[*idx];
			(*idx)++;
		}
		else
		{
			token_list.push_back(createToken(100, lexeme, lineNo));
			symbol_table[100] = "num";
		}
	}
	if (state == 3)
	{
		if (line[*idx] < '0' || line[*idx] > '9')
		{
			state = 5;
			throw_error(lexeme, idx, lineNo);
			(*idx)--;
			return;
		}
		else
		{
			state = 4;
			lexeme += line[*idx];
			(*idx)++;
		}
	}
	if (state == 4)
	{
		while (line[*idx] >= '0' && line[*idx] <= '9')
		{
			lexeme += line[*idx];
			(*idx)++;
		}
		token_list.push_back(createToken(101, lexeme, lineNo));
		symbol_table[101] = "num";
	}
}
 
// dfa for scanning named entities
void scanNamesToken(string line, int *idx, int lineNo)
{
	string lexeme = "";
	(*idx)--;
	char firstLetter = line[*idx];
	(*idx)++;
	while ((line[*idx]) && ((line[*idx] >= 'a' && line[*idx] <= 'z') || (line[*idx] >= '0' && line[*idx] <= '9') || (line[*idx] >= 'A' && line[*idx] <= 'Z') || (line[*idx] == '_')))
	{
		lexeme += line[*idx];
		(*idx)++;
	}
	if (firstLetter >= '0' && firstLetter <= '9')
	{
		throw_error(firstLetter + lexeme, idx, lineNo);
		return;
	}
	int flg = 0;
	for (int i = 0; i < keywords.size(); i++)
	{
		if (lexeme == keywords[i])
		{
			token_list.push_back(createToken(501 + i, lexeme, lineNo));
			symbol_table[501 + i] = keywords[i];
			flg = 1;
			break;
		}
	}
	if (flg == 0)
	{
		token_list.push_back(createToken(500, lexeme, lineNo));
		symbol_table[500] = "id";
	}
}
 
void scanStringliterals(string line, int *idx, int lineNo)
{
	// cout<<"str"<<endl;
	string lexeme = "";
	(*idx)++;
	int flg = 0;
	while (line[*idx] != '\"')
	{
		// cout<<line[*idx]<<endl;
		lexeme += line[*idx];
		(*idx)++;
	}
	token_list.push_back(createToken(111, lexeme, lineNo));
	symbol_table[111] = "str";
	(*idx)++;
}
 
int scanTokens(string fname1, string fname2)
{
	ifstream fin;  // input file stream
	ofstream fout; // output file stream
	fin.open(fname1);
	fout.open(fname2);
	int lineNo = 0; // maintains line number count
	string line;
	while (getline(fin, line))
	{
		lineNo++;
		int idx = 0; // positional index
		while (line[idx])
		{
			if ((line[idx] >= 'A' && line[idx] <= 'Z') || (line[idx] >= 'a' && line[idx] <= 'z'))
			{
				scanNamesToken(line, &idx, lineNo);
			}
			else if ((line[idx] >= '0' && line[idx] <= '9'))
			{
				scanNumberToken(line, &idx, lineNo);
			}
			else
			{
				switch (line[idx])
				{
				case '%':
					skipComments(line, &idx, lineNo);
					break; // get comments
				case '\t':
				case ' ':
					idx++;
					break; // ignore whitespaces,tabs
				case '+':
				case '-':
				case '*':
				case '/':
					switch (line[idx])
					{
					case '+':
						token_list.push_back(createToken(300, "+", lineNo));
						symbol_table[300] = "+";
						break;
					case '-':
						token_list.push_back(createToken(301, "-", lineNo));
						symbol_table[301] = "-";
						break;
					case '*':
						token_list.push_back(createToken(302, "*", lineNo));
						symbol_table[302] = "*";
						break;
					case '/':
						token_list.push_back(createToken(303, "/", lineNo));
						symbol_table[303] = "/";
						break;
					}
					idx++;
					break; // arithmetic operators
				case '>':
				case '<':
				case '=':
					scanRelOp(line, &idx, lineNo);
					break; // relational operator
				case '{':
				case '}':
				case '(':
				case ')':
				case '[':
				case ']':
				case ';':
				case ',':
					// delimiters
					switch (line[idx])
					{
					case '{':
						token_list.push_back(createToken(400, "{", lineNo));
						symbol_table[400] = "{";
						break;
					case '}':
						token_list.push_back(createToken(401, "}", lineNo));
						symbol_table[401] = "}";
						break;
					case '(':
						token_list.push_back(createToken(402, "(", lineNo));
						symbol_table[402] = "(";
						break;
					case ')':
						token_list.push_back(createToken(403, ")", lineNo));
						symbol_table[403] = ")";
						break;
					case ',':
						token_list.push_back(createToken(404, ",", lineNo));
						symbol_table[404] = ",";
						break;
					case '[':
						token_list.push_back(createToken(405, "[", lineNo));
						symbol_table[405] = "[";
						break;
					case ']':
						token_list.push_back(createToken(406, "]", lineNo));
						symbol_table[406] = "]";
						break;
					case ';':
						token_list.push_back(createToken(200, ";", lineNo));
						symbol_table[200] = ";";
						break;
					}
					idx++;
					break;
				case ':':
					scanAssignOp(line, &idx, lineNo);
					break;
				case '\"':
					scanStringliterals(line, &idx, lineNo);
					break;
				default:
					throw_error(line[idx], lineNo);
					idx++;
					break;
				}
			}
		}
	}
	// Writing the token list on o/p file
	for (token tk : token_list)
	{
		fout << "Token " << tk.token_num << ", string \"" << tk.lexeme << "\", line number " << tk.lineNo << "\n";
	}
 
	token_list.push_back(createToken(-1, "$", -1));
	symbol_table[-1] = "$";
 
	fin.close();
	fout.close();
	return 0;
}
 
// int main() {
// 	scanTokens("/Users/sarvu_don/Desktop/College/Sem 2021-2022 (II)/Compiler construction/project/Compiler-Construction-main 2/TC_lexer/tc_1.txt", "/Users/sarvu_don/Desktop/College/Sem 2021-2022 (II)/Compiler construction/project/Compiler-Construction-main 2/TC_lexer/tc_1_op.txt");
// }