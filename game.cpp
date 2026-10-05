/*
    Knight-Game
    version: kg-01061026
*/

#include <raylib.h>
#include <algorithm>
#include <vector>
#include <map>
#include <string>


class Object {
protected:
    Rectangle hitbox; 
    Vector2 position;
    Vector2 hitbox_offset;
    Texture2D image;
    Object(Vector2 tex_pos, Vector2 pos, Vector2 size, Texture2D tex) {
        hitbox = {pos.x, pos.y, size.x, size.y};
        position = tex_pos;
        image = tex;
        hitbox_offset.x = pos.x - tex_pos.x;
        hitbox_offset.y = pos.y - tex_pos.y;
    }
public:
    virtual ~Object() = default;
    virtual void draw() = 0;
    virtual void draw_hitbox() = 0;
};

class Character : public Object {
protected:
    int HP;
    int damage;
    const float max_speed;
    float speed;
    float a; //Ускорение

    Character(Vector2 tex_pos, Vector2 pos, Vector2 size, Texture2D tex, int HP_, int damage_, float max_speed_, float speed_, float a_) 
        : Object(tex_pos, pos, size, tex), 
          HP(HP_), 
          damage(damage_), 
          max_speed(max_speed_),
          speed(speed_),
          a(a_) {}

public:
    virtual ~Character() = default;
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
        hitbox.x = position.x + hitbox_offset.x;
        hitbox.y = position.y + hitbox_offset.y;
    }

    void draw() override {
        DrawTexture(image, position.x, position.y, WHITE);
    }
    void draw_hitbox() override {
        DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RED);
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Base window");
    Image window_icon = LoadImage("icon.png");
    SetWindowIcon(window_icon);
    
    Camera2D camera = { 0 };
    camera.target = { 0.0f, 0.0f }; // Камера смотрит в начало координат (или на игрока)
    camera.offset = { 0.0f, 0.0f }; // Смещение камеры относительно экрана
    camera.rotation = 0.0f;
    camera.zoom = 1.0f; 
    const float targetRenderHeight = 720.0f;
    Texture2D icon_tex = LoadTextureFromImage(window_icon);
    SetTextureFilter(icon_tex, TEXTURE_FILTER_POINT);

    Knight knight({0.0, 0.0f}, {3.0f * 16.0f, 0.0f}, {10.0f * 16.0f, 23.0f * 16.0f}, icon_tex, 100, 10, 10.0, 0.0, 1.0);

    while (!WindowShouldClose()) {
        camera.zoom = (float)GetScreenHeight() / targetRenderHeight;
        BeginDrawing();
            ClearBackground(WHITE);
            knight.move();
            BeginMode2D(camera);
                knight.draw();
                knight.draw_hitbox();
            EndMode2D();
        EndDrawing();
    }

    UnloadTexture(icon_tex);
    CloseWindow();
    return 0;
}