
#include <vector>
#include "frame.h"

struct enviroment
{
	enviroment(){}
	enviroment(std::vector<frame> Frame_stack, frame Global_frame, vector<frame> Fn_defs)
		: frame_stack(Frame_stack), global_frame(Global_frame), fn_defs(Fn_defs){}

	std::vector<frame> frame_stack;
	std::vector<frame> fn_defs;
	frame global_frame;	    
};

enviroment parser(std::vector<token_t> token_list);
