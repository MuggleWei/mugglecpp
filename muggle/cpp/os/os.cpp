#include "os.h"
#include "muggle/c/os/os.h"

NS_MUGGLE_BEGIN


std::string Os::ProcessPath()
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_os_process_path(buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Os::Curdir()
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_os_curdir(buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

int Os::Chdir(const char *path)
{
	return muggle_os_chdir(path);
}

int Os::Mkdir(const char *path)
{
	return muggle_os_mkdir(path);
}

int Os::Remove(const char *path)
{
	return muggle_os_remove(path);
}

int Os::Rmdir(const char *path)
{
	return muggle_os_rmdir(path);
}

int Os::Rename(const char *src, const char *dst)
{
	return muggle_os_rename(src, dst);
}

NS_MUGGLE_END
