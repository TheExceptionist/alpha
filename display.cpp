#include "display.h"

#include <iostream>

bool Display::init()
{
	bool success = true;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);

	if (m_window == NULL)
	{
		const char** error_description = nullptr;
		glfwGetError(error_description);

		std::cout << "GLFW coult not create a window!" << std::endl;
		std::cout << "GLFW Error Code: " << error_description << std::endl;

		success = false;
		close();
	}
	else
	{
		glfwMakeContextCurrent(m_window);
		glfwSetKeyCallback(m_window, key_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			success = false;
			close();
		}

		glViewport(0, 0, m_width, m_height);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	return success;
}

void Display::close()
{
	if (isRunning()) glfwSetWindowShouldClose(m_window, true);
	glfwTerminate();
}

void Display::clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{

}
