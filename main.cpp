// std
#include <fstream>

// cstd
#include <ctype.h>

// local
#include "enviroment.h"

using namespace std;

string file_to_string(const char* path)
{
	ifstream ifs(path);
	string text( (istreambuf_iterator<char>(ifs) ),
                       (istreambuf_iterator<char>()));
	return text;
}

int main(int argc, char *argv[])
{

	string src = file_to_string("../fnexample");
	size_t fn_def_size = 0;
	vector<token_t> token_list = tokenize(fn_def_size,src);

	
	enviroment env = parser(token_list);
	
	return 0;
}