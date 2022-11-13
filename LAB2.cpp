#include <iostream>

using namespace std;

class bitmem
{
public:
    static const size_t item_size = 14;
    typedef unsigned short mem_t;
    static const size_t mem_t_size = sizeof(mem_t) * 8;
    static const mem_t item_mask = (1 << item_size) - 1;
    
    mem_t* mem;
    size_t mem_size;
    size_t items_num;

public:
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
};

int main()
{
    bitmem mem(20);
    mem.set(0, 12);
    mem.set(1, 13);
    mem.set(2, 16383);
    std::cout << mem.get(0) << " "<<mem.get(1) << " " << mem.get(2) << "\n";
    mem.set(1, 16383);
    std::cout << mem.get(0) << " " << mem.get(1) << " " << mem.get(2);
}