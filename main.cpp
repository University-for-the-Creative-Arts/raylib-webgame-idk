#include "raylib.h"
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

// Game states
enum GameState { STATE_START, STATE_PLAYING, STATE_END };

// Returns a random joke from the list
std::string GetRandomJoke()
{
    std::vector<std::string> jokes = {
        "Why did the computer go to therapy? It had a hard drive.",
        "Why do programmers prefer dark mode? Because light attracts bugs.",
        "There are 10 types of people: those who understand binary and those who don’t.",
        "What do you call 8 hobbits? A hobbyte.",
        "Debugging is like being the detective in a crime movie where you are also the murderer."
    };

    int index = rand() % jokes.size();
    return jokes[index];
}

int main()
{
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize Raylib window
    InitWindow(800, 450, "Joke Runner (No Bash / No API)");
    SetTargetFPS(60);

    // Game variables
    GameState currentState = STATE_START;
    std::string jokeText = GetRandomJoke();

    Rectangle player = { 100, 350, 50, 50 };
    float playerSpeed = 5.0f;

    float timePlayed = 0.0f;
    const float gameDuration = 10.0f;

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState)
        {
        case STATE_START:
            DrawText("JOKE RUNNER", 280, 40, 30, DARKBLUE);
            DrawText("Joke of the Day:", 100, 120, 20, GRAY);
            DrawText(jokeText.c_str(), 100, 160, 20, DARKGRAY);
            DrawText("Press [SPACE] to start", 260, 400, 20, DARKGREEN);

            if (IsKeyPressed(KEY_SPACE))
            {
                currentState = STATE_PLAYING;
                timePlayed = 0.0f;
            }
            break;

        case STATE_PLAYING:
            // Player movement
            if (IsKeyDown(KEY_RIGHT)) player.x += playerSpeed;
            if (IsKeyDown(KEY_LEFT))  player.x -= playerSpeed;

            // Clamp to screen bounds
            if (player.x < 0) player.x = 0;
            if (player.x > GetScreenWidth() - player.width)
                player.x = GetScreenWidth() - player.width;

            // Update timer
            timePlayed += GetFrameTime();
            if (timePlayed >= gameDuration)
            {
                currentState = STATE_END;
            }

            DrawText("Use arrow keys to move!", 240, 20, 20, DARKGRAY);
            DrawRectangleRec(player, SKYBLUE);
            break;

        case STATE_END:
            DrawText("GAME OVER", 320, 180, 30, MAROON);
            DrawText(TextFormat("You survived %.1f seconds!", timePlayed), 250, 230, 20, DARKGRAY);
            DrawText("Press [R] to restart", 280, 300, 20, DARKGREEN);

            if (IsKeyPressed(KEY_R))
            {
                currentState = STATE_START;
                jokeText = GetRandomJoke();
                player.x = 100;
            }
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
