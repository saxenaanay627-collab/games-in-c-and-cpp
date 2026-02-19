#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#define maxSnakeLength 625

typedef struct {
    int x;
    int y;
} cell;

int border = 75;

void snake_game(void){
 
    int gridSize = 32;
    int gridcount = 25;
    int boardSize = gridSize * gridcount;

    int winW = boardSize + 2 * border;
    int winH = boardSize + 2 * border;

    InitWindow(winW, winH, "Snake Game");
    SetTargetFPS(8);

    Texture2D background = LoadTexture("background.png");
    Texture2D snakeTex = LoadTexture("snake.png");
    Texture2D foodTex  = LoadTexture("food.png");


    cell food = { GetRandomValue(0, gridcount - 1), GetRandomValue(0, gridcount - 1) };

    cell snake[maxSnakeLength];
    int snakeLength = 2;
    snake[0] = (cell){12, 12};
    snake[1] = (cell){11, 12};

    cell dir = (cell){1, 0};
    bool gameOver = false;

    int score = 0;

    while (!WindowShouldClose()) {

        if (!gameOver) {
            if (IsKeyPressed(KEY_RIGHT) && !(dir.x == -1 && dir.y == 0)) dir = (cell){ 1, 0};
            else if (IsKeyPressed(KEY_LEFT) && !(dir.x ==  1 && dir.y == 0)) dir = (cell){-1, 0};
            else if (IsKeyPressed(KEY_UP) && !(dir.x == 0 && dir.y ==  1)) dir = (cell){0, -1};
            else if (IsKeyPressed(KEY_DOWN) && !(dir.x == 0 && dir.y == -1)) dir = (cell){0,  1};

            for (int i = snakeLength - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }
            snake[0].x += dir.x;
            snake[0].y += dir.y;

            if (snake[0].x < 0 || snake[0].x >= gridcount || snake[0].y < 0 || snake[0].y >= gridcount) {
                gameOver = true;
            }

            for (int i = 1; i < snakeLength && !gameOver; i++) {
                if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                    gameOver = true;
                }
            }

            if (!gameOver && snake[0].x == food.x && snake[0].y == food.y) {
                if (snakeLength < maxSnakeLength) {
                    snake[snakeLength] = snake[snakeLength - 1];
                    snakeLength++;
                }
                score++;

                while (1) {
                    food.x = GetRandomValue(0, gridcount - 1);
                    food.y = GetRandomValue(0, gridcount - 1);

                    bool onSnake = false;
                    for (int i = 0; i < snakeLength; i++) {
                        if (snake[i].x == food.x && snake[i].y == food.y) { onSnake = true; break; }
                    }
                    if (!onSnake) break;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE); // frame (board rectangle) 
        DrawRectangleLines(border, border, boardSize, boardSize, WHITE);
        Rectangle foodSrc = {0,0,foodTex.width,foodTex.height};
Rectangle foodDest = {
    border + food.x * gridSize,
    border + food.y * gridSize,
    gridSize,
    gridSize
};

DrawTexturePro(foodTex, foodSrc, foodDest, (Vector2){0,0}, 0, WHITE);

        for(int i=0;i<snakeLength;i++){
            Rectangle snakeSrc = {0,0,snakeTex.width,snakeTex.height};

Rectangle snakeDest = {
    border + snake[i].x * gridSize,
    border + snake[i].y * gridSize,
    gridSize,
    gridSize
};

DrawTexturePro(snakeTex, snakeSrc, snakeDest, (Vector2){0,0}, 0, WHITE);

        }

        DrawText(TextFormat("Score: %d", score), border, 20, 24, WHITE);

        if (gameOver) {
            DrawText("Game Over!", winW / 2 - 80, winH / 2 - 10, 28, RED);
            DrawText("Press R to Restart", winW / 2 - 120, winH / 2 + 30, 20, WHITE);

            if (IsKeyPressed(KEY_R)) {
                snakeLength = 2;
                snake[0] = (cell){12,12};
                snake[1] = (cell){11,12};
                dir = (cell){1,0};
                score = 0;
                gameOver = false;
                food = (cell){ GetRandomValue(0, gridcount - 1), GetRandomValue(0, gridcount - 1) };
            }
        }

        EndDrawing();
    }

    UnloadTexture(background);   // ⭐ IMPORTANT
    CloseWindow();
}
