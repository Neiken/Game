#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include "window.h"
#include "rect.h"
#include "camera.h"
#include "vector.h"

Window *window;

void start();
void update();
void on_change(GLFWwindow *, int, int);
void on_input(GLFWwindow *, int, int, int, int);

int main()
{
	
	window = createWindow(1000, 700, "Game");
	window_init(window);

	window_on_orientation_change(window, on_change);

	window_on_keyboard_input(window, on_input);

	window_actions(window, start, update);

	window_close(window);

	return 0;
}

Rect *rect;
Camera *camera;

float player_speed = 2;

int KEY_A = 0;
int KEY_D = 0;
int KEY_W = 0;
int KEY_S = 0;

void start()
{
	camera = camera_create(window->width, window->height);
	rect = rect_create();

	camera_push_rect(camera, rect);
}

void update()
{
	camera_update_projection(camera, window->width, window->height);

	camera_show_vision(camera);

	rect->position[0] += player_speed * window->delta * (KEY_A ? -1 : (KEY_D ? 1 : 0));
	rect->position[1] += player_speed * window->delta * (KEY_S ? -1 : (KEY_W ? 1 : 0));
}

void on_change(GLFWwindow *win, int width, int height)
{
	glViewport(0, 0, width, height);

	window_update_size(window);	
}

void on_input(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	switch(key)
	{
		case GLFW_KEY_A:
			KEY_A = action != GLFW_RELEASE;
			break;

		case GLFW_KEY_D:
			KEY_D = action != GLFW_RELEASE;
			break;

		case GLFW_KEY_S:
			KEY_S = action != GLFW_RELEASE;
			break;
			
		case GLFW_KEY_W:
			KEY_W = action != GLFW_RELEASE;
			break;
	}
}
