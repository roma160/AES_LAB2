#include "bitmem.h"

#include <algorithm>
#include <iomanip>

using namespace std;

bitmem::bitmem(size_t items_num)
{
	mem_size = items_num * item_size;
	mem_size = mem_size / mem_t_size + (mem_size % mem_t_size != 0);
	mem = new mem_t[mem_size];
	std::fill(mem, mem + mem_size, 0);
}
bitmem::~bitmem() noexcept
{
	delete[] mem;
}

// Setting the current and next cell:
//      |......item|..shift|
// |mem_T 1 ...|mem_T 0 ...|
bitmem::mem_t bitmem::get(const size_t i) const
{
	const size_t bit_index = i * item_size;
	const size_t index = bit_index / mem_t_size;
	const size_t bit_shift = bit_index % mem_t_size;

	mem_t ret = mem[index] >> bit_shift;
	if (bit_shift) ret |= mem[index + 1] << (mem_t_size - bit_shift);
	ret &= item_mask;
	return ret;
}
void bitmem::set(const size_t i, const mem_t val)
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
			((mem_t)val >> (mem_t_size - shift));
	}
}

std::string bitmem::str() const
{
	stringstream s;
	auto* buff = (unsigned const char*)mem;
	for (size_t i = mem_size * mem_t_size / 8 - 1; i >= 1; i--)
	{
		s << hex << setfill('0') << setw(2) << (int)buff[i] << '.';
	}
	s << hex << setfill('0') << setw(2) << (int)buff[0];
	return s.str();
}
std::string bitmem::order() const
{
	stringstream s;
	for (size_t i = mem_size * mem_t_size / 8 - 1; i >= 1; i--)
	{
		s << setfill('0') << setw(2) << i << '.';
	}
	s << hex << setfill('0') << setw(2) << 0;
	return s.str();
}
