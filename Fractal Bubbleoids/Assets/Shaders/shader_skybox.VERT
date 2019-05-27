#version 440 core
layout (location = 0) in vec3 Position; //vertex positions

out vec3 textureCoordinate;

uniform mat4 projectionLocation;
uniform mat4 viewLocation;

void main()
{
    textureCoordinate = Position;
    gl_Position = projectionLocation * viewLocation * vec4(Position, 1.0);
} 