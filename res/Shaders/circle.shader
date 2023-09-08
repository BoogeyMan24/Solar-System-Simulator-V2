#shader vertex
#version 410

layout (location = 0) in vec2 a_VertexPosition;
layout (location = 1) in vec2 a_Position;
layout (location = 2) in vec4 a_Color;
layout (location = 3) in float a_Radius;

out vec4 v_Color;
out float v_Radius;
out vec4 v_Position;
out vec2 v_Resolution;

uniform mat4 u_MVP;

void main()
{
	v_Color = a_Color;
	v_Radius = a_Radius;
	v_Position = u_MVP * vec4(a_Position, 0.0, 1.0);
	gl_Position = u_MVP * vec4(a_VertexPosition, 0.0, 1.0);
}



#shader fragment
#version 410

layout (location = 0) out vec4 o_Color;

uniform vec2 u_Resolution;
uniform float u_Zoom;

in vec4 v_Color;
in float v_Radius;
in vec4 v_Position;

void main()
{
	vec2 uv = (gl_FragCoord.xy / u_Resolution) - 1.0;
	float aspect = u_Resolution.x / u_Resolution.y;
	uv.x *= aspect;

	vec2 position;
	position = vec2(v_Position.x * aspect, v_Position.y);

	float distance = distance(u_Zoom * uv, u_Zoom * position);

	if (distance > v_Radius / u_Resolution.y) {
		discard;
	}

	o_Color = vec4(v_Color.rgb, v_Color.a);
}