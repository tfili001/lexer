#include "token.h"
#include <cstring>

enum type_t
{
	NUM,
	STRING,
	COMPLEX,
	LIST
};

struct var
{
	var(){}
	var(token_t Token) : token(Token)
	{
		identifier = new char [Token.text.length()+1];
		std::strcpy (identifier, Token.text.c_str());
	}

	char* identifier;
	token_t token;

	type_t type;
	const char *str_text;
	double value = 0;
	vector<token_t> expression;
};

