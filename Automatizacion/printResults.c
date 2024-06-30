#include <stdio.h>
#include <raylib.h>
#include <string.h>

#define MAX_LINES 100

void printResults()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Print Results");

    char filename[] = "results.txt";
    FILE *file = fopen(filename, "r");

    char lines[MAX_LINES][256];
    int numberOfLines = 0;

    while (fgets(lines[numberOfLines], sizeof(lines[0]), file) && numberOfLines < MAX_LINES){
        numberOfLines ++;
    }

    fclose(file);

    int scrollOffset = 0;
    const int lineHeight = 20;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        scrollOffset -= GetMouseWheelMove() * lineHeight;

        if (scrollOffset < 0){
            scrollOffset = 0;
        }
        if (scrollOffset > (numberOfLines * lineHeight) - screenHeight + 100){
            scrollOffset = (numberOfLines * lineHeight) - screenHeight + 100;
        }

        BeginDrawing();

            ClearBackground(SKYBLUE);

            for (int i = 0; i<numberOfLines; i++){
                int y = 50 + i * lineHeight - scrollOffset;
                if (y >= 50 && y < screenHeight){
                    DrawText(lines[i], 50, y, 16, BLACK);
                }
            }

        EndDrawing();
    }
    CloseWindow();
}