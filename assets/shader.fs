#version 100
precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform float time;
uniform int frameCount;

const float resolutionX = 1920.;
const float resolutionY = 1080.;
const int blinkRate = 60; // higher number = slower change

vec4 color = vec4(1., 0., 0., 1.);

float random(in float seed) {
    return fract(sin(seed) * 43758.5453123);
}

vec4 noise(in float seed) {
    return vec4(random(seed), random(seed + 1.), random(seed + 2.), 1.);
}

void main()
{
    // if (fragColor.r > 0.5) {
    if (true) {
        color = noise(
                float(frameCount / blinkRate) +
                    fragTexCoord.x * resolutionX +
                    (fragTexCoord.y + float(frameCount / blinkRate))
            );
    }
    gl_FragColor = color;
}
