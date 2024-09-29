#include "init.hpp"
#include "raylib.h"
#include <cstdlib>
#include <thread>
#include <chrono>

int n = 10;


void testEvents(int n , _EVENT* events);
void eventSelector( double& system_clock , int& index , _EVENT* events , _SERVER& server , _SERVER_QUEUE& sq);

void launch_arrival_animation(int lastx , int radius ,Color color);
int main(int argc, char *argv[]) {

  _SERVER s1;
  _EVENT* events;
  _SERVER_QUEUE q1;

  initServer(&s1);
  initQueue(&q1);
  events = initEvents(n,0.60);
  //testEvents(n , events);

  InitWindow(GetScreenWidth(), GetScreenHeight(), "Simulation Queue");
  SetTargetFPS(60);

  Rectangle serverRect = {400, 250, 100, 100};
 
  // queue boundaries

  float queueStartX = 50.0f;
  float queueStartY = 450.0f;
  float queueWidth = 500.0f;
  float queueHeight = 100.0f;

  // queue items properties
  float circle_initialX = 450.0f;
  float circle_initialY = 400.0f;
  float circle_radius = 15;
  Color qcolor = GREEN;

  double system_clock = 0;
  int current_index = 0;
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // check server state and status

    if (s1.state == DOWN)
      DrawRectangleRec(serverRect, RED);
    else if (s1.serving_status == 0)
      DrawRectangleRec(serverRect, DARKGRAY);
    else
      DrawRectangleRec(serverRect, GREEN);

    // Draw queue boundaries
    DrawLine(queueStartX + queueWidth, queueStartY, queueStartX + queueWidth, queueStartY + queueHeight, BLACK);
    DrawLine(queueStartX, queueStartY + queueHeight, queueStartX + queueWidth, queueStartY + queueHeight, BLACK);

    // draw queue
    for (int i = 0; i < q1.count; i++) {
      DrawCircle(circle_initialX - (i * 10) , circle_initialY, circle_radius,
                 qcolor);
      if(q1.new_arrival){ launch_arrival_animation( circle_initialX - (i * 10) ,circle_radius, qcolor); }
    }
    DrawText("Circle Movin Into Rectangle", 10, 10, 20, DARKGRAY);
    EndDrawing();
    eventSelector( system_clock , current_index , events , s1 ,q1);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
  CloseWindow();
  return 0;
}
