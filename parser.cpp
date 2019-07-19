#include "enviroment.h"
#include "display.h"
#include "string.h"

using namespace std;

int index_by_identifier(const char* identifier, const frame&);
bool is_operand(token_t token);

enviroment parser(vector<token_t> token_list)
{
	vector<frame> fn_defs;
	vector<frame> frame_stack;
	frame global_frame;

	for(size_t i = 0; i < token_list.size(); i++)
	{   
		if ( token_list[i].symbol == FN)
		{
			i++;
			
			////// Capture Function Definition //////
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
			////// Argument Captured //////
			while( token_list[i].symbol != L_BRACE )
			{
				if( token_list[i].symbol == IDENTIFIER ) 
				{
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
			i++;
			
			/* 
			 * Scan function body for:
			 * variable expressions,
			 * sub function calls, and
			 * optional return statements
			 */
			 
			while( token_list[i].symbol != R_BRACE )
			{
				if( token_list[i].symbol   == IDENTIFIER &&
				    token_list[i+1].symbol == EQUAL)
				{
					var local_var = var(token_list[i]);
					   
					i+=2;
					   
					while( is_operand(token_list[i]) )
					{
						if( index_by_identifier(token_list[i].text.c_str(),fn_def) != -1)
						{
							local_var.expression.push_back(token_list[i]);
						}
						else
						{
							cerr <<"error: variable not declared\n";
							display_token(token_list[i]);
							exit(1);
						}
						
						if ( token_list[i + 1].symbol == ADD)
						{
							local_var.expression.push_back(token_list[i+1]);
						}
						else
						{	  
							break;
						}
						i+=2;
					}
					fn_def.local_vars.push_back(local_var);
				}
				else if( token_list[i].symbol == RETURN )
				{
					if ( !is_operand(token_list[i+1]) &&
						 token_list[i+1].symbol != STRING_LITERAL )
					{
						cerr <<"error: return statement missing value\n";
						exit(1);
					}

					if ( token_list[i+2].symbol != R_BRACE )
				    {
						cerr <<"error: function missing \'}\'\n";
						exit(1);
				    }

					fn_def.return_var = var(token_list[i+1]);
					break;
				}
				i++;
			}
			display_frame(fn_def);
			fn_defs.push_back(fn_def);
		}

    }
	//display_frame(fn_defs[0]);
//	display_frame(fn_defs[1]);

	return enviroment(frame_stack, global_frame, fn_defs);
}

bool is_operand(token_t token)
{
	if ( token.symbol == IDENTIFIER ||
	     token.symbol == NUMERIC )
	{
		return true;
	}
	return false;
}

int index_by_identifier(const char* identifier, const frame &f)
{
	for (unsigned int i = 0; i < f.local_vars.size(); i++)
	{
		if (strcmp(identifier,f.local_vars[i].identifier) == 0)
		{
			return i;
		}
	}
	return -1;
}
