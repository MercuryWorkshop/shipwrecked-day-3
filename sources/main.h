#pragma once
#include "raylib.h"
struct App {
  Texture2D texture;
  Shader shader;
  int time_loc;
  float time = 0;
};
