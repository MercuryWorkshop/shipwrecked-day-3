#include <cstdio>
#if defined(PLATFORM_WEB)
#include "emscripten.h"
#endif
#include "main.h"
#include "raylib.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Static Noise"
#define GLSL_VERSION 100

static bool enable_render = true;

extern "C" {
void set_enable_render_(bool enable) { enable_render = enable; }
}

App app;
void render_loop() {
  app.time += GetFrameTime();
  app.frame++;
  if (enable_render) {
    SetShaderValue(app.shader, app.time_loc, &app.time, SHADER_UNIFORM_FLOAT);
    SetShaderValue(app.shader, app.frame_loc, &app.frame, SHADER_UNIFORM_INT);

    BeginTextureMode(app.target);
    ClearBackground(BLACK);
    BeginMode3D(app.camera);
    DrawSphere({0, 1, 0}, 1, WHITE);
    // DrawPlane({0, 0, 0}, {100, 100}, BLACK);
    EndMode3D();
    EndTextureMode();

    BeginDrawing();
    ClearBackground(WHITE);

    BeginShaderMode(app.shader);
    DrawTextureRec(app.target.texture,
                   (Rectangle){0, 0, (float)app.target.texture.width,
                               (float)-app.target.texture.height},
                   (Vector2){0, 0}, WHITE);

    EndShaderMode();

    EndDrawing();
  }
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
  app.target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

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
