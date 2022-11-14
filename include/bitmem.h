#pragma once

#include <string>
#include <sstream>

class bitmem
{
public:
    static constexpr size_t item_size = 15;

    typedef unsigned short mem_t;
    static constexpr size_t mem_t_size = sizeof(mem_t) * 8;

    static constexpr mem_t item_mask = (1 << item_size) - 1;
    static constexpr int char_mask = (1 << 8) - 1;

private:
    mem_t* mem;
    size_t mem_size;

public:

    bitmem(size_t items_num);
    ~bitmem() noexcept;

    mem_t get(size_t i) const;
    void set(size_t i, mem_t val);

    std::string str() const;
    std::string byte_offset() const;
    std::string item_offset() const;
};
