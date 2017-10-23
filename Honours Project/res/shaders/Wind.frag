#version 440

uniform sampler2D tex;
uniform vec3 windVector;

// Incoming texture coordinate
layout(location = 0) in vec2 tex_coord;
// Outgoing fragment colour
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 0) out vec4 colour;

void main()
{
	//colour = texture(tex, tex_coord);
	
	//windVector = dot((windVector, normal) 0.0);
	colour = vec4(windVector.x, windVector.y, windVector.z, 1.0f);
}