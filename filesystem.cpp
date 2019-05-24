#include "filesystem.h"

#include <iostream>
#include <algorithm>

std::string Filesystem::m_exe_dir;
std::string Filesystem::m_textures_dir = "textures\\";
std::string Filesystem::m_shaders_dir = "shaders\\";
std::string Filesystem::m_exe_name = "alpha.exe";

bool Filesystem::initDirectories()
{
#ifdef _WIN32
	WCHAR buffer[MAX_PATH];
	int bytes = GetModuleFileNameW(NULL, buffer, MAX_PATH);

	std::wstring buffer_str(buffer);
#endif

	std::string buffer_s(buffer_str.begin(), buffer_str.end());
	buffer_s.erase(buffer_s.length() - m_exe_name.length(), m_exe_name.length());
	m_exe_dir = buffer_s;

	std::string texture(m_exe_dir + "" + m_textures_dir);
	std::string shaders(m_exe_dir + "" + m_shaders_dir);

	std::replace(texture.begin(), texture.end(), '\\', '/');
	std::replace(shaders.begin(), shaders.end(), '\\', '/');

	m_textures_dir = texture;
	m_shaders_dir  = shaders;

	if (bytes == 0)
		return false;
	else
		return true;
}
