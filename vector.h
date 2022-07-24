#pragma once

#include <cglm/vec4.h>
#include <cglm/vec3.h>
#include <cglm/vec2.h>

float *vec_vec4(float x, float y, float z, float w)
{
	float *vector = (float *) malloc(4 * sizeof(float));
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	vector[3] = w;

	return vector;
}

float *vec_vec3(float x, float y, float z)
{
	float *vector = (float *) malloc(3 * sizeof(float));
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;

	return vector;
}

float *vec_vec2(float x, float y)
{
	float *vector = (float *) malloc(2 * sizeof(float));
	vector[0] = x;
	vector[1] = y;

	return vector;
}
