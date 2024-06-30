#include <stdio.h>
#include <raylib.h>
#include <string.h>

#define MAX_INPUT_CHARS 80

void getPhraseAndAddress(char * phrasePointer, char * addressPointer)
{

    // Resolución de la ventana

    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Input Box");

    // Finalizar los arreglos con el elemento cero

    char phrase[MAX_INPUT_CHARS + 1] = "\0";
    char address[MAX_INPUT_CHARS + 1] = "\0";

    int phraseCount = 0;
    int addressCount = 0;

    // Creación de los rectángulos en donde el usuario ingresa la frase y la dirección

    Rectangle phraseBox = { screenWidth/3.0f - 300, 180, 800, 50 };
    Rectangle addressBox = { screenWidth/3.0f - 300, 360, 800, 50 };

    bool mouseOnText = false;

    int framesCounter = 0;

    SetTargetFPS(10);

    // Loop principal
    while (!WindowShouldClose())
    {
        // Obtener la frase ingresada por el usuario
        if (CheckCollisionPointRec(GetMousePosition(), phraseBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Obtener el caracter presionado
            int key = GetCharPressed();

            while (key > 0)
            {
                // Permitir caracteres Unicode del 32 al 125
                if ((key >= 32) && (key <= 125) && (phraseCount < MAX_INPUT_CHARS))
                {
                    phrase[phraseCount] = (char)key;
                    phrase[phraseCount+1] = '\0'; // Finalizar el string con el elemento cero
                    phraseCount++;
                }

                key = GetCharPressed();
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
        
        // Obtener la dirección ingresada por el usuario
        if (CheckCollisionPointRec(GetMousePosition(), addressBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Obtener el caracter presionado
            int key = GetCharPressed();

            while (key > 0)
            {
                // Permitir caracteres Unicode del 32 al 125
                if ((key >= 32) && (key <= 125) && (addressCount < MAX_INPUT_CHARS))
                {
                    address[addressCount] = (char)key;
                    address[addressCount+1] = '\0'; // Finalizar el string con el elemento cero
                    addressCount++;
                }

                key = GetCharPressed();
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
        
        // Guardar la frase y la dirección ingresadas por el usuario

        strncpy(phrasePointer, phrase, MAX_INPUT_CHARS);
        strncpy(addressPointer, address, MAX_INPUT_CHARS);

        // Dibujo de los textos

        BeginDrawing();

            ClearBackground(SKYBLUE);

            DrawText("Phrase Finder", 300, 50, 50, DARKPURPLE);

            DrawText("Ingrese la frase que desea encontrar: ", 50, 140, 20, BLACK);

            DrawRectangleRec(phraseBox, LIGHTGRAY);

            DrawText(phrase, (int)phraseBox.x + 5, (int)phraseBox.y + 8, 16, MAROON);

            DrawText(TextFormat("Frase: %i/%i", phraseCount, MAX_INPUT_CHARS), 315, 235, 20, GRAY);

            DrawText("Ingrese la dirección del folder que contiene los archivos: ", 50, 320, 20, BLACK);

            DrawRectangleRec(addressBox, LIGHTGRAY);

            DrawText(address, (int)addressBox.x + 5, (int)addressBox.y + 8, 16, MAROON);

            DrawText(TextFormat("Dirección: %i/%i", addressCount, MAX_INPUT_CHARS), 315, 415, 20, GRAY);

        EndDrawing();
    }

    // Finalización de la ventana
    CloseWindow();

}

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}