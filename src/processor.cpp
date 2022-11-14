#include "processor.h"

#include <cstring>
#include <iomanip>
#include <algorithm>

using namespace std;

processor::processor(vector<string> program, const size_t ram_size):
	ram(ram_size), accm(0), line(0), tick(0), comm(0), stat(0), cur_command()
{
	this->program = move(program);
}

bool processor::do_tick()
{
	if (line >= program.size()) return false;

	if (tick == 0)
	{
		// Parsing command data from string
		stringstream s;
		s << program[line];
		cur_command_str = s.str();

		string buff_name;
		s >> buff_name;
		if (strcmp(buff_name.c_str(), "set_c") == 0)
			cur_command.name = command::set_c;
		else if (strcmp(buff_name.c_str(), "dump_ca") == 0)
			cur_command.name = command::dump_ca;
		else if (strcmp(buff_name.c_str(), "load_ca") == 0)
			cur_command.name = command::load_ca;
		else if (strcmp(buff_name.c_str(), "mod_c") == 0)
			cur_command.name = command::mod_c;
		else if (strcmp(buff_name.c_str(), "mod_ca") == 0)
			cur_command.name = command::mod_ca;

		s >> cur_command.val;

		comm = cur_command.name;
	}
	else if (tick == 1)
	{
		switch (comm)
		{
		case command::set_c:
			accm = cur_command.val;
			break;
		case command::dump_ca:
			ram.set(cur_command.val, accm);
			break;
		case command::load_ca:
			accm = ram.get(cur_command.val);
			break;
		case command::mod_c:
			accm %= cur_command.val;
			break;
		case command::mod_ca:
			accm %= ram.get(cur_command.val);
			break;
		}
	}

	return line < program.size();
}
void processor::end_tick()
{
	if (tick == 1) line++;
	tick++;
	tick %= 2;
}

std::string processor::to_binary(reg_t n)
{
	stringstream s;
	while (n > 0)
	{
		s << n % 2;
		n >>= 1;
	}
	string ret = s.str();
	reverse(ret.begin(), ret.end());
	ret = string(bitmem::item_size - ret.size(), '0') + ret;
	for (int i = bitmem::item_size - 8; i > 0; i -= 8)
		ret.insert(i, 1, '.');
	return ret;
}

std::string processor::get_state() const
{
	static constexpr auto delim = "------------------------------------\n";

	stringstream ss;
	ss << delim << "Current executed line: " << cur_command_str << "\n";

	ss << "\nOperand registers:\n";
	ss << "accm = " << to_binary(accm) << "\n";

	ss << "\nRAM:\n";
	ss << ram.str() << "\n" << ram.order() << "\n";

	ss << "\nState registers:\n";
	ss << "line = " << to_binary(line) << "\n";
	ss << "tick = " << to_binary(tick) << "\n";
	ss << "comm = " << to_binary(comm) << "\n";
	ss << "stat = " << to_binary(stat) << "\n";

	return ss.str();
}
