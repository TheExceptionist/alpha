#pragma once

#include <string>

#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_CONTEXT_LOST 0x0507
#define GL_TABLE_TOO_LARGE 0x8031

enum
{
	ERROR_GL,
	ERROR_GLFW,
	ERROR_CPP
};


class ErrorChecker
{
public:
	static bool checkError(const int type = ERROR_CPP, const bool debug = false);
	static int getLastCode() { return m_last_code;  }
	static bool hasErrorOccured(const int type = ERROR_CPP) { checkError(type);  return m_last_code != 0; }
	static void printErrorInfo();
	static std::string getGLText(const int type);
private:
	ErrorChecker() {}

	static int m_last_code;
	static int m_last_type;
	static std::string m_error_text;
};

