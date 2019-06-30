#include "var.h"
#include <vector>
#include <string>

using namespace std;

struct frame
{    
    string fn_name;
    size_t arg_size;
    
    vector<var> local_vars;
    vector<var>	output_stack;
	var return_var;
};
