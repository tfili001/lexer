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
	/*
    if(argc < 2)
    {
        cerr<<"Missing file\n";
        return 0;
    }
	*/
	string src = file_to_string("../fnexample");
	vector<token_t> token_list = tokenize(src);
	
	/*
	for(const auto &i : token_list)
	{	 
		display_token(i);
	}
	*/
	
	enviroment env = parser(token_list);
	
	/*
	for(const auto &i : env.frame_stack)
	{	 
		
	}
	*/	
	return 0;
}