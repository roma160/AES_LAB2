#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "bitmem.h"

class processor
{
public:
    using reg_t = bitmem::mem_t;

    reg_t R1;
    reg_t PC, TC, RS;
    bitmem ram;

    struct command
    {
        enum name_t : reg_t
        {
            set_c, load_ca, unwrap, dump_ca, mod_c, mod_ca,
            COUNT
        };
        static std::map<name_t, const char*> name_map;

        name_t name;
        reg_t val;

        std::string str() const;
    } IR;

    std::vector<std::string> program;

    processor(std::vector<std::string> program, size_t ram_size = 10);

    bool do_tick();
    void end_tick();

    std::string get_state() const;
};
