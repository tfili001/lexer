#include <vector>
#include "frame.h"

struct enviroment
{
	enviroment(vector<frame> Frame_stack,
	           frame Global_frame)
	            
	: frame_stack(Frame_stack), 
	  global_frame(Global_frame){}


	vector<frame> frame_stack; 
	frame global_frame;	    
};

enviroment parser(vector<token_t> token_list);
