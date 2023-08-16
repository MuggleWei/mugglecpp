#include "muggle/cpp/muggle_cpp.h"

int main() {
  muggle::Log::ComplicatedInit(LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG, nullptr);

  uint16_t u16 = 0x01;
  uint16_t u16_swap = muggle::Endian::Swap(u16);
  uint16_t u16_ret = muggle::Endian::Swap(u16_swap);

  uint32_t u32 = 0x01;
  uint32_t u32_swap = muggle::Endian::Swap(u32);
  uint32_t u32_ret = muggle::Endian::Swap(u32_swap);

  uint64_t u64 = 0x01;
  uint64_t u64_swap = muggle::Endian::Swap(u64);
  uint64_t u64_ret = muggle::Endian::Swap(u64_swap);

  LOG_INFO("u16: %u -> %u -> %u", (unsigned int)u16, (unsigned int)u16_swap,
           (unsigned int)u16_ret);
  LOG_INFO("u32: %u -> %u -> %u", (unsigned int)u32, (unsigned int)u32_swap,
           (unsigned int)u32_ret);
  LOG_INFO("u64: %llu -> %llu -> %llu", (unsigned long long)u64,
           (unsigned long long)u64_swap, (unsigned long long)u64_ret);

  return 0;
}
