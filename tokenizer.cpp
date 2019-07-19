#include <iostream>
#include <sstream>
#include "token.h"

using namespace std;

vector<token_t> tokenize(const string& src)
{
	vector<token_t>token_list;
	uint32_t line_num = 1;
	uint32_t col_num  = 1;
	
	for(size_t i = 0; i < src.size(); i++)
	{
		if(!isspace(src[i]))
		{
			token_t token;
			size_t begin_pos = i;
			size_t end_length;

			if(src.substr(i,2) == "fn")
			{
				token = token_t(FN,src.substr(i,2));
                i++;
			}
			else if(src[i] == '{')
			{
				token = token_t(L_BRACE,"{");
			}
			else if(src.substr(i,6) == "return")
			{
				token = token_t(RETURN,src.substr(i,6));
			    i+=5;
			}
			else if(src[i] == '}')
			{
				token = token_t(R_BRACE,"}");
			}
			else if(isalpha(src[i]))
			{
				i++;
				col_num++;
				while(isalpha(src[i]))
				{
				    i++;
				}
				end_length = i - begin_pos;
				i--;										  
				token = token_t(IDENTIFIER,src.substr(begin_pos,end_length));
			}
			else if(src[i] == '=')
			{
			    col_num++;
				token = token_t(EQUAL,"=");
				
			}
			else if(src[i] == '+')
			{
			    col_num++;
				token.symbol  = ADD;
				token.op_type = true;
				token.text.push_back(src[i]);
			}
			else if(src[i] == '(')
			{
			    col_num++;
				token.symbol  = L_PARA;
				token.op_type = true;
				token.text.push_back(src[i]);
			}
			else if(isdigit(src[i]))
			{
				i++;
				col_num++;
				while(isdigit(src[i]))
				{
				    i++;
				}
				if(src[i+1] == '\n')
                {
                    line_num++;
                }               
				end_length 	 = i - begin_pos;
				token.symbol = NUMERIC;
				token.text   = src.substr(begin_pos,end_length);
			}
			else if(src[i] == ')')
			{
			    col_num++;
				token.symbol  = R_PARA;
				token.op_type = true;
				token.text.push_back(src[i]);
			}
			// Quote character
			else if(src[i] == '\"')
			{
				i++;
				col_num++;
				while(src[i] != '\"')
				{
				    i++;
				}
                if(src[i+1] == '\n')
                {
                  //  line_num++;
                }               
				end_length = i - begin_pos -1;
			/*  
			    We don't i-- so we can skip past 
                the ending string quote for the 
                next iteration.
			*/    
				token.symbol = STRING_LITERAL;
				token.text = src.substr(begin_pos + 1,
										end_length);
			}
			else
			{
				cerr<<"Error:Undetectable token\n";
				break;
			}
			token.col_num  = col_num;
			/*
    			Line number should be indivdually 
    			recorded in token member during 
    			each capture 
			*/
			token.line_num = line_num;		
			
			token_list.push_back(token);
		}
		else if(src[i] == '\n')
	    {
	        line_num++;
	        col_num = 1;
	    }
	    else
	    {
	        col_num++;
	    }
	}
	return token_list;
}

string token_to_string(token_t token)
{
	const char* syms[] =
	{
	   "IDENTIFIER",
	   "EQUAL",
	   "ADD",
	   "STRING_LITERAL",
	   "NUMERIC",
	   "FN",
       "L_BRACE",
	   "R_BRACE",
	   "RETURN"
	};

	stringstream ss;
	ss << '[' << syms[token.symbol] << " (" << token.text << ")] (" << token.line_num << ',' << token.col_num << ')';
return ss.str();
}

void display_token(token_t token)
{
	cout << token_to_string(token) << endl;	
}
