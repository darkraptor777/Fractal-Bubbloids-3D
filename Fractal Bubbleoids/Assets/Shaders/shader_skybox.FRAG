#version 440 core
out vec4 vertColour;

in vec3 textureCoordinate;

uniform samplerCube skybox;

void main()
{    
    vertColour = texture(skybox, textureCoordinate);
}