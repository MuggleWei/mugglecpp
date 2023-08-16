#include "endian.h"
#include "muggle/c/os/endian.h"

NS_MUGGLE_BEGIN

void Endian::Swap(uint16_t &val)
{
	MUGGLE_ENDIAN_SWAP_16(val);
}

void Endian::Swap(uint32_t &val)
{
	MUGGLE_ENDIAN_SWAP_32(val);
}

void Endian::Swap(uint64_t &val)
{
	MUGGLE_ENDIAN_SWAP_64(val);
}

NS_MUGGLE_END
