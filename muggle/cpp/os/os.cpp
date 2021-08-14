#include "os.h"
#include "muggle/c/os/os.h"

NS_MUGGLE_BEGIN


std::string Os::processPath()
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_os_process_path(buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Os::curdir()
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_os_curdir(buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

int Os::chdir(const char *path)
{
	return muggle_os_chdir(path);
}

int Os::mkdir(const char *path)
{
	return muggle_os_mkdir(path);
}

int Os::remove(const char *path)
{
	return muggle_os_remove(path);
}

int Os::rmdir(const char *path)
{
	return muggle_os_rmdir(path);
}

int Os::rename(const char *src, const char *dst)
{
	return muggle_os_rename(src, dst);
}

NS_MUGGLE_END
