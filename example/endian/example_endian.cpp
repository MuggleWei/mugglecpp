#include "muggle/cpp/muggle_cpp.h"

int main()
{
	muggle::Log::ComplicatedInit(LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG, nullptr);

	// u16
	uint16_t u16 = 0x0102;
	uint16_t u16_swap = muggle::Endian::Swap(u16);
	LOG_INFO("u16: 0x%04x -> 0x%04x", u16, u16_swap);

	u16 = 0xff00;
	u16_swap = muggle::Endian::Swap(u16);
	LOG_INFO("u16: 0x%04x -> 0x%04x", u16, u16_swap);

	// i16
	int16_t i16 = 0x0102;
	int16_t i16_swap = muggle::Endian::Swap(i16);
	LOG_INFO("i16: 0x%04x -> 0x%04x", *(uint16_t *)&i16,
			 *(uint16_t *)&i16_swap);

	i16 = 0xff00;
	i16_swap = muggle::Endian::Swap(i16);
	LOG_INFO("i16: 0x%04x -> 0x%04x", *(uint16_t *)&i16,
			 *(uint16_t *)&i16_swap);

	// u32
	uint32_t u32 = 0x01020304;
	uint32_t u32_swap = muggle::Endian::Swap(u32);
	LOG_INFO("u32: 0x%08x -> 0x%08x", u32, u32_swap);

	u32 = 0xff000000;
	u32_swap = muggle::Endian::Swap(u32);
	LOG_INFO("u32: 0x%08x -> 0x%08x", u32, u32_swap);

	// i32
	int32_t i32 = 0x01020304;
	int32_t i32_swap = muggle::Endian::Swap(i32);
	LOG_INFO("i32: 0x%08x -> 0x%08x", *(uint32_t *)&i32,
			 *(uint32_t *)&i32_swap);

	i32 = 0xff000000;
	i32_swap = muggle::Endian::Swap(i32);
	LOG_INFO("i32: 0x%08x -> 0x%08x", *(uint32_t *)&i32,
			 *(uint32_t *)&i32_swap);

	// u64
	uint64_t u64 = 0x0102030405060708;
	uint64_t u64_swap = muggle::Endian::Swap(u64);
	LOG_INFO("u64: 0x%016llx -> 0x%016llx", u64, u64_swap);

	u64 = 0xff00000000000000;
	u64_swap = muggle::Endian::Swap(u64);
	LOG_INFO("u64: 0x%016llx -> 0x%016llx", u64, u64_swap);

	// i64
	int64_t i64 = 0x0102030405060708;
	int64_t i64_swap = muggle::Endian::Swap(i64);
	LOG_INFO("i64: 0x%016llx -> 0x%016llx", *(uint64_t *)&i64,
			 *(uint64_t *)&i64_swap);

	i64 = 0xff00000000000000;
	i64_swap = muggle::Endian::Swap(i64);
	LOG_INFO("i64: 0x%016llx -> 0x%016llx", *(uint64_t *)&i64,
			 *(uint64_t *)&i64_swap);

	// float
	float f32 = 3.14;
	float f32_swap = muggle::Endian::Swap(f32);
	LOG_INFO("f32(%f): 0x%08x -> 0x%08x", f32, *(uint32_t *)&f32,
			 *(uint32_t *)&f32_swap);

	f32 = -3.14;
	f32_swap = muggle::Endian::Swap(f32);
	LOG_INFO("f32(%f): 0x%08x -> 0x%08x", f32, *(uint32_t *)&f32,
			 *(uint32_t *)&f32_swap);

	// double
	double f64 = 3.14;
	double f64_swap = muggle::Endian::Swap(f64);
	LOG_INFO("f64(%f): 0x%016llx -> 0x%016llx", f64, *(uint64_t *)&f64,
			 *(uint64_t *)&f64_swap);

	f64 = -3.14;
	f64_swap = muggle::Endian::Swap(f64);
	LOG_INFO("f64(%f): 0x%016llx -> 0x%016llx", f64, *(uint64_t *)&f64,
			 *(uint64_t *)&f64_swap);

	return 0;
}
