/*
    Knight-Game
    version: kg-23151026
*/

#include <raylib.h>
#include <algorithm>
#include <vector>
#include <map>
#include <string>


class Character {
protected:
    Rectangle pushbox; //Хитбокс персонажа (относительно позиции игрока)
    Vector2 position; //позиция персонажа (левый верхний угол картинки)
    Texture2D image;
    int HP;
    int damage;
    float max_speed;
    float speed;
    float a; //Ускорение

    Character(Vector2 tex_pos, Vector2 push_pos, Vector2 push_size, Texture2D tex, int HP_, int damage_, float max_speed_, float speed_, float a_) {
        pushbox = {push_pos.x, push_pos.y, push_size.x, push_size.y};
        position = {tex_pos.x, tex_pos.y};
        image = tex;
        HP = HP_;
        damage = damage_;
        max_speed = max_speed_;
        speed = speed_;
        a = a_;
    }

public:
    virtual ~Character() = default;
    virtual void draw() = 0;
    virtual void draw_pushbox() = 0;
    virtual Rectangle get_current_pushbox() = 0;
    virtual void move() = 0;
    virtual Vector2 get_pos() const {
        return position;
    }
};

class Knight : public Character {
public:
    Knight(Vector2 tex_pos, Vector2 pos, Vector2 size, Texture2D tex, int HP_, int damage_, float max_speed_, float speed_, float a_) 
        : Character(tex_pos, pos, size, tex, HP_, damage_, max_speed_, speed_, a_) {}

    void move() override {
        if (IsKeyDown(KEY_RIGHT)) {
            if (speed >= 0) {
                speed = std::min(max_speed, speed + a * 2);
            } else {
                speed = 0;
            }
        } 
        if (IsKeyDown(KEY_LEFT)) {
            if (speed <= 0) {
                speed = std::max(max_speed * -1, speed - a * 2);
            } else {
                speed = 0;
            }
        } 
        if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) {
            if (speed > 0) {
                speed = std::max(0.0f, speed - a);
            } else if (speed < 0) {
                speed = std::min(0.0f, speed + a);
            }
        }
        position.x += speed;
    }

    void draw() override {
        DrawTexture(image, position.x, position.y, WHITE);
    }
    void draw_pushbox() override {
        DrawRectangleLinesEx(get_current_pushbox(), 1, RED);
    }
    Rectangle get_current_pushbox() override {
        return {pushbox.x + position.x, pushbox.y + position.y, pushbox.width, pushbox.height};
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Base window");
    Image window_icon24 = LoadImage("Window_icons/24.png");
    Image window_icon48 = LoadImage("Window_icons/48.png");
    Image window_icon96 = LoadImage("Window_icons/96.png");
    Image icons[3] = {window_icon24, window_icon48, window_icon96};
    SetWindowIcons(icons, 3);
    
    Camera2D camera = { 0 };
    camera.target = { 0.0f, 0.0f }; // Камера смотрит в начало координат (или на игрока)
    camera.offset = { 0.0f, 0.0f }; // Смещение камеры относительно экрана
    camera.rotation = 0.0f;
    camera.zoom = 1.0f; 
    const float targetRenderHeight = 80.0f;
    Texture2D icon_tex = LoadTexture("knight-for-tests.png");
    SetTextureFilter(icon_tex, TEXTURE_FILTER_POINT);

    Knight knight({2.0f, 2.0f}, {3.0f, 0.0f}, {10.0f, 23.0f}, icon_tex, 100, 10, 10.0, 0.0, 1.0);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        camera.zoom = (float)GetScreenHeight() / targetRenderHeight;
        BeginDrawing();
            ClearBackground(WHITE);
            knight.move();
            BeginMode2D(camera);
                knight.draw();
                knight.draw_pushbox();
            EndMode2D();
        EndDrawing();
    }

    UnloadTexture(icon_tex);
    CloseWindow();
    return 0;
}