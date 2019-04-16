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
	uint32_t line_num;
	uint32_t  col_num;
	token_symbol symbol;
};

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
				token.text   = src.substr(begin_pos,end_length);
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
				end_length = i - begin_pos;
				token.symbol = NUMERIC;
				token.text   = src.substr(begin_pos,end_length);
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
				token.text = src.substr(begin_pos+1,end_length);
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
cout<<"["<<syms[token.symbol]<<" ("<<token.text<<")] ("
    <<token.line_num<<','<<token.col_num<<")\n";
}



struct var
{
    string identifier;
    token_t token;
    string text_data;
    double value;
};

struct frame
{    
    string name;
    size_t arg_size;
    
    vector<var> local_vars;
    size_t local_size;
    
    vector<var>output_stack;
    var return_var;
};

vector<frame> parser(vector<token_t> token_list)
{
    vector<frame>fn_defs;
    vector<frame>frame_stack; 
    frame global_frame;
    
    for(size_t i = 0; i < token_list.size(); i++)
    {
        
        // Global Assignment
        if (token_list[i].symbol == IDENTIFIER)
        {          
                display_token(token_list[i]);
                
            i++;
            if(token_list[i].symbol != EQUAL)
            {
                cerr<<"Variable missing assignment\n";
                return frame_stack;
            }
            
            display_token(token_list[i]);
            
        
            cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
            do
            {
                i++;
                display_token(token_list[i]);
                if(token_list[i].symbol != NUMERIC &&
                   token_list[i].symbol != IDENTIFIER)
                {   
                    // Operand
                
                    cerr<<"Assignment missing operand\n";

                    return frame_stack;
                }

                
            
                i++;
            }while(token_list[i].symbol == ADD);
            cout<<"_____________________________\n";
            i--;
        } 
    }  
    
    return frame_stack;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr<<"missing file\n";
        return 0;
    }
	string src = file_to_string(argv[1]);

	vector<token_t> token_list = tokenize(src);

    vector<frame>frame_stack = parser(token_list); 
	

return 0;
}
