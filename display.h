#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Display
{
public:
	Display(const char* name, const int width, const int height) 
	: m_name(name), m_width(width), m_height(height)
	{}

	~Display()
	{
		close();
	}

	bool init();
	void close();

	void clear();
	void update();

	bool isRunning() const { return !glfwWindowShouldClose(m_window); }
	const char* getName() const { return m_name; }
	int getWidth() const { return m_width;  }
	int getHeight() const { return m_height; }
private:
	const char* m_name;
	const int m_width;
	const int m_height;

	GLFWwindow* m_window = nullptr;

};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
