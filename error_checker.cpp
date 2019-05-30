#include "error_checker.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

int ErrorChecker::m_last_code = 0;
int ErrorChecker::m_last_type = 0;
std::string ErrorChecker::m_error_text = "";

using namespace std;

bool ErrorChecker::checkError(const int type, const bool debug)
{
	bool error_occured = false;
	m_last_type = type;

	switch (type)
	{
		case ERROR_GL:
		{
			if (debug) cout << "Checking for GL Error..." << endl;

			m_last_code = glGetError();
		}
		break;
		case ERROR_GLFW:
		{
			if (debug) cout << "Checking for GLFW Error..." << endl;

			const char* description;
			m_last_code = glfwGetError(&description);

			if (m_last_code != GLFW_NO_ERROR)
			{
				m_error_text = description;
			}
		}
		break;
		default:
		{
			if (debug) cout << "Checking for Cpp Error..." << endl;
			m_last_code = errno;
		}
	}

	error_occured = m_last_code ? true : false;
	return error_occured;
}

void ErrorChecker::printErrorInfo()
{
	if (m_last_code != NULL)
	{
		switch (m_last_type)
		{
			case ERROR_GL:
			{
				cout << "GL Error: " << getGLText(m_last_code) << endl;
			}
			break;
			case ERROR_GLFW:
			{

				cout << "GLFW Error:\n" << m_error_text << endl;
			}
			break;
			default:
			{
				cout << "Cpp Error: " << strerror(m_last_code) << endl;
			}
		}
	}
	else
	{
		cout << "No Error." << endl;
	}
}

std::string ErrorChecker::getGLText(const int type)
{
	switch (type)
	{
		case GL_INVALID_ENUM:
		{
			return "Enumeration parameter is not a legal enumeration for a function.";
		}
		case GL_INVALID_VALUE:
		{
			return "Value parameter is not a legal value for that function.";
		}
		case GL_INVALID_OPERATION:
		{
			return "Set of state for a command is not legal for the parameters given to that command.";
		}
		case GL_STACK_OVERFLOW:
		{
			return "Pushing operation cannot be done because it would overflow the limit of that stack's size.";
		}
		case GL_STACK_UNDERFLOW:
		{
			return "Popping operation cannot be done because the stack is already at its lowest point.";
		}
		case GL_OUT_OF_MEMORY:
		{
			return "Performing an operation that can allocate memory, and the memory cannot be allocated.";
		}
		case GL_INVALID_FRAMEBUFFER_OPERATION:
		{
			return "Read from or write/render to a framebuffer is not complete.";
		}
		case GL_CONTEXT_LOST:
		{
			return "Graphics card reset. Context lost!";
		}
		case GL_TABLE_TOO_LARGE:
		{
			return "ARB imageing error: Table too large.";
		}
	}

	return "Unknown Error.\nCode: " + type;
}
