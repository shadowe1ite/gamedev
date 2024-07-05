#include <iostream>
#include "raylib.h"

// TODO: learn and understand what compond assignment operator

int main(){

    // window dimensions and other values
    const int win_x {800}; // width
    const int win_y {450}; // hight
    const Color win_color {BLACK}; // user defined datatype 
    
    // initialize window
    InitWindow(win_x, win_y, "Axe Game");
    
    // circle coordinates and other values
    int circle_x {win_x/2}; // dived by 2 to get center of x coordinates (center of width)
    int circle_y {win_y/2}; // dived by 2 to get center of y coordinates (center of hight)
    const int circle_radius {25};
    const Color circle_color {GREEN}; // here Color is user defined data type in raylib
    
    // rectangle cooordinates and other values
    int axe_x {550};
    int axe_y {0};
    int axe_width {50};
    int axe_heigt {50};
    const Color axe_color {RED}; // here Color is user defined data type in raylib

    // FPS (use to set how many frames can be changed in each senconds)
    const int fps {60};
    SetTargetFPS(fps);
    
    // main loop
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(win_color); // used variable win_color

        // Game logic Begin
        // Draw user character circle 
        DrawCircle(circle_x, circle_y, circle_radius, circle_color);

        // Draw villain Axe
        DrawRectangle(axe_x, axe_y, axe_width, axe_heigt, axe_color);

        // Move Axe
        axe_y += 10;

        // user controls
        // use and operation to check if then circle coordiante is less than window diamension (use window diamention width(x coordinates) variable for right moment)
        // use and operation to check if then circle coordiante is greater than window diamension (use window diamention 0 (staring of x coordinate [origin]) for right moment)
        if (IsKeyDown(KEY_D) && circle_x < win_x || IsKeyDown(KEY_RIGHT) && circle_x < win_x){
            circle_x += 10;
        } else if (IsKeyDown(KEY_A) && circle_x > 0 || IsKeyDown(KEY_LEFT) && circle_x > 0 ){
            circle_x -= 10;
        }

        // Game logic End
        EndDrawing();
    }
}
