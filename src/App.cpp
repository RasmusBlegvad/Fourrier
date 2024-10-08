#include "App.h"
#include <fstream>


App::App(const char* title)
   : wav("Asine.wav"), ui()
{
   InitWindow(ui.screen.width, ui.screen.height, title);
   ui.load_font("jbMono.ttf");
   SetTargetFPS(ui.screen.fps);
   SetWindowMonitor(1);
   SetWindowState(FLAG_WINDOW_RESIZABLE);
   SetWindowState(FLAG_WINDOW_MAXIMIZED);
   game_loop();
}

// Implement the game_loop function
void App::game_loop()
{

   while (!WindowShouldClose())
   {
      BeginDrawing();
      ui.render();
      ui.event_handler(wav);
      ui.plotting(wav.get_signal());
      ui.graph_zoom();
      EndDrawing();
   }

   CloseWindow();
}






