#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;

uniform mat4 View;
uniform mat4 Projection;

out vec4 ShapeColor;

void main()
{
	gl_Position = Projection * View * vec4(Position, 1.0f);
	ShapeColor = Color;
}
