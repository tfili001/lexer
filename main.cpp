// std::
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// cstd
#include <ctype.h>

// local

#include "frame.h"

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
    if(argc < 2)
    {
        cerr<<"Missing file\n";
        return 0;
    }
	string src = file_to_string(argv[1]);

	vector<token_t> token_list = tokenize(src);
	for(const auto &token : token_list)
	{	
		display_token(token);
	}	

return 0;
}
