#include "token.h"

enum type_t
{
	NUM,
	STRING,
	COMPLEX,
	LIST
};

struct var
{
    const char* identifier;
    token_t token;
    
    type_t type;
    char *str_text;
    double value;
	vector<token_t> expression;
	
	var(void){}
	var(token_t Token) : token(Token), identifier(Token.text.c_str()){}
};

