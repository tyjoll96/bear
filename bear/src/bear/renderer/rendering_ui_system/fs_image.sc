$input v_texcoord0

#include "../../../../vendor/bgfx/examples/common/common.sh"

SAMPLER2D(s_imageTex, 0);
uniform vec4 u_color;

void main()
{
	vec4 output = toLinear(texture2D(s_imageTex, v_texcoord0));
	output = output * u_color;
	gl_FragColor = output;
}