#version 100
precision mediump float;

// varying vec2 fragTexCoord;
varying vec4 fragColor;

// uniform vec2 u_resolution;
uniform float time;

vec4 color = vec4(0);

float random(in float seed) {
    return fract(sin(seed) * 43758.5453123);
}

void main()
{
    if (fragColor.r > 0.5) {
        color = vec4(random(time), random(time + 1.), random(time + 2.), 1.);
        // color = vec4(0., 0., 1., 1.);
    } else {
        color = vec4(0., 0., 0., 1.);
    }
    gl_FragColor = color;
}
