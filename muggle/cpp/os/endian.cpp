#include "endian.h"
#include "muggle/c/os/endian.h"

NS_MUGGLE_BEGIN

uint16_t Endian::Swap(uint16_t val)
{
	return MUGGLE_ENDIAN_SWAP_16(val);
}

uint32_t Endian::Swap(uint32_t val)
{
	return MUGGLE_ENDIAN_SWAP_32(val);
}

uint64_t Endian::Swap(uint64_t val)
{
	return MUGGLE_ENDIAN_SWAP_64(val);
}

NS_MUGGLE_END
