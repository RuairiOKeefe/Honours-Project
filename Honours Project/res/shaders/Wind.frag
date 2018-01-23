#version 440

uniform sampler2D tex;
uniform vec3 windVector;

// Incoming texture coordinate

// Outgoing fragment colour
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;

layout(location = 0) out vec4 colour;

void main()
{
	//colour = texture(tex, tex_coord);

	colour = max(dot(normal, windVector), 0) * vec4(1,0,0,1);
	if(colour.x < 1.0)
		colour.z = 1.0 - colour.x;
}