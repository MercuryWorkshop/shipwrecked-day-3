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
  app.frame++;
  SetShaderValue(app.shader, app.time_loc, &app.time, SHADER_UNIFORM_FLOAT);
  SetShaderValue(app.shader, app.frame_loc, &app.frame, SHADER_UNIFORM_INT);

  BeginMode3D(app.camera);
  BeginShaderMode(app.shader);

  DrawSphere({0, 0, 0}, 1, BLACK);
  DrawTextureRec(
      app.texture,
      (Rectangle){0, 0, (float)app.texture.width, (float)-app.texture.height},
      (Vector2){0, 0}, WHITE);

  EndShaderMode();
  EndMode3D();

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
  app.frame_loc = GetShaderLocation(app.shader, "frameCount");
  app.camera = {};
  app.camera.position = (Vector3){0, 4.0f, 4.0f};
  app.camera.target = (Vector3){0.0f, 1.0f, -1.0f};
  app.camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  app.camera.fovy = 45.0f;
  app.camera.projection = CAMERA_PERSPECTIVE;

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(render_loop, 0, 1);
#else
  SetTargetFPS(120);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();

  return 0;
}
