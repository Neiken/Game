#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "shaders.h"
#include "vector.h"

typedef struct Rect
{
	unsigned vbo;
	unsigned vao;

	float rotation;

	float *color;

	vec2 position;
	vec2 scale;
	vec3 rotationAxis;

	Shader *shader;
} Rect;

Rect *rect_create()
{
	Rect *rect = (Rect *) malloc(sizeof(Rect));

	rect->shader = shader_create("glsl/rectVertexShader.glsl", "glsl/rectFragmentShader.glsl");

	float vertexs[] =
	{
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,

		0.5f, -0.5f,
		-0.5f, -0.5f,
		-0.5f, 0.5f
	};

	rect->color = vec_vec4(1, 1, 1, 1);

	rect->scale[0] = 1;
	rect->scale[1] = 1;

	rect->rotationAxis[2] = 1;

	glGenBuffers(1, &(rect->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, rect->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &(rect->vao));
	glBindVertexArray(rect->vao);

	int vertex_coord_location = glGetAttribLocation(rect->shader->program, "vertexCoord");
	glVertexAttribPointer(vertex_coord_location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(vertex_coord_location);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return rect;
}

void rect_draw(Rect *rect, mat4 projection)
{
	glUseProgram(rect->shader->program);

	glBindVertexArray(rect->vao);
	
	int location = glGetUniformLocation(rect->shader->program, "projection");
	glUniformMatrix4fv(location, 1, false, (const float *) projection);

	location = glGetUniformLocation(rect->shader->program, "color");
	glUniform4fv(location, 1, (const float *) rect->color);

	mat4 position;
	glm_translate_make(position, rect->position);

	mat4 rotation;
	glm_rotate_make(rotation, rect->rotation, rect->rotationAxis);

	mat4 scale;
	glm_scale_make(scale, rect->scale);

	mat4 model;
	glm_mat4_mul(scale, rotation, model);
	glm_mat4_mul(model, position, model);

	location = glGetUniformLocation(rect->shader->program, "model");
	glUniformMatrix4fv(location, 1, false, (const float *) model);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glBindVertexArray(0);
}
