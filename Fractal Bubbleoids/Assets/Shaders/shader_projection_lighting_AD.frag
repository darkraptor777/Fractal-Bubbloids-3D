#version 440 core
out vec4 vertColour;	//output colour of vertex
in vec2 textureCoordinate; //tex coords from vertex shader
in vec3 normals;
in vec3 fragmentPosition;
in vec3 lightColour;
in vec3 lightPosition;
in vec3 lampColour;
in vec3 lampPosition;
//in vec3 lightPositions; //use a matrix (3x3 matrix for example) matrix has to be a fixed size (so make one larger than you need and stop looping when you find empty members)


uniform sampler2D aTex;		//uniform holding texture info from main programme



void main()
{
	//dist calc
	float distance = sqrt( pow(lightPosition[0]-fragmentPosition[0],2) + pow(lightPosition[1]-fragmentPosition[1],2) + pow(lightPosition[2]-fragmentPosition[2],2) );
	float lampdistance = sqrt( pow(lampPosition[0]-fragmentPosition[0],2) + pow(lampPosition[1]-fragmentPosition[1],2) + pow(lampPosition[2]-fragmentPosition[2],2) );
	
	//ambient component
	//********************************
	//set the ambient coeff from material
	float lightAmbientStrength = 0.3f;
	vec3 objectAmbientReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambient = (lightAmbientStrength * objectAmbientReflectionCoeff) * lightColour;
	
	//diffuse component
	//********************************
	//normalise normal vectors (reset them as unit vectors)
	vec3 nNormal = normalize(normals);
	//calculate the light direction from the light position and the fragment position
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
	vec3 lampDirection = normalize(lampPosition - fragmentPosition);
	
	//determine the dot product of normal direction and light direction
	float diffuseStrength = max(dot(nNormal, lightDirection), 0.0f) * (1/pow(distance,2));
	float diffuseStrengthLamp = max(dot(nNormal, lampDirection), 0.0f) * (1/pow(lampdistance,2));
	
	//combine this with the light colour
	//set the diffuse coeff from material
	vec3 objectDiffuseReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
    vec3 diffuse = (diffuseStrength * objectDiffuseReflectionCoeff) * lightColour;
	vec3 diffuseLamp = (diffuseStrengthLamp * objectDiffuseReflectionCoeff) * lampColour;
	
	vec4 textureColour = texture(aTex, textureCoordinate);
	
	//apply no lighting, ambient and diffuse components with colour contributed by texture
	//vertColour = (vec4((lightColour), 1.0) * textureColour);
	//vertColour = (vec4((ambient),1.0) * textureColour);
	vertColour = (vec4((ambient+diffuse+diffuseLamp),1.0) * textureColour);
	
	
}