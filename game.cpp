/*
    Knight-Game
    version: kg-18051026
*/

#include <raylib.h>
#include <algorithm>

class Character {
protected:
    int HP;
    int damage;
    const float max_speed;
    float speed;
    float a; //Ускорение
    Vector2 position;

    Character(int HP_, int damage_, float max_speed_, float speed_, float a_, Vector2 postion_) 
        : HP(HP_), 
        damage(damage_), 
        max_speed(max_speed_),
        speed(speed_),
        a(a_),
        position(postion_) {}

public:
    virtual ~Character() = default;
    virtual void move() = 0;
    virtual Vector2 get_pos() const {
        return position;
    }
};

class Knight : public Character {
public:
    Knight(int HP_, int damage_, float max_speed_, float speed_, float a_, Vector2 postion_) : Character(HP_, damage_, max_speed_, speed_, a_, postion_) {}

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
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Base window");
    Image window_icon = LoadImage("icon.png");
    SetWindowIcon(window_icon);
    Texture2D icon_tex = LoadTextureFromImage(window_icon);

    Knight knight(100, 10, 10.0, 0.0, 1.0, {0.0f, 0.0f});

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            knight.move();
            DrawTextureV(icon_tex, knight.get_pos(), WHITE);
        EndDrawing();
    }

    UnloadTexture(icon_tex);
    CloseWindow();
    return 0;
}