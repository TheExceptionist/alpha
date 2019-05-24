#pragma once

#include <string>

#ifdef _WIN32
	#include <windows.h>
#endif

class Filesystem
{
public:
	static bool initDirectories();

	static std::string getExeDir() { return m_exe_dir; }
	static std::string getTextureDir() { return m_textures_dir; }
	static std::string getShadersDir() { return m_shaders_dir; }
private:
	Filesystem() {}

	static std::string m_exe_dir;
	static std::string m_exe_name;
	static std::string m_textures_dir;
	static std::string m_shaders_dir;
};

