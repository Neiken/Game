#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

static char *readFile(char *);
static int makeShard(int, char *);

typedef struct Shader
{
	int vertexShader;
	int fragmentShader;
	int program;
} Shader;

Shader *shader_create(char *vertex_shader_source_path, char *fragment_shader_source_path)
{
	Shader *shader = (Shader *) malloc(sizeof(Shader));

	shader->vertexShader = makeShard(GL_VERTEX_SHADER, readFile(vertex_shader_source_path));
	shader->fragmentShader = makeShard(GL_FRAGMENT_SHADER, readFile(fragment_shader_source_path));

	if(shader->vertexShader == -1 || shader->fragmentShader == -1) { return (Shader *) NULL; }

	shader->program = glCreateProgram();
	glAttachShader(shader->program, shader->vertexShader);
	glAttachShader(shader->program, shader->fragmentShader);
	glLinkProgram(shader->program);

	int success;
	glGetProgramiv(shader->program, GL_LINK_STATUS, &success);

	if(!success)
	{
		int size;
		glGetProgramiv(shader->program, GL_INFO_LOG_LENGTH, &size);

		char log[size+1];
		glGetProgramInfoLog(shader->program, size+1, NULL, log);

		printf("\033[31mError while linking program: \n\n%s\n", log);
		
		glDeleteShader(shader->vertexShader);
		glDeleteShader(shader->fragmentShader);
		glDeleteProgram(shader->program);

		return (Shader *) NULL;
	}

	return shader;
}

static char *readFile(char *path)
{
	FILE *file = fopen(path, "r");

	if(!file) { printf("\033[31mUnexistent file '%s'\033[0m\n", path); return (char *) NULL; }

	fseek(file, 0, SEEK_END);
	unsigned size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *content = (char *) malloc((size+1) * sizeof(char));
	fread(content, size+1, sizeof(char), file);

	content[size] = '\0';

	return content;
}

static int makeShard(int type, char *src)
{
	int shader = glCreateShader(type);

	glShaderSource(shader, 1, (const char**) &src, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		int size;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

		char log[size+1];
		glGetShaderInfoLog(shader, size+1, NULL, log);

		log[size] = '\0';

		printf("\033[31mError:\n\n%s\n\n%s\n\033[0m", src, log);
		
		glDeleteShader(shader);
		return -1;
	}

	return shader;
}
