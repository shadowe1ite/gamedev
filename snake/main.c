#include <iostream>
#include "raylib.h"
#include <deque>

// Window size
const int WinWidth {750};
const int WinHeight {750};
    
// cell
const int CellSize {30};
const int CellCount {25};

// Declare color
const Color Green {173, 204, 96, 255};
const Color DarkGreen {43, 51, 24, 255};
   
    
// Classes
class Snake {
    public:
        std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

        void Draw(){
            for(int i = 0; i < body.size(); i++){
                int x = body[i].x;
                int y = body[i].y;
                DrawRectangle(x * CellSize, y * CellSize, CellSize, CellSize, DarkGreen);
            }
        }
};

class Food {
    public:
        Vector2 position;
        Texture2D texture;

        // constroctor
        Food(){
            Image image = LoadImage("./assets/sprites/food.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            position = GenRandPos();

        }

        // destructor
        ~Food(){
            UnloadTexture(texture);
        }

        // method
        void Draw(){
            DrawTexture(texture, position.x * CellSize, position.y * CellSize, WHITE);
        }

        Vector2 GenRandPos(){
            float x = GetRandomValue(0, CellCount - 1);
            float y = GetRandomValue(0, CellCount - 1);
            return Vector2{x, y};
        }
    };

int main(){
    // init window
    InitWindow(CellSize * CellCount, CellSize * CellCount, "Snake");
    // fps
    const int fps {60};
    SetTargetFPS(fps);

    Food food;
    Snake snake;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Green);

        // Game code start from here
        food.Draw();
        snake.Draw();

        EndDrawing();
    }
    
    CloseWindow();
   
}