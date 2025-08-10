#include <cstdio>
#if defined(PLATFORM_WEB)
#include "emscripten.h"
#endif
#include "main.h"
#include "raylib.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"
#define GLSL_VERSION 100

App app;
void render_loop() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  app.time += GetFrameTime();
  SetShaderValue(app.shader, app.time_loc, &app.time, SHADER_UNIFORM_FLOAT);

  BeginShaderMode(app.shader);
  DrawTexture(app.texture, 0, 0, WHITE);
  EndShaderMode();

  EndDrawing();
  return;
}

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  Texture2D texture = LoadTexture(ASSETS_PATH "test.png");
  app.texture = texture;
  app.shader = LoadShader(0, TextFormat(ASSETS_PATH "shader.fs", GLSL_VERSION));
  app.time_loc = GetShaderLocation(app.shader, "time");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(render_loop, 60, 1);
#else
  SetTargetFPS(120);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();

  return 0;
}
