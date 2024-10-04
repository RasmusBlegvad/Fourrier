#include "App.h"
#include <fstream>


App::App(const char* title)
   : wav("100.wav"), ui()
{
   InitWindow(ui.screen.width, ui.screen.height, title);
   ui.load_font("jbMono.ttf");
   SetTargetFPS(ui.screen.fps);
   SetWindowMonitor(1);
   SetWindowState(FLAG_WINDOW_RESIZABLE);
   game_loop();
}

// Implement the game_loop function
void App::game_loop()
{
   float sliderValue = 50.0f;

   while (!WindowShouldClose())
   {
      BeginDrawing();
      ui.render();
      ui.event_handler();
      ui.event_handler();
      ui.plot_signal(wav.get_signal());

      EndDrawing();
   }

   CloseWindow();
}






