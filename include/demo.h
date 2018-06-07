/*
** EPITECH PROJECT, 2018
** gpu-intro
** File description:
** engine
*/

#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PTRCall(x)                                                            \
	if ((x) == 0) {                                                       \
		dprintf(2, "%s[%s:%d]: Pointer issue.", __FUNCTION__,         \
			__FILE__, __LINE__);                                  \
		exit(1);                                                      \
	}

#define GLCall(x)                                                             \
	GLClearError();                                                       \
	x;                                                                    \
	assert(GLLogCall(__FUNCTION__, __FILE__, __LINE__));

void GLClearError(void);
bool GLLogCall(const char *function, const char *file, int line);

unsigned int compileProgramFromFile(
	const char *vertexShaderPath, const char *fragmentShaderPath);
unsigned int compileProgramFromMemory(
	const char *vertexShaderSource, const char *fragmentShaderSource);
char *readFile(const char *path);
