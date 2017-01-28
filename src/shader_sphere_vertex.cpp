#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec4 Color;

out vec3 FragPos;
out vec3 SurfaceNormal;
out vec4 ObjectColor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(Position, 1.0f);
	FragPos = vec3(Model * vec4(Position, 1.0f));
	SurfaceNormal = mat3(Model) * Normal;
	ObjectColor = Color;
}
