#include<raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include "tictactoe.h"
#include "snake_game.h"
#include "ping_pong.h"

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "Game Menu");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Select a Game:", 350, 200, 30, WHITE);
        DrawText("1. Tic Tac Toe", 350, 300, 20, WHITE);
        DrawText("2. Ping Pong", 350, 350, 20, WHITE);
        DrawText("3. Snake Game", 350, 400, 20, WHITE);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            if (mousePos.x >= 350 && mousePos.x <= 650)
            {
                if (mousePos.y >= 300 && mousePos.y <= 320)
                    tictactoe();
                else if (mousePos.y >= 350 && mousePos.y <= 370)
                    ping_pong();
                else if (mousePos.y >= 400 && mousePos.y <= 420)
                    snake_game();
            }
        }
    }
    CloseWindow();
    return 0;
}