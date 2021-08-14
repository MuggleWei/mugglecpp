#include "dl.h"
#include "muggle/c/os/dl.h"

NS_MUGGLE_BEGIN

void* Dl::load(const char *path)
{
	return muggle_dl_load(path);
}

void* Dl::sym(void *handle, const char *symbol)
{
	return muggle_dl_sym(handle, symbol);
}

int Dl::close(void *handle)
{
	return muggle_dl_close(handle);
}

NS_MUGGLE_END
