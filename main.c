#include "raylib.h"

int main(void) {
    InitWindow(500, 500, "First Window");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK); 
        EndDrawing();
    }

    CloseWindow();
    return 0;
}