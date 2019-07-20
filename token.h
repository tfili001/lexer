#include <string>
#include <vector>
#include "symbols.h"
using namespace std;



struct token_t
{
	token_t(void){}
	
	token_t(token_symbol Symbol, string Text) 
		: symbol(Symbol), text(Text){}
	
	token_symbol symbol;

	op_symbol op_sym = NO_SYMBOL;
	
	string text;
	uint32_t line_num;
	uint32_t  col_num;
};

vector<token_t> tokenize(size_t &fn_def_size, const string& src);

string token_to_string(token_t token);

void display_token(token_t token);

