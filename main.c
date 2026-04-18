#include <stdio.h>
#include "raylib.h"

// Screen dimensions
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

// Map size
#define ROWS 10
#define COLS 10

// Cell size
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

// --- FUNCTIONS ---
void DrawWorldMap(void) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int posX = x * CELL_WIDTH;
            int posY = y * CELL_HEIGHT;

            Color tileColor = (map[y][x] == 1) ? DARKGRAY : BLACK;

            DrawRectangle(posX, posY, CELL_WIDTH, CELL_HEIGHT, tileColor);
        }
    }
}

// --- MAIN ---
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            DrawWorldMap();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}