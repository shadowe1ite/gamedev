#include <iostream>
#include "raylib.h"

int main(){
    
    // window properties
    const int win_width {400};
    const int win_height {350};
    const std::string title {"Dapper Dasher"};

    // init window
    InitWindow(win_width, win_height, title.c_str());

    // FPS
    const int fps {60};
    SetTargetFPS(fps);

    int velocity {0};

    // check rectangle is in air
    bool isInAir {};

    // jump velocity
    const int jumpVal {-18};

    // accelartion due to gravity (pixel/frame)/frame
    const int gravity {1};

    // sprite
    Texture2D scarfy = LoadTexture("assets/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = win_width/2 - scarfyRec.width/2;
    scarfyPos.y = win_height - scarfyRec.height;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // logic begin
        
        if(scarfyPos.y >= win_height - scarfyRec.height){
            // in ground
            velocity = 0;
            isInAir = false;

        } else {
            // in air
           velocity += gravity;
           isInAir = true;
        }

        if(IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jumpVal;
        }
        
        scarfyPos.y += velocity;
        
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // logic end
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}