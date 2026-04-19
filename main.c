#include <stdio.h>
#include <math.h> 
#include "raylib.h"

// Screen dimensions
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

// Map size
#define ROWS 20
#define COLS 20

// Cell size
#define CELL_WIDTH (SCREEN_WIDTH / COLS)
#define CELL_HEIGHT (SCREEN_HEIGHT / ROWS)

// Map
int map[ROWS][COLS] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
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

bool IsWallAt(float x, float y) {
    int mapX = (int)(x / CELL_WIDTH);
    int mapY = (int)(y / CELL_HEIGHT);

    if (mapX < 0 || mapX >= COLS || mapY < 0 || mapY >= ROWS) return true;
    
    return (map[mapY][mapX] == 1);
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

    // Calculate potential next coordinates
    float nextX = p->position.x + cosf(p->angle) * moveStep;
    float nextY = p->position.y + sinf(p->angle) * moveStep;

    // Check X and Y separately to allow wall sliding
    if (!IsWallAt(nextX, p->position.y)) {
        p->position.x = nextX;
    }
    if (!IsWallAt(p->position.x, nextY)) {
        p->position.y = nextY;
    }
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
        .position = (Vector2){ 80, 80 },
        .angle = 0.0f,
        .speed = 200.0f,
        .turnSpeed = 4.0f
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