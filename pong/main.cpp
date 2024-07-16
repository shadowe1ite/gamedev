#include <iostream>
#include "raylib.h"

// global vars for score
int player_score {0};
int ai_score {0};

// custom colors
Color Green {Color{38, 185, 154,255}};
Color DarkGreen {Color{20, 160, 133,255}};
Color LightGreen {Color{129, 204, 184,255}};
Color Yellow {Color{243, 213, 91,255}};

class Ball {
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;
        Color color;

        // methods
        void Draw(){
            DrawCircle(x, y, radius, color);
        }

        // update position
        void Update(){
            x += speed_x;
            y += speed_y;

            // check border collision
            if(y + radius >= GetScreenHeight() || y - radius <= 0){
                speed_y *= -1;
            }
            else if(x + radius >= GetScreenWidth()){
                ai_score++;
                ResetBall();  
            } 
            else if(x - radius <= 0){
                player_score++;
                ResetBall();
            }
        }

        void ResetBall(){
            x = GetScreenWidth()/2;
            y = GetScreenHeight()/2;
            int speed_choices[2] = {-1, 1};
            WaitTime(0.5);
            speed_x *= speed_choices[GetRandomValue(0,1)];
            speed_y *= speed_choices[GetRandomValue(0,1)];
        }
};

class Paddle {
    protected:
        // used to check if the paddle getting outside the window
        void limit_move(){
            if(y <= 0){
                y = 0;
            } else if (y + height >= GetScreenHeight()){
                y = GetScreenHeight() - height;
            }
        }

    public:
        float x,y;
        float width, height;
        Color color;
        int speed;
        
        
        // methods
        void Draw(){
            DrawRectangleRounded(Rectangle{x, y, width, height} ,0.8, 0, color);
        }

        void Update(){
            if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
                y = y - speed;
            }
            else if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
                y = y + speed;
            }

            limit_move();
        }
};

class AiPaddle: public Paddle {
    public:

        void Update(int ball_y){
            // ai algorithm to move paddle
            if(y + height/2 > ball_y){
                // if center of the ball is greater than the center if paddle we need to move the paddle up
                y = y - speed;
            } else if (y + height/2 <= ball_y){
                y = y + speed;
            }
            limit_move(); // limit movement (inherited from Parent class)
        }
};

// instaces
Ball ball;
Paddle player;
AiPaddle ai;


int main(){

    // window configs
    const int win_width {1280};
    const int win_height {800};
    const int fps {60};
    InitWindow(win_width, win_height, "My Pong");
    SetTargetFPS(fps);
    
    // ball objects
    ball.radius = 20;
    ball.x = win_width/2;
    ball.y = win_height/2;
    ball.color = Yellow;
    ball.speed_x = 7;
    ball.speed_y = 7;
    
    // player objects
    player.width = 25;
    player.height = 120;
    player.color = WHITE;
    player.x = win_width - player.width - 10;
    player.y = win_height/2 - player.height/2;
    player.speed = 6;

    // ai objects
    ai.width = 25;
    ai.height = 120;
    ai.color = WHITE;
    ai.x = 10;
    ai.y = win_height/2 - ai.height/2;
    ai.speed = 6;

    // main loop
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(DarkGreen);

        DrawRectangle(win_width/2, 0, win_width/2, win_height, Green);
        DrawCircle(win_width/2, win_height/2, 120, LightGreen);
        DrawLine(win_width/2, 0, win_width/2, win_height, WHITE);
        
        ball.Update();
        player.Update();
        ai.Update(ball.y); // pass arg (ball.y == center of ball)

        // collision detection
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        } 
        else if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{ai.x, ai.y, ai.width, ai.height})){
            ball.speed_x *= -1;
        }
       
        
        ball.Draw();
        player.Draw();
        ai.Draw();
        
        // Draw score bord
        DrawText(TextFormat("AI: %i", ai_score), win_width/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("ME: %i", player_score), 3*win_width/4 - 20, 20, 80, WHITE);
        
        EndDrawing();
    }
    CloseWindow();
}
