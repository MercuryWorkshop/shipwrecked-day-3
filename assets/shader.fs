#version 100
precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform float time;
uniform int frameCount;

const float resolutionX = 1920.;
const float resolutionY = 1080.;
const int blinkRate = 5; // higher number = higher change

vec4 color = vec4(0., 0., 0., 1.);

float random(in float seed) {
    return fract(sin(seed) * 43758.5453123);
}

vec4 noise(in float seed) {
    return vec4(random(seed), random(seed + 10.), random(seed + 20.), 1.);
}

int mod(in int n, in int modulus) {
    return n - (modulus * (n / modulus));
}

void main()
{
    float seed = gl_FragCoord.x + fragTexCoord.y;
    if (distance(gl_FragCoord.xy, vec2(400., 250.)) > 100.) {
        seed += float(mod(frameCount, 5000) * blinkRate);
    }
    color = noise(seed);
    gl_FragColor = color;
}
