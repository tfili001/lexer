#include "enviroment.h"
#include <iostream>

using namespace std;


enviroment parser(vector<token_t> token_list)
{
    vector<frame> fn_defs;
    vector<frame> frame_stack;
    frame global_frame;
	
    for(size_t i = 0; i < token_list.size(); i++)
    {   
			if ( token_list[i].symbol == FN && i < token_list.size())
			{
				i++;
				if ( token_list[i].symbol != IDENTIFIER )
				{
					cerr << "error: Function definition missing identifier\n";
					exit(1);
				}
				
				frame fn_def;
				
				fn_def.fn_name = token_list[i].text.c_str();
				/*
					fn add x y
					{
				*/
				i++;
				
				while( token_list[i].symbol != L_BRACE )
				{
					if( token_list[i].symbol == IDENTIFIER ) 
					{
						/// Argument Variables
						var arg_var = var(token_list[i]);
						
						fn_def.local_vars.push_back(arg_var);
					}
					else
					{
						cerr << "error: Invalid symbol for function definition \"" 
							 << token_list[i].text << "\"\n";
						exit(1);
					}
					i++;
				}
				
				fn_def.arg_size = fn_def.local_vars.size();
				fn_defs.push_back(fn_def);
				i++;
				
				if ( token_list[i].symbol == IDENTIFIER )
				{
					if (token_list[i+1].symbol != EQUAL)
					{
						cerr << "error: Identifier missing assignment\n";
						exit(1);
					}
					
					i+=2;
					
					if (token_list[i].symbol == IDENTIFIER || 
						token_list[i].symbol == NUMERIC)
					{
						
					}
					else if (token_list[i].symbol == STRING_LITERAL)
					{
						
					}
					else
					{
						cerr << "error: can't figure out token\n";
						display_token(token_list[i]);
					}
										
				}
				
			}
    }  
	
	
    return enviroment(frame_stack, global_frame);
}