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

	float vertices[] = {0, 0.5, -0.5, -0.5, 0.5, -0.5};
	float color[] = {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1};
	float val = 0, inc = 0.01;
	unsigned int vao, vbuffer, cbuffer, program;

	if (init(&win) == false)
		return 1;

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));

	GLCall(glGenBuffers(1, &vbuffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbuffer));
	GLCall(glBufferData(
		GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, true, 0, 0));

	GLCall(glGenBuffers(1, &cbuffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, cbuffer));
	GLCall(glBufferData(
		GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, true, 0, 0));

	program = compileProgramFromFile(
		"shaders/vertex.vs", "shaders/fragment.fs");
	GLCall(glUseProgram(program));

	GLCall(glBindAttribLocation(program, 0, "aPos"));
	GLCall(glBindAttribLocation(program, 1, "aColor"));

	while (glfwWindowShouldClose(win) == false) {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		val += inc;
		if (val >= 1)
			inc = -0.01;
		if (val <= -1)
			inc = 0.01;

		GLCall(glUniform1f(glGetUniformLocation(program, "uVal"), val));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		glfwSwapBuffers(win);
		handleEvents(win);
	}
	return 0;
}
