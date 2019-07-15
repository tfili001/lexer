
#include <vector>

using namespace std;

struct frame
{   
 	frame(void){}

	const char* fn_name;
    size_t arg_size;
    
    vector<var> local_vars;
    vector<var>	output_stack;
	var return_var;
};
