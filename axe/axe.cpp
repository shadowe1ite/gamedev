#include <iostream>
#include "raylib.h"

// TODO: Move axe

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
    const Color circle_color {WHITE}; // here Color is user defined data type in raylib
    
    // circle edges
    // watch this -> https://www.udemy.com/course/cpp-fundamentals/learn/lecture/25867394#content
    int l_circle_x {circle_x - circle_radius};
    int r_circle_x {circle_x + circle_radius};
    int u_circle_y {circle_y - circle_radius};
    int b_circle_y {circle_y + circle_radius};

    // axe (rectangle) cooordinates and other values
    int axe_x {550};
    int axe_y {0};
    int axe_length {50};
    int direction {10}; // increment y
    const Color axe_color {RED}; // here Color is user defined data type in raylib

    // Axe edges
    int l_axe_x {axe_x};
    int r_axe_x {axe_x + axe_length};
    int u_axe_y {axe_y};
    int b_axe_y {axe_y + axe_length};

    // collision detection
    bool collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

    // FPS (use to set how many frames can be changed in each senconds)
    const int fps {60};
    SetTargetFPS(fps);
    
    // main loop
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(win_color); // used variable win_color
        DrawText("Axe Game", 350, 28, 23, GRAY);
        // Game logic Begin

        if(collision_with_axe){
            DrawText("Game Over!", 310, 200, 40, RED);
        } else {

            // update the edges
            
            // circle
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            // axe
            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;

            // update collision_with_axe
            collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

    
            // Draw user character circle 
            DrawCircle(circle_x, circle_y, circle_radius, circle_color);

            // Draw villain Axe
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, axe_color);

            // Move Axe (working = when -+ = -)
            axe_y += direction;
            if(axe_y > win_y || axe_y < 0){
                direction = -direction;
            }

            // user controls
            // use and operation to check if then circle coordiante is less than window diamension (use window diamention width(x coordinates) variable for right moment)
            // use and operation to check if then circle coordiante is greater than window diamension (use window diamention 0 (staring of x coordinate [origin]) for right moment)
            if (IsKeyDown(KEY_D) && circle_x < win_x || IsKeyDown(KEY_RIGHT) && circle_x < win_x){
                circle_x += 10;
            } else if (IsKeyDown(KEY_A) && circle_x > 0 || IsKeyDown(KEY_LEFT) && circle_x > 0 ){
                circle_x -= 10;
            }

            // Game logic End  
        }

        EndDrawing();
    }
}