#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class bitmem
{
public:
    static constexpr size_t item_size = 15;
    typedef unsigned short mem_t;
    static constexpr size_t mem_t_size = sizeof(mem_t) * 8;
    static constexpr mem_t item_mask = (1 << item_size) - 1;
    static constexpr int char_mask = (1 << 8) - 1;
    
    mem_t* mem;
    size_t mem_size;
    size_t items_num;
    
    bitmem(size_t items_num): items_num(items_num)
    {
        mem_size = items_num * item_size;
        mem_size = mem_size / mem_t_size + (mem_size % mem_t_size != 0);
        mem = new mem_t[mem_size];
        fill(mem, mem + mem_size, 0);
    }
    ~bitmem() noexcept
    {
        delete[] mem;
    }

    // Setting the current and next cell:
    //      |......item|..shift|
    // |mem_T 1 ...|mem_T 0 ...|

    mem_t get(const size_t i) const
    {
        const size_t bit_index = i * item_size;
        const size_t index = bit_index / mem_t_size;
        const size_t bit_shift = bit_index % mem_t_size;

        mem_t ret = mem[index] >> bit_shift;
        if (bit_shift) ret |= mem[index + 1] << (mem_t_size - bit_shift);
        ret &= item_mask;
        return ret;
    }
    void set(const size_t i, const mem_t val)
    {
        const size_t bit_index = i * item_size;
        const size_t index = bit_index / mem_t_size;
        const size_t shift = bit_index % mem_t_size;
        mem[index] = (mem_t)(val << shift) |
					 (mem[index] & ((mem_t)(1 << shift) - 1));
        
        if (shift > 0) {
            mem[index + 1] = (mem[index + 1] & (
								(1 << mem_t_size) - (1 << (item_size + shift - mem_t_size)))
                              ) |
							 ((mem_t) val >> (mem_t_size - shift));
        }
    }

    string str() const
    {
    	stringstream s;
        auto* buff = (unsigned const char*) mem;
        for(size_t i = mem_size * mem_t_size / 8 - 1; i >= 1; i--)
        {
            s << hex << setfill('0') << setw(2) << (int) buff[i] << '.';
        }
        s << hex << setfill('0') << setw(2) << (int)buff[0];
        return s.str();
    }

    string order() const
    {
        stringstream s;
        for (size_t i = mem_size * mem_t_size / 8 - 1; i >= 1; i--)
        {
            s << setfill('0') << setw(2) << i << '.';
        }
        s << hex << setfill('0') << setw(2) << 0;
        return s.str();
    }
};

class processor
{
public:
    using reg_t = bitmem::mem_t;
    
    reg_t accum;
	reg_t line, tick, comm, stat;
    bitmem ram;

    struct command
    {
        enum name_t: reg_t
        {
            set, dump, mod
	    } name;

        reg_t val;
    } cur_command;
    vector<string> program;

    processor(vector<string> program, const size_t ram_size = 10):
		ram(ram_size), accum(0), line(0), tick(0), comm(0), stat(0), cur_command()
    {
        this->program = move(program);
    }

    void do_tick()
    {
	    if(tick == 0)
	    {
            // Parsing command data from string
            stringstream s;
            s << program[line];

            string buff_name;
            s >> buff_name;
            if (strcmp(buff_name.c_str(), "set") == 0)
                cur_command.name = command::set;
            else if (strcmp(buff_name.c_str(), "dump") == 0)
                cur_command.name = command::dump;
            else if (strcmp(buff_name.c_str(), "mod") == 0)
                cur_command.name = command::mod;

            s >> cur_command.val;
	    }
        else if(tick == 1)
        {
	        switch (comm)
	        {
            case command::set:
                accum = cur_command.val;
                break;
            case command::dump:
                ram.set(cur_command.val, accum);
                break;
            case command::mod:
                accum %= cur_command.val;
                break;
	        }
        }
        tick++;
        tick %= 2;
    }
};



int main()
{
    bitmem mem(20);
    mem.set(0, 12);
    mem.set(1, 13);
    mem.set(2, 16383);
    cout << mem.get(0) << " " << mem.get(1) << " " << mem.get(2) << "\n";
    cout << mem.str() << "\n" << mem.order() << "\n";
}