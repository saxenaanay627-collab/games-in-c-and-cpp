#include <raylib.h>
#include <stdio.h>

#define SCREEN_W 1000
#define SCREEN_H 1000

#define GRID_LEFT   100
#define GRID_TOP    100
#define GRID_RIGHT  900
#define GRID_BOTTOM 900

// Precomputed centers for your 3x3 cells (matches your old coordinates)
static const int CX[3] = {217, 500, 783};
static const int CY[3] = {217, 500, 783};

static void ResetGame(int board[3][3], bool *turn, int *winner, bool *gameOver)
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = 0;

    *turn = 0;       // 0 -> Player 1 (X), 1 -> Player 2 (O)
    *winner = 0;     // 0 none, 1 X, 2 O, 3 draw
    *gameOver = false;
}

static int CheckWinner(const int b[3][3])
{
    // rows + cols
    for (int i = 0; i < 3; i++)
    {
        if (b[i][0] != 0 && b[i][0] == b[i][1] && b[i][1] == b[i][2]) return b[i][0];
        if (b[0][i] != 0 && b[0][i] == b[1][i] && b[1][i] == b[2][i]) return b[0][i];
    }

    // diagonals
    if (b[0][0] != 0 && b[0][0] == b[1][1] && b[1][1] == b[2][2]) return b[0][0];
    if (b[0][2] != 0 && b[0][2] == b[1][1] && b[1][1] == b[2][0]) return b[0][2];

    // draw?
    int filled = 0;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (b[r][c] != 0) filled++;

    if (filled == 9) return 3; // draw
    return 0;                  // no winner yet
}

static bool MouseToCell(int mx, int my, int *row, int *col)
{
    if (mx < GRID_LEFT || mx > GRID_RIGHT || my < GRID_TOP || my > GRID_BOTTOM) return false;

    // Determine column by your line positions: 333 and 666
    if (mx < 333) *col = 0;
    else if (mx < 666) *col = 1;
    else *col = 2;

    // Determine row by your line positions: 333 and 666
    if (my < 333) *row = 0;
    else if (my < 666) *row = 1;
    else *row = 2;

    return true;
}

void tictactoe(void)

{
    InitWindow(SCREEN_W, SCREEN_H, "Tic Tac Toe");
    SetTargetFPS(60);

    int board[3][3];
    bool turn = 0;          // 0 = Player 1 (X), 1 = Player 2 (O)
    bool gameOver = false;
    int winner = 0;         // 0 none, 1 X, 2 O, 3 draw

    ResetGame(board, &turn, &winner, &gameOver);

    while (!WindowShouldClose())
    {
        // Restart
        if (IsKeyPressed(KEY_R))
        {
            ResetGame(board, &turn, &winner, &gameOver);
        }

        // Handle click -> place mark
        if (!gameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int mx = GetMouseX();
            int my = GetMouseY();

            int r, c;
            if (MouseToCell(mx, my, &r, &c))
            {
                if (board[r][c] == 0) // only place if empty
                {
                    board[r][c] = (turn == 0) ? 1 : 2; // 1=X, 2=O
                    winner = CheckWinner(board);
                    if (winner != 0) gameOver = true;
                    else turn = !turn;
                }
            }
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Grid
        DrawLine(333, 100, 333, 900, DARKBLUE);
        DrawLine(666, 100, 666, 900, DARKBLUE);
        DrawLine(100, 333, 900, 333, DARKBLUE);
        DrawLine(100, 666, 900, 666, DARKBLUE);

        // UI text
        DrawText("Tic Tac Toe", 450, 10, 20, WHITE);
        DrawText("Player 1: X", 100, 10, 20, WHITE);
        DrawText("Player 2: O", 800, 10, 20, WHITE);

        if (!gameOver)
        {
            if (!turn) DrawText("Player 1's turn", 450, 50, 20, WHITE);
            else       DrawText("Player 2's turn", 450, 50, 20, WHITE);
        }
        else
        {
            if (winner == 1) DrawText("X WINS!  (Press R to restart)", 360, 50, 20, WHITE);
            else if (winner == 2) DrawText("O WINS!  (Press R to restart)", 360, 50, 20, WHITE);
            else DrawText("DRAW!  (Press R to restart)", 380, 50, 20, WHITE);
        }

        // Draw marks
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if (board[r][c] == 1)
                {
                    DrawText("X", CX[c], CY[r], 150, DARKBLUE);
                }
                else if (board[r][c] == 2)
                {
                    DrawText("O", CX[c], CY[r], 150, DARKBLUE);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
