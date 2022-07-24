attribute vec2 vertexCoord;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection * model * vec4(vertexCoord, 0, 1);
}
