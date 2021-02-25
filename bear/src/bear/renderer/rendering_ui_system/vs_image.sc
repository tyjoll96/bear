$input a_position, a_texcoord0
$output v_texcoord0

#include "../../../../vendor/bgfx/examples/common/common.sh"

uniform mat4 u_fill;

void main()
{
	gl_Position = mul(u_fill, vec4(a_position, 1.0));
	gl_Position = mul(u_modelViewProj, gl_Position);

	v_texcoord0 = a_texcoord0;
}