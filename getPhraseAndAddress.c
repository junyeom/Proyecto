#include <stdio.h>
#include "raylib.h"
#include "string.h"

#define MAX_INPUT_CHARS     20

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void getPhraseAndAddress(char * frase, char * direccion)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - input box");

    char phrase[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    char address[MAX_INPUT_CHARS + 1] = "\0";

    int phraseCount = 0;
    int addressCount = 0;

    Rectangle phraseBox = { screenWidth/3.0f - 100, 180, 500, 50 };
    Rectangle addressBox = { screenWidth/3.0f - 100, 270, 500, 50 };

    bool mouseOnText = false;

    int framesCounter = 0;

    SetTargetFPS(10);               // Set our game to run at 10 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update phrase
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), phraseBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (phraseCount < MAX_INPUT_CHARS))
                {
                    phrase[phraseCount] = (char)key;
                    phrase[phraseCount+1] = '\0'; // Add null terminator at the end of the string.
                    phraseCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                phraseCount--;
                if (phraseCount < 0) phraseCount = 0;
                phrase[phraseCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Update address
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), addressBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (addressCount < MAX_INPUT_CHARS))
                {
                    address[addressCount] = (char)key;
                    address[addressCount+1] = '\0'; // Add null terminator at the end of the string.
                    addressCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                addressCount--;
                if (addressCount < 0) addressCount = 0;
                address[addressCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        strncpy(frase, phrase, MAX_INPUT_CHARS);
        strncpy(direccion, address, MAX_INPUT_CHARS);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Ingrese la frase que desea encontrar: ", 240, 140, 20, GRAY);

            DrawRectangleRec(phraseBox, LIGHTGRAY);

            DrawText(phrase, (int)phraseBox.x + 5, (int)phraseBox.y + 8, 40, MAROON);

            DrawText(TextFormat("Frase: %i/%i", phraseCount, MAX_INPUT_CHARS), 315, 235, 20, DARKGRAY);

            DrawRectangleRec(addressBox, LIGHTGRAY);

            DrawText(address, (int)addressBox.x + 5, (int)addressBox.y + 8, 40, MAROON);

            DrawText(TextFormat("Dirección: %i/%i", addressCount, MAX_INPUT_CHARS), 315, 325, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

int main ()
{
    char frase[MAX_INPUT_CHARS];
    char direccion[MAX_INPUT_CHARS];
    getPhraseAndAddress(frase, direccion);
    printf("%s\n%s\n", frase, direccion);
    return 0;
}