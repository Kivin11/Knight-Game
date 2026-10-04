/*
    Knight-Game
    version: kg-17041026
*/

#include <raylib.h>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Base window");
    Image window_icon = LoadImage("icon.png");
    SetWindowIcon(window_icon);
    Texture2D icon_tex = LoadTextureFromImage(window_icon);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(icon_tex, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(icon_tex);
    UnloadImage(window_icon);
    CloseWindow();
    return 0;
}