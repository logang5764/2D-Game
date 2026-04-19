#include <stdio.h>
#include <math.h> 
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

// Player Structure
typedef struct Player {
    Vector2 position;
    float angle;      
    float speed;
    float turnSpeed;
} Player;

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

void UpdatePlayer(Player *p) {
    float deltaTime = GetFrameTime();

    // Turning controls
    if (IsKeyDown(KEY_LEFT))  p->angle -= p->turnSpeed * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) p->angle += p->turnSpeed * deltaTime;

    // Movement step calculation
    float moveStep = 0;
    if (IsKeyDown(KEY_UP)) moveStep = p->speed * deltaTime;
    if (IsKeyDown(KEY_DOWN)) moveStep = -p->speed * deltaTime;

    // Update position
    p->position.x += cosf(p->angle) * moveStep;
    p->position.y += sinf(p->angle) * moveStep;
}

void DrawPlayer(Player p) {
    DrawCircleV(p.position, 8, RED);
    
    // Draw direction line
    Vector2 dirEnd = {
        p.position.x + cosf(p.angle) * 30,
        p.position.y + sinf(p.angle) * 30
    };
    DrawLineV(p.position, dirEnd, YELLOW);
}

// --- MAIN ---
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map");
    
    // Initialize player
    Player player = {
        .position = (Vector2){ 150, 150 },
        .angle = 0.0f,
        .speed = 200.0f,
        .turnSpeed = 3.0f
    };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update
        UpdatePlayer(&player);

        BeginDrawing();
            ClearBackground(BLACK);

            DrawWorldMap();
            DrawPlayer(player);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}