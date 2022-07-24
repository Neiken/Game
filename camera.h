#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rect.h"

typedef struct Camera
{
	int rects_amount;
	float zoom;
	mat4 projection;
	Rect **rects;
} Camera;

void camera_update_projection(Camera *camera, int width, int height)
{
	float ratio = (float) width / height;

	glm_ortho(-ratio * camera->zoom, ratio * camera->zoom, -1 * camera->zoom, 1 * camera->zoom, -1, 1, camera->projection);
}

Camera *camera_create(int width, int height)
{
	Camera *camera = (Camera *) malloc(sizeof(Camera));

	camera_update_projection(camera, width, height);

	camera->rects_amount = 0;
	camera->rects = (Rect **) malloc(0);
	
	camera->zoom = 5.f;

	return camera;
}

void camera_push_rect(Camera *camera, Rect *rect)
{
	Rect **old_rects = camera->rects;
	camera->rects = (Rect **) malloc((camera->rects_amount + 1) * sizeof(Rect *));

	for(int x = 0; x < camera->rects_amount; x++) { camera->rects[x] = old_rects[x]; }

	camera->rects[camera->rects_amount++] = rect;
}

void camera_show_vision(Camera *camera)
{
	for(int x = 0; x < camera->rects_amount; x++)
	{
		rect_draw(camera->rects[x], camera->projection);
	}
}
