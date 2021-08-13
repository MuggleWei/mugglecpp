#include "path.h"
#include "muggle/c/os/path.h"

NS_MUGGLE_BEGIN

std::string Path::abs(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_abspath(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Path::basename(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_basename(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Path::dirname(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_dirname(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

bool Path::isAbs(const char *path)
{
	return muggle_path_isabs(path);
}

bool Path::exists(const char *path)
{
	return muggle_path_exists(path);
}

std::string Path::join(const char *path1, const char *path2)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_join(path1, path2, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Path::norm(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_normpath(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

NS_MUGGLE_END
