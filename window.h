#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "vector.h"

typedef struct Window
{
	int width;
	int height;

	float delta;

	char *name;
	float *background;

	void (*start)();
	void (*update)();
	void (*on_change)(GLFWwindow *, int, int);
	void (*on_input)(GLFWwindow *, int, int, int, int);

	GLFWwindow *window;
} Window;

Window *createWindow(int width, int height, char *name)
{
	Window *window = (Window *) malloc(sizeof(Window));

	window->width = width;
	window->height = height;
	window->name = name;

	window->background = vec_vec4(0, 0, 0, 1);

	return window;
}

void window_init(Window *window)
{
	if(!glfwInit()) { free(window); printf("\033[31mGLFW cannot initialize\033m[0m\n"); }

	window->window = glfwCreateWindow(window->width, window->height, window->name, NULL, NULL);

	if(!window->window) { free(window); glfwTerminate(); printf("\033[31mCannot create window\033[0m\n"); }

	glfwMakeContextCurrent(window->window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}

void window_actions(Window *window, void (*start)(), void (*update)())
{
	window->start = start;
	window->update = update;

	(*(window->start))();

	float lastFrame = 0;

	while(!glfwWindowShouldClose(window->window)) 
	{
		window->delta = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		glClearColor(window->background[0], window->background[1], window->background[2], window->background[3]);

		glClear(GL_COLOR_BUFFER_BIT);

		(*(window->update))();

		glfwSwapBuffers(window->window);

		glfwPollEvents();
	}
}

void window_close(Window *window)
{
	glfwDestroyWindow(window->window);
	free(window);

	glfwTerminate();
}

void window_on_orientation_change(Window *window, void (*on_change)(GLFWwindow *, int, int))
{
	window->on_change = on_change;

	glfwSetFramebufferSizeCallback(window->window, window->on_change);
}

void window_update_size(Window *window)
{
	glfwGetFramebufferSize(window->window, &(window->width), &(window->height));
}

void window_on_keyboard_input(Window *window, void (*on_input)(GLFWwindow *, int, int, int, int))
{
	window->on_input = on_input;
	glfwSetKeyCallback(window->window, on_input);
}
