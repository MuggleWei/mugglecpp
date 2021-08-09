#include "ring_buffer.h"
#include <stdexcept>

NS_MUGGLE_BEGIN

RingBuffer::RingBuffer(uint32_t capacity, int flags)
	: cursor_(0)
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

int RingBuffer::push(void *data)
{
	return muggle_ring_buffer_write(&ring_buf_, data);
}

void* RingBuffer::read()
{
	// muggle_atomic_int cursor = muggle_atomic_fetch_add(&cursor_, 1, muggle_memory_order_relaxed);
	// every thread read all data
	return muggle_ring_buffer_read(&ring_buf_, cursor_++);
}

NS_MUGGLE_END
