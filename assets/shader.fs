#version 330

in vec4 fragColor;

uniform vec2 u_resolution;
uniform float time;

out vec4 finalColor;

float random(in float seed) {
    return fract(sin(seed) * 43758.5453123);
}

void main()
{
    if (fragColor.r > 0.8) {
        finalColor = vec4(random(time), random(time + 1.), random(time + 2.), 1.);
    } else {
        finalColor = vec4(0.0, 1.0, 0.0, 1.0);
    }
}
