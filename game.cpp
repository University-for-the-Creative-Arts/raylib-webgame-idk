#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Move the Square - raylib + C++");
    SetTargetFPS(60);

    // Square setup
    Rectangle player = { 100, 100, 50, 50 };
    float speed = 5.0f;

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyDown(KEY_RIGHT)) player.x += speed;
        if (IsKeyDown(KEY_LEFT)) player.x -= speed;
        if (IsKeyDown(KEY_DOWN)) player.y += speed;
        if (IsKeyDown(KEY_UP)) player.y -= speed;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Use arrow keys to move the square!", 10, 10, 20, DARKGRAY);
        DrawRectangleRec(player, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

