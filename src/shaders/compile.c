/*
** EPITECH PROJECT, 2018
** gpu-intro
** File description:
** compile
*/

#include "demo.h"
#include <fcntl.h>
#include <string.h>

char *readFile(const char *path)
{
	int fd = open(path, O_RDONLY);
	char *contents = 0;
	char buffer[2048] = {0};
	ssize_t bytes = 1;

	if (fd == -1)
		return 0;
	PTRCall(contents = strdup(""));
	bytes = read(fd, buffer, 2048);
	while (bytes > 0) {
		buffer[bytes] = 0;
		PTRCall(contents = (char *)realloc(contents,
				sizeof(char) *
					(strlen(contents) + strlen(buffer) +
						1)));
		strcat(contents, buffer);
		bytes = read(fd, buffer, 2048);
	}
	if (bytes == -1) {
		free(contents);
		contents = 0;
	}
	return contents;
}

unsigned int compileProgramFromFile(
	const char *vertexShaderPath, const char *fragmentShaderPath)
{
	char *vertexShaderSource;
	char *fragmentShaderSource;
	unsigned int program;

	PTRCall(vertexShaderSource = readFile(vertexShaderPath));
	PTRCall(fragmentShaderSource = readFile(fragmentShaderPath));
	program = compileProgramFromMemory(
		vertexShaderSource, fragmentShaderSource);
	free(vertexShaderSource);
	free(fragmentShaderSource);
	return program;
}

unsigned int compileProgramFromMemory(
	const char *vertexShaderSource, const char *fragmentShaderSource)
{
	GLCall(unsigned int program = glCreateProgram());
	GLCall(unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER));
	GLCall(unsigned int fragmentShader =
			glCreateShader(GL_FRAGMENT_SHADER));
	int vlen = strlen(vertexShaderSource);
	int flen = strlen(fragmentShaderSource);
	char buffer[2048];
	int status;

	GLCall(glShaderSource(vertexShader, 1, &vertexShaderSource, &vlen));
	GLCall(glShaderSource(
		fragmentShader, 1, &fragmentShaderSource, &flen));

	GLCall(glCompileShader(vertexShader));
	GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status));
	if (status == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 2048, 0, buffer);
		dprintf(2, "[Vertex Shader] Compile Error: %s\n", buffer);
		return 0;
	}
	GLCall(glCompileShader(fragmentShader));
	GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status));
	if (status == GL_FALSE) {
		glGetShaderInfoLog(fragmentShader, 2048, 0, buffer);
		dprintf(2, "[Fragment Shader] Compile Error: %s\n", buffer);
		return 0;
	}

	GLCall(glAttachShader(program, vertexShader));
	GLCall(glAttachShader(program, fragmentShader));

	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
	GLCall(glGetProgramiv(program, GL_VALIDATE_STATUS, &status));
	if (status == GL_FALSE) {
		glGetProgramInfoLog(program, 2048, 0, buffer);
		dprintf(2, "[Program] Linking Error: %s\n", buffer);
		return 0;
	}

	GLCall(glDetachShader(program, vertexShader));
	GLCall(glDetachShader(program, fragmentShader));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));
	return program;
}
