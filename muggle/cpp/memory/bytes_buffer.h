/******************************************************************************
 *  @file         bytes_buffer.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2022-08-31
 *  @copyright    Copyright 2022 Muggle Wei
 *  @license      MIT License
 *  @brief        mugglecpp bytes buffer
 *****************************************************************************/

#ifndef MUGGLE_CPP_BYTES_BUFFER_H_
#define MUGGLE_CPP_BYTES_BUFFER_H_

#include "muggle/cpp/base/macro.h"
#include "muggle/c/memory/bytes_buffer.h"

NS_MUGGLE_BEGIN

class BytesBuffer
{
public:
	MUGGLE_CPP_EXPORT
	BytesBuffer(int capacity);
	MUGGLE_CPP_EXPORT
	virtual ~BytesBuffer();

	MUGGLE_CPP_EXPORT
	int Writable();

	MUGGLE_CPP_EXPORT
	int Readable();

	MUGGLE_CPP_EXPORT
	int ContiguousReadable();

	MUGGLE_CPP_EXPORT
	bool Fetch(int num_bytes, void *dst);

	MUGGLE_CPP_EXPORT
	bool Read(int num_bytes, void *dst);

	MUGGLE_CPP_EXPORT
	bool Write(int num_bytes, void *src);

	MUGGLE_CPP_EXPORT
	void* WriterFc(int num_bytes);

	MUGGLE_CPP_EXPORT
	bool WriterMove(int num_bytes);

	MUGGLE_CPP_EXPORT
	void* ReaderFc(int num_bytes);

	MUGGLE_CPP_EXPORT
	bool ReaderMove(int num_bytes);

	MUGGLE_CPP_EXPORT
	void Clear();

private:
	muggle_bytes_buffer_t bytes_buf_;
};

NS_MUGGLE_END

#endif // !MUGGLE_CPP_BYTES_BUFFER_H_
