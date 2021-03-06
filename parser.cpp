#include "enviroment.h"
#include "display.h"
#include "string.h"

using namespace std;

int get_frame_index_by_fn_name(const char* fn_name, const vector<frame> &frame_stack);

int get_var_index_by_identifier(const char* identifier, const frame&);

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
			////// Argument Captured //////
			i++;
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
				// To be put in function for global assignment
				// Assignemnt
				if( token_list[i].symbol   == IDENTIFIER &&
				    token_list[i+1].symbol == EQUAL)
				{
					var local_var = var(token_list[i]);
                    i+=2;
					   
					while( token_list[i].op_sym == OPERAND )
					{
                        const char* identifier = token_list[i].text.c_str();
                        
                        switch(token_list[i+1].op_sym)
                        {
                            case OPERATOR:
                            {
                                // Search for var identifier and function identifier
                                int var_index = get_var_index_by_identifier(identifier,fn_def);
                                
                                if( var_index != -1)
                                {
                                    token_list[i].var_index = var_index;
                                    local_var.expression.push_back(token_list[i]);
                                    local_var.expression.push_back(token_list[i+1]);
                                }
                                else  
                                {
                                    cerr <<"error: variable not declared\n";
                                    display_token(token_list[i]);
                                    exit(1);
                                }
                                
                                break;
                            }
                            case OPERAND:
                            {
                                
                                cerr<<"error: token shouldn't be value\n";
                                display_token(token_list[i+1]);
                                exit(1);
                                
                                break;
                            }
                            case PARENTHESIS:
                            {
                                // Function Call
                                int fn_index = get_frame_index_by_fn_name(identifier,fn_defs);
                                if ( fn_index != -1)
                                {
                                    token_list[i].op_sym = FN_CALL;
                                    local_var.expression.push_back(token_list[i]);
                                    frame_stack.push_back(fn_defs[fn_index]);
                                }
                                else
                                {
                                    cerr <<"error: function not declared\n";
                                    display_token(token_list[i]);
                                    exit(1);
                                }
                            }
                            case FN_CALL:
                            {
                                cerr << "FN_CALL shouldn't be assigned during tokenization\n";
                                exit(1);
                                break;
                            }
                            case NO_SYMBOL:
                            {
                                cout<<"Defined as No Symbol\n";
                                break;
                            }
      
                        }
                         
						i+=2;
					}
                    
					fn_def.local_vars.push_back(local_var);
				}
				else if( token_list[i].symbol == RETURN )
				{
					if ( token_list[i+1].op_sym != OPERAND &&
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
			fn_defs.push_back(fn_def);
		}
		else if ( token_list[i].symbol 	   == IDENTIFIER &&
				  token_list[i + 1].symbol == EQUAL)
		{	
			// Global Assignment
			
			var global_var = var(token_list[i]);					   
			i+=2;
					   
			while( token_list[i].op_sym == OPERAND )
			{
				if( get_var_index_by_identifier(token_list[i].text.c_str(),global_frame) != -1)
				{
					global_var.expression.push_back(token_list[i]);
				}
				else
				{
					cerr <<"error: variable not declared\n";
					display_token(token_list[i]);
					exit(1);
				}
				
				if ( token_list[i + 1].symbol == ADD)
				{
					global_var.expression.push_back(token_list[i+1]);
				}
				else
				{	  
					break;
				}
				i+=2;
			}
			global_frame.local_vars.push_back(global_var);
		}

    }
    
    cout<<"display framestack\n";
    
    for (const frame &f : frame_stack)
    {
        display_frame(f);
    }

	return enviroment(frame_stack, global_frame, fn_defs);
}

int get_var_index_by_identifier(const char* identifier, const frame &f)
{
	for (unsigned int i = 0; i < f.local_vars.size(); i++)
	{
		if (strcmp(identifier,f.local_vars[i].identifier) == 0)
			return i;
	}
	return -1;
}

int get_frame_index_by_fn_name(const char* fn_name, const vector<frame> &frame_stack)
{
	for (unsigned int i = 0; i < frame_stack.size(); i++)
	{
		if (strcmp(fn_name,frame_stack[i].fn_name) == 0)
			return i;
	}
	return -1;
}
