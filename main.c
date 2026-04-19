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

// Raycasting settings
#define FOV 60.0f
#define NUM_RAYS 125

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
    if (!IsWallAt(nextX, p->position.y)) p->position.x = nextX;
    if (!IsWallAt(p->position.x, nextY)) p->position.y = nextY;
}

void Draw3DView(Player p) {
    float startAngle = p.angle - (FOV * PI / 180.0f) / 2.0f;
    float step = (FOV * PI / 180.0f) / (float)NUM_RAYS;
    float stripWidth = (float)SCREEN_WIDTH / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        float rayAngle = startAngle + (i * step);
        float rayX = p.position.x;
        float rayY = p.position.y;
        
        float dx = cosf(rayAngle);
        float dy = sinf(rayAngle);

        // Raycasting
        while (!IsWallAt(rayX, rayY)) {
            rayX += dx * 0.5f; 
            rayY += dy * 0.5f;
        }

        // Distance and Fisheye Correction
        float distance = sqrtf(powf(rayX - p.position.x, 2) + powf(rayY - p.position.y, 2));
        distance *= cosf(rayAngle - p.angle);

        // Calculate height of wall strip
        float wallHeight = (CELL_HEIGHT * SCREEN_HEIGHT) / distance;

        // Center the wall vertically
        float drawStart = (SCREEN_HEIGHT / 2.0f) - (wallHeight / 2.0f);

        // Shading
        float brightness = 1.0f - (distance / (SCREEN_WIDTH * 0.8f));
        if (brightness < 0) brightness = 0;
        Color wallColor = ColorBrightness(DARKGRAY, brightness - 0.2f);

        DrawRectangle(i * stripWidth, drawStart, stripWidth + 1, wallHeight, wallColor);
    }
}

// --- MAIN ---
int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map");
    
    // Initialize player
    Player player = {
        .position = (Vector2){ 80, 80 },
        .angle = 0.0f,
        .speed = 125.0f,
        .turnSpeed = 3.0f
    };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update
        UpdatePlayer(&player);

        BeginDrawing();
            ClearBackground(BLACK);

            // Draw 3D Walls
            Draw3DView(player);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}