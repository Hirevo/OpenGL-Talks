/*
** EPITECH PROJECT, 2018
** gpu-intro
** File description:
** main
*/

#include "demo.h"
#include <GLFW/glfw3.h>

bool init(GLFWwindow **win)
{
	if (glfwInit() == GLFW_FALSE) {
		dprintf(2, "glfwInit(): Couldn't initialize GLFW.\n");
		return false;
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	PTRCall(*win = glfwCreateWindow(1280, 720, "OpenGL Demo", 0, 0));
	glfwMakeContextCurrent(*win);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		dprintf(2, "glfwInit(): Couldn't initialize GLFW.\n");
		return false;
	}
	GLCall(glClearColor(0, 0, 0, 1));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_DEPTH_TEST));
	return true;
}

void handleEvents(GLFWwindow *win)
{
	(void)win;
	glfwPollEvents();
}

int main(void)
{
	GLFWwindow *win = 0;
	float val = 0.f;
	float inc = 0.01f;

	if (init(&win) == false)
		return 1;
	while (glfwWindowShouldClose(win) == false) {
		GLCall(glClearColor(val, val, val, 1));
		val += inc;
		if (val >= 1)
			inc = -0.01;
		if (val <= 0)
			inc = 0.01;

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glfwSwapBuffers(win);
		handleEvents(win);
	}
	return 0;
}
