#version 120

uniform sampler2DRect tex0;
uniform float windowWidth;
uniform float windowHeight;

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/




void main()
{
	//vec4 basecolor = vec4(0.05,0.1,0.18,1.0);
	vec4 basecolor = vec4(0.05,0.2,0.3,1.0);

	float multiplier = 0.1;

	vec4 color = vec4(1.0, 0.0, 0.0, 0.0);

	color += 0.000229 * texture2DRect(tex0, vec2(4.0, 0.0));
	color.r = 1.0;
	color.g = 0.0;
	color.b = 1.0;
	color.a = 1.0;
    
	float r = gl_FragCoord.y / windowHeight*multiplier + basecolor.r;
	float g = basecolor.g;
	float b = gl_FragCoord.x / windowWidth*multiplier + basecolor.b;
	float a = 1.0;
	gl_FragColor = vec4(r, g, b, a);

    
    //gl_FragColor = color;
}