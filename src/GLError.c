/*
** EPITECH PROJECT, 2018
** gpu-intro
** File description:
** GLError
*/

#include "demo.h"

void GLClearError(void)
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line)
{
	GLenum error = glGetError();
	bool ret = true;

	while (error != GL_NO_ERROR) {
		ret = false;
		dprintf(2, "[OpenGL Error]: %u => '%s' in %s (%s:%d)\n", error,
			glewGetErrorString(error), function, file, line);
		error = glGetError();
	}
	return ret;
}
