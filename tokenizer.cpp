#include <string>
#include <vector>
#include <iostream>
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
                token.text = src.substr(i,2);
                token.symbol = FN;
                i++;
			}
			else if(src.substr(i,6) == "return")
			{
			    token.text = src.substr(i,6);
			    token.symbol = RETURN;
			    i+=5;
			}
			else if(src[i] == '{')
			{
			    token.text   = src[i];
                token.symbol = L_BRACE;
			}
			else if(src[i] == '}')
			{
			    token.text   = src[i];
                token.symbol = R_BRACE;
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
				token.symbol = IDENTIFIER;
				token.text   = src.substr(begin_pos,
										  end_length);
			}
			else if(src[i] == '=')
			{
			    col_num++;
				token.symbol = EQUAL;
				token.text.push_back(src[i]);
			}
			else if(src[i] == '+')
			{
			    col_num++;
				token.symbol = ADD;
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
				token.text   = src.substr(begin_pos,
									      end_length);
			}
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
				token.symbol = STRING;
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
