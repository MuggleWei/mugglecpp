#include "ring_buffer.h"
#include <stdexcept>
#include "muggle/c/log/log.h"

NS_MUGGLE_BEGIN

RingBuffer::RingBuffer(uint32_t capacity, int flags)
{
	if (muggle_ring_buffer_init(&ring_buf_, (muggle_atomic_int)capacity, flags) != 0)
	{
		throw std::runtime_error("failed init ring buffer");
	}
}

RingBuffer::~RingBuffer()
{
	muggle_ring_buffer_destroy(&ring_buf_);
}

int RingBuffer::write(void *data)
{
	return muggle_ring_buffer_write(&ring_buf_, data);
}

void* RingBuffer::read(muggle_atomic_int idx)
{
	return muggle_ring_buffer_read(&ring_buf_, idx);
}

NS_MUGGLE_END
