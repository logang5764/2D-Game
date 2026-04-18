#include <stdio.h>

#include "raylib.h"

//====================
//
//  Compile using:
//
//  gcc <file.name> -o <new_file.name> -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
//
//====================

#define ROWS 10
#define COLS 10

int map[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};



int main(void) {
    InitWindow(500, 500, "First Window");


    for (int y = 0; y < ROWS; y++) {
        printf("\nRow Number: %d \n", y);
        for (int x = 0; x < COLS; x++) {
            printf("Column Number: %d ", x);
        };
        printf("\n");
    };




    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK); 
        EndDrawing();
    }

    CloseWindow();
    return 0;
};