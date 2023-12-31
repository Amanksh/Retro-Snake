#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;
// Variables
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};
int cellSize = 20;
int cellCount = 15;
double lastUpdateTime = 0;
int offset = 75;

// Functions
bool eventTrigger(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(element, deque[i]))
        {
            return true;
        }
    }
    return false;
}

// Classes
// Snkae object
class Snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;
    void Draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = {offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
    void Update()
    {
        body.push_front(Vector2Add(body[0], direction));
        if (addSegment == true)
        {
            addSegment = false;
        }
        else
        {
            body.pop_back();
        }
    }
    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};
// Food object
class Food

{
public:
    Vector2 position;
    Texture2D texture;
    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }
    ~Food()
    {
        UnloadTexture(texture);
    }
    void Draw()
    {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }
    Vector2 GenerateCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateCell();
        while (ElementInDeque(position, snakeBody))
        {
            position = GenerateCell();
        }
        return position;
    }
};
class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    void Draw()
    {
        snake.Draw();
        food.Draw();
    }
    void Update()
    {
        if (running)
        {
            snake.Update();
            CheckCollision();
            CheckCollisionWithEdges();
            CheckCollionWithTail();
        }
    }
    void CheckCollision()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
        }
    }
    void CheckCollisionWithEdges()
    {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1)
        {
            GameOver();
        }
        else if (snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }
    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
    }
    void CheckCollionWithTail()
    {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if (ElementInDeque(snake.body[0], headlessBody))
        {
            GameOver();
        }
    }
};
int main()
{
    InitWindow(2 * offset + cellSize * cellSize, 2 * offset + cellCount * cellSize, "retro snake game");
    SetTargetFPS(60);
    Game game = Game();
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        // drawing
        if (eventTrigger(0.2))
        {
            game.Update();
        }
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0, -1};
            game.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0, 1};
            game.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1, 0};
            game.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = {1, 0};
            game.running = true;
        }
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellCount * cellSize + 10}, 5, darkGreen);
        DrawText("Retro Snake", offset - 5, 20, 40, darkGreen);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}