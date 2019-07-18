
#include <vector>
#include "frame.h"

struct enviroment
{
	enviroment(){}
	enviroment(std::vector<frame> Frame_stack, frame Global_frame)
		: frame_stack(Frame_stack), global_frame(Global_frame){}

	std::vector<frame> frame_stack; 
	frame global_frame;	    
};

enviroment parser(std::vector<token_t> token_list);
