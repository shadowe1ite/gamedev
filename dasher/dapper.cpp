#include <iostream>
#include "raylib.h"

int main(){
    
    // window properties
    const int width {400};
    const int height {350};
    const std::string title {"Dapper Dasher"};

    // init window
    InitWindow(width, height, title.c_str());

    // FPS
    const int fps {60};
    SetTargetFPS(fps);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // logic begin


        // logic end
        EndDrawing();
    }
    
}