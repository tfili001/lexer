#include <string>
#include <vector>

using namespace std;

enum token_symbol
{
	IDENTIFIER,
	EQUAL,
	ADD,
	L_PARA,
	R_PARA,
	STRING_LITERAL,
	NUMERIC,
	FN,
	L_BRACE,
	R_BRACE,
	RETURN
};

struct token_t
{
	token_t(void){}
	
	token_t(token_symbol Symbol, string Text) : symbol(Symbol), text(Text){}
	
	token_symbol symbol;
	bool op_type = false;
	
	string text;
	uint32_t line_num;
	uint32_t  col_num;
};

vector<token_t> tokenize(const string& src);

string token_to_string(token_t token);

void display_token(token_t token);

