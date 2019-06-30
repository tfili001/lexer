#include <string>
#include <iostream>
#include <sstream>
using namespace std;

enum token_symbol
{
	IDENTIFIER,
	EQUAL,
	ADD,
	STRING,
	NUMERIC,
	FN,
	L_BRACE,
	R_BRACE,
	RETURN
};

struct token_t
{
	string text;
	uint32_t line_num;
	uint32_t  col_num;
	token_symbol symbol;
};

vector<token_t> tokenize(const string& src);

string token_to_string(token_t token)
{
	const char* syms[] =
	{
	   "IDENTIFIER",
	   "EQUAL",
	   "ADD",
	   "STRING",
	   "NUMERIC",
	   "FN",
       "L_BRACE",
	   "R_BRACE",
	   "RETURN"
	};

	stringstream ss;
	ss << '[' << syms[token.symbol] << " (" << 
token.text << ")] (" << token.line_num << ',' << token.col_num << ')';
return ss.str();
}

void display_token(token_t token)
{
	cout << token_to_string(token) << endl;	
}
