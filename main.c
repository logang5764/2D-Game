#include <stdio.h>
#include "raylib.h"

// Screen dimensions
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 500

// Map size
#define ROWS 10
#define COLS 10

// Cell size based on dimension and size
#define CELL_WIDTH (SCREEN_WIDTH / COLS)
#define CELL_HEIGHT (SCREEN_HEIGHT / ROWS)


// Map
int map[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw map
        for (int y = 0; y < ROWS; y++)
        {
            for (int x = 0; x < COLS; x++)
            {
                // Position on drawing
                int posX = x * CELL_WIDTH;
                int posY = y * CELL_HEIGHT;

                Color tileColor;

                // Find colour
                if (map[y][x] == 1)
                {
                    tileColor = DARKGRAY;
                }
                else
                {
                    tileColor = BLACK;
                };

                DrawRectangle(posX, posY, CELL_WIDTH, CELL_HEIGHT, tileColor);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}