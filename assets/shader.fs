#version 100
precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform float time;
uniform int frameCount;

const float resolutionX = 1920.;
const float resolutionY = 1080.;

vec4 color = vec4(0);

float random(in float seed) {
    return fract(sin(seed) * 43758.5453123);
}

void main()
{
    if (fragColor.r > 0.5) {
        color = vec4(
                random(time + fragTexCoord.x * resolutionX + fragTexCoord.y),
                random(time + fragTexCoord.x * resolutionX + fragTexCoord.y + 1.),
                random(time + fragTexCoord.x * resolutionX + fragTexCoord.y + 2.),
                1.
            );
        // color = vec4(0., 0., 1., 1.);
    } else {
        color = vec4(0., 0., 0., 1.);
    }
    gl_FragColor = color;
}
