#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "processor.h"

#ifdef _WIN32
#include <conio.h>
#endif
#ifdef linux
#include <curses.h>
#endif

using namespace std;

vector<string> read_file(string filename = "program.txt")
{
    ifstream file(filename, ios_base::in);
    vector<string> ret{};
    string buff;
    while(getline(file, buff))
    {
	    if(buff.empty()) continue;
        ret.push_back(buff);
    }
    file.close();
    return ret;
}

int main()
{
    auto program = read_file();
    processor p(program);

    while(p.do_tick())
    {
        cout << p.get_state();
        getch();
        p.end_tick();
    }
}