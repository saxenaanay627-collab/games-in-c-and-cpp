#include "raylib.h"

void ping_pong(void)

{
    const int W = 1280, H = 800;
    const float paddleW = 20, paddleH = 100;
    const float ballR = 20;
    InitWindow(W, H, "ping pong");
    SetTargetFPS(60);
    float l_x = 10, l_y = H / 2.0f - paddleH / 2.0f;
    float r_x = W - 30, r_y = H / 2.0f - paddleH / 2.0f;
    float ball_x = W / 2.0f, ball_y = H / 2.0f;
    float ball_speed_x = 350.0f, ball_speed_y = 350.0f;
    int score_l = 0, score_r = 0;
    bool game_started = false;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (!game_started && IsKeyPressed(KEY_ENTER))
            game_started = true;
        if (game_started)
        {
            // Paddle input
            float paddleSpeed = 600.0f;
            if (IsKeyDown(KEY_W))
                l_y -= paddleSpeed * dt;
            if (IsKeyDown(KEY_S))
                l_y += paddleSpeed * dt;
            if (IsKeyDown(KEY_UP))
                r_y -= paddleSpeed * dt;
            if (IsKeyDown(KEY_DOWN))
                r_y += paddleSpeed * dt;
            // Clamp paddles
            if (l_y < 0)
                l_y = 0;
            if (l_y + paddleH > H)
                l_y = H - paddleH;
            if (r_y < 0)
                r_y = 0;
            if (r_y + paddleH > H)
                r_y = H - paddleH;
            // Move ball
            ball_x += ball_speed_x * dt;
            ball_y += ball_speed_y * dt;
            // Wall bounce (top/bottom)
            if (ball_y - ballR <= 0)
            {
                ball_y = ballR;
                ball_speed_y *= -1;
            }
            if (ball_y + ballR >= H)
            {
                ball_y = H - ballR;
                ball_speed_y *= -1;
            }
            // Paddle bounce + push-out (prevents double bounce)
            // Left paddle
            if (ball_speed_x < 0 &&
                ball_x - ballR <= l_x + paddleW &&
                ball_y >= l_y && ball_y <= l_y + paddleH)
            {
                ball_x = l_x + paddleW + ballR;
                ball_speed_x *= -1;
            }
            // Right paddle
            if (ball_speed_x > 0 &&
                ball_x + ballR >= r_x &&
                ball_y >= r_y && ball_y <= r_y + paddleH)
            {
                ball_x = r_x - ballR;
                ball_speed_x *= -1;
            }
            if (ball_x + ballR < 0)
            {
                score_r++;
                ball_x = W / 2.0f;
                ball_y = H / 2.0f;
                ball_speed_x = 350.0f;
                ball_speed_y = 350.0f;
            }
            if (ball_x - ballR > W)
            {
                score_l++;
                ball_x = W / 2.0f;
                ball_y = H / 2.0f;
                ball_speed_x = -350.0f;
                ball_speed_y = 350.0f;
            }
        }
        BeginDrawing();
        ClearBackground(DARKGREEN);
        DrawLine(W / 2, 0, W / 2, H, WHITE);
        DrawRectangle((int)l_x, (int)l_y, (int)paddleW, (int)paddleH, WHITE);
        DrawRectangle((int)r_x, (int)r_y, (int)paddleW, (int)paddleH, WHITE);
        DrawCircle((int)ball_x, (int)ball_y, ballR, WHITE);
        DrawText(TextFormat("%i", score_l), 300, 20, 50, WHITE);
        DrawText(TextFormat("%i", score_r), 980, 20, 50, WHITE);
        if (!game_started)
            DrawText("Press Enter to Start", W / 2 - 120, H / 2 - 10, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
}