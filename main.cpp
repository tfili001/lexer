#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctype.h>

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
//	uint32_t line_num;
//	uint32_t col_num;
	token_symbol symbol;
};

vector<token_t> tokenize(const string& src)
{
	vector<token_t>token_list;
	
	for(size_t i = 0; i < src.size(); i++)
	{
		if(!isspace(src[i]))
		{
			token_t token;
			size_t begin_pos = i;
			size_t end_length;
//			cout<<"leading token ["<<src[i]<<"]\n";
			if(src[i] =='\n')
			{
//				cout<<"New Line Detected\n";
			}
			else if(isalpha(src[i]))
			{
			//    cout<<"Identifier\n";
				i++;
				while(isalpha(src[i]))
				{
				i++;
				}
				end_length = i - begin_pos;
				i--;
				token.symbol = IDENTIFIER;
				token.text   = src.substr(begin_pos,end_length);
			}
			else if(src[i] == '=')
			{
				//cout<<"Equal Added\n";
				token.symbol = EQUAL;
				token.text.push_back(src[i]);
			}
			else if(src[i] == '+')
			{
				token.symbol = ADD;
				token.text.push_back(src[i]);
			}
			else if(isdigit(src[i]))
			{
			//    cout<<"Digit found\n";
				i++;
				while(isdigit(src[i])){i++;}
				end_length = i - begin_pos;
				token.symbol = NUMERIC;
				token.text   = src.substr(begin_pos,end_length);
			}
			else if(src[i] == '\"')
			{
			//    cout<<"String found\n";
				i++;
				while(src[i] != '\"')
				{
    
				i++;
				}
                
				end_length = i - begin_pos -1;
			/*  
			    We don't i-- so we can skip past 
                the ending string quote for the 
                next iteration. Possibly problematic
                for future additions. Guess we'll 
                find out :^)
			*/    
				token.symbol = STRING;
				token.text = src.substr(begin_pos+1,end_length);
			}
			/*
			else if(src[i] =='\n')
			{
				cout<<"New Line Detected\n";
			}
			*/
			else
			{
				cerr<<"Error:Undetectable token\n";
				break;
			}
			
			token_list.push_back(token);
		}
	}
	return token_list;
}

string file_to_string(const char* path)
{
	ifstream ifs(path);
	string content( (istreambuf_iterator<char>(ifs) ),
                       (istreambuf_iterator<char>()));
return content;
}

void display_token(token_t token)
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
	cout<<"["<<syms[token.symbol]<<" ("<<token.text<<")]\n";
}

int main()
{
	string src = file_to_string("example");

	auto token_list = tokenize(src);

	for(const auto& token : token_list)
		display_token(token);


return 0;
}
