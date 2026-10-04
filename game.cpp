/*
    Knight-Game
    version: kg-00051026
*/

#include <raylib.h>

int main() {
    Vector2 knight_pos = {0.0f, 0.0f};
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Base window");
    Image window_icon = LoadImage("icon.png");
    SetWindowIcon(window_icon);
    Texture2D icon_tex = LoadTextureFromImage(window_icon);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            if (IsKeyDown(KEY_RIGHT)) {
                knight_pos.x += 7.5;
            } 
            if (IsKeyDown(KEY_LEFT)) {
                knight_pos.x -= 7.5;
            }
            DrawTexture(icon_tex, knight_pos.x, knight_pos.y, WHITE);
        EndDrawing();
    }

    UnloadTexture(icon_tex);
    UnloadImage(window_icon);
    CloseWindow();
    return 0;
}