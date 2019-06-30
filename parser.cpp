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
		if (token_list[i].symbol == FN)
		{
			i++;
			if (token_list[i].symbol != IDENTIFIER)
			{
				cerr<<"Function missing name\n";
				exit(1);
			}
			frame fndef;
			fndef.fn_name = token_list[i].text;
			
		}
        // Global Assignment
        else if (token_list[i].symbol == IDENTIFIER)
        {          
            display_token(token_list[i]);
                
            i++;
            if(token_list[i].symbol != EQUAL)
            {
                cerr<<"Variable missing assignment\n";
				exit(1);
            }
            
            display_token(token_list[i]);
            
            do
            {
                i++;
                display_token(token_list[i]);
                if(token_list[i].symbol != NUMERIC &&
                   token_list[i].symbol != IDENTIFIER)
                {   
                    // Operand           
                    cerr<<"Assignment missing operand\n";
					exit(1);
                }
       
                i++;
            }while(token_list[i].symbol == ADD);
            i--;
        }
    }  
    enviroment env(frame_stack, global_frame);
    return env;
}
