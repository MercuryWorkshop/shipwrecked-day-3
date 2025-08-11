#version 100
precision mediump float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform float time;
uniform float mix_val;
uniform int bw;
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

float sdTorus( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}

float sdSphere( vec3 p, float s )
{
  return length(p)-s;
}

float sdBox( vec3 p, vec3 b )
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

float map( in vec3 pos )
{
    return mix(sdTorus(vec3(-pos.y, pos.x, pos.z), vec2(0.2, 0.04)), sdBox(pos, vec3(0.2)), mix_val);
}

void main()
{
    float an = 0.5*(time-10.0);
    vec3 ro = vec3( 0.7*cos(an), 0.7*cos(an), 0.7*sin(an) );
    vec3 ta = vec3( 0.0, 0.0, 0.0 );
    // camera matrix
    vec3 ww = normalize( ta - ro );
    vec3 uu = normalize( cross(ww,vec3(0.0,1.0,0.0) ) );
    vec3 vv = normalize( cross(uu,ww));


    vec3 tot = vec3(0.0);

    vec2 p = (-vec2(resolutionX, resolutionY) + 4.0*gl_FragCoord.xy)/resolutionY;

	    // create view ray
        vec3 rd = normalize( p.x*uu + p.y*vv + 1.5*ww );

  const float tmax = 5.0;
  float t = 0.0;
  for( int i=0; i<256; i++ )
  {
      vec3 pos = ro + t*rd;
      float h = map(pos);
      if( h<0.0001 || t>tmax ) break;
      t += h;
  }


    float seed = gl_FragCoord.x + fragTexCoord.y;
    if (t > tmax) {
        seed += float(mod(frameCount, 5000) * blinkRate);
    } else {
        seed -= float(mod(frameCount, 5000) * blinkRate);
    }
    color = noise(seed);
    if(bw == 1) {
        color = vec4(vec3(t), 1.0);
    }
    gl_FragColor = color;
}
