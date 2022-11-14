#pragma once
#include <vector>
#include <string>
#include <sstream>

#include "bitmem.h"

class processor
{
public:
    using reg_t = bitmem::mem_t;

    reg_t accm;
    reg_t line, tick, comm, stat;
    bitmem ram;

    std::vector<std::string> program;

    struct command
    {
        enum name_t : reg_t
        {
            set_c, dump_ca, load_ca, mod_c, mod_ca
        } name;

        reg_t val;
    } cur_command;
    std::string cur_command_str;

    processor(std::vector<std::string> program, size_t ram_size = 10);

    bool do_tick();

    void end_tick();

    static std::string to_binary(reg_t n);

    std::string get_state() const;
};
