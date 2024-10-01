#include "App.h"
#include <fstream>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

App::App(const char* title)
   : wav("audio7.wav"), ui()
{
   InitWindow(ui.screen.width, ui.screen.height, title);
   SetTargetFPS(ui.screen.fps);
   SetWindowMonitor(1);
   SetWindowState(FLAG_WINDOW_RESIZABLE);
   game_loop();
}

// Implement the game_loop function
void App::game_loop()
{
   while (!WindowShouldClose())
   {
      BeginDrawing();
      ui.render();
      ui.event_handler();

      EndDrawing();
   }

   CloseWindow();
}






