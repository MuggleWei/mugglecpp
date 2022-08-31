#include "bytes_buffer.h"
#include <stdexcept>

NS_MUGGLE_BEGIN

BytesBuffer::BytesBuffer(int capacity)
{
	if (!muggle_bytes_buffer_init(&bytes_buf_, capacity))
	{
		throw std::runtime_error("failed init bytes buffer");
	}
}
BytesBuffer::~BytesBuffer()
{
	muggle_bytes_buffer_destroy(&bytes_buf_);
}

int BytesBuffer::Writable()
{
	return muggle_bytes_buffer_writable(&bytes_buf_);
}

int BytesBuffer::Readable()
{
	return muggle_bytes_buffer_readable(&bytes_buf_);
}

int BytesBuffer::ContiguousReadable()
{
	return muggle_bytes_buffer_contiguous_readable(&bytes_buf_);
}

bool BytesBuffer::Fetch(int num_bytes, void *dst)
{
	return muggle_bytes_buffer_fetch(&bytes_buf_, num_bytes, dst);
}

bool BytesBuffer::Read(int num_bytes, void *dst)
{
	return muggle_bytes_buffer_read(&bytes_buf_, num_bytes, dst);
}

bool BytesBuffer::Write(int num_bytes, void *src)
{
	return muggle_bytes_buffer_write(&bytes_buf_, num_bytes, src);
}

void* BytesBuffer::WriterFc(int num_bytes)
{
	return muggle_bytes_buffer_writer_fc(&bytes_buf_, num_bytes);
}

bool BytesBuffer::WriterMove(int num_bytes)
{
	return muggle_bytes_buffer_writer_move(&bytes_buf_, num_bytes);
}

void* BytesBuffer::ReaderFc(int num_bytes)
{
	return muggle_bytes_buffer_reader_fc(&bytes_buf_, num_bytes);
}

bool BytesBuffer::ReaderMove(int num_bytes)
{
	return muggle_bytes_buffer_reader_move(&bytes_buf_, num_bytes);
}

void BytesBuffer::Clear()
{
	muggle_bytes_buffer_clear(&bytes_buf_);
}

NS_MUGGLE_END
