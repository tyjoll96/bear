$input v_color0, v_texcoord0

#include "../../vendor/bgfx/examples/common/common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 color = toLinear(texture2D(s_texColor, v_texcoord0));
	if (color.w < 0.5)
	{
		discard;
	}
	
	gl_FragColor = color;
}