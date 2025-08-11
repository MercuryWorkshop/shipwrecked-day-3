#pragma once
#include "raylib.h"
struct App {
  Texture2D texture;
  Shader shader;
  int time_loc;
  int frame_loc;
  float time = 0;
  float mix = 0;
  int mix_loc;
  int frame = 0;
  Camera camera;
  RenderTexture2D target;
};
