#include "path.h"
#include "muggle/c/os/path.h"

NS_MUGGLE_BEGIN

std::string Path::Abs(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_abspath(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Path::Basename(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_basename(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Path::Dirname(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_dirname(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

bool Path::IsAbs(const char *path)
{
	return muggle_path_isabs(path);
}

bool Path::Exists(const char *path)
{
	return muggle_path_exists(path);
}

std::string Path::Join(const char *path1, const char *path2)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_join(path1, path2, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

std::string Path::Norm(const char *path)
{
	char buf[MUGGLE_MAX_PATH];
	if (muggle_path_normpath(path, buf, sizeof(buf)) != 0)
	{
		return "";
	}
	return buf;
}

NS_MUGGLE_END
