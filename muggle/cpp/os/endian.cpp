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

int16_t Endian::Swap(int16_t val)
{
	// NOTE: use unsigned integer to avoid of UB and implementation-defined
	uint16_t u16 = Endian::Swap(*(uint16_t*)&val);
	return *(int16_t*)&u16;
}

int32_t Endian::Swap(int32_t val)
{
	// NOTE: use unsigned integer to avoid of UB and implementation-defined
	uint32_t u32 = Endian::Swap(*(uint32_t*)&val);
	return *(int32_t*)&u32;
}

int64_t Endian::Swap(int64_t val)
{
	// NOTE: use unsigned integer to avoid of UB and implementation-defined
	uint64_t u64 = Endian::Swap(*(uint64_t*)&val);
	return *(int64_t*)&u64;
}

float Endian::Swap(float val)
{
	static_assert(sizeof(float) == sizeof(uint32_t),
				  "sizeof(float) != sizeof(uint32_t)");
	uint32_t u32 = *(uint32_t*)&val;
	u32 = MUGGLE_ENDIAN_SWAP_32(u32);
	return *(float*)&u32;
}

double Endian::Swap(double val)
{
	static_assert(sizeof(double) == sizeof(uint64_t),
				  "sizeof(double) != sizeof(uint64_t)");
	uint64_t u64 = *(uint64_t*)&val;
	u64 = MUGGLE_ENDIAN_SWAP_64(u64);
	return *(double*)&u64;
}

NS_MUGGLE_END
