#version 100
precision mediump float;

uniform float time;

void main() {
    // Use time to create a color effect
    gl_FragColor = vec4(sin(time), cos(time), 0.5, 1.0);
}
