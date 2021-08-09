#include "channel.h"
#include <stdexcept>

NS_MUGGLE_BEGIN

Channel::Channel(uint32_t capacity, int flags)
{
	if (muggle_channel_init(&channel_, capacity, flags) != 0)
	{
		throw std::runtime_error("failed init channel");
	}
}

Channel::~Channel()
{
	muggle_channel_destroy(&channel_);
}

int Channel::push(void *data)
{
	return muggle_channel_write(&channel_, data);
}

void* Channel::read()
{
	return muggle_channel_read(&channel_);
}

NS_MUGGLE_END
