#include "App.h"
#include <fstream>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <iostream>

App::Screen::Screen(int w, int h, int fps)
   : width(w), height(h), h_padding(h * 0.01f), w_padding(w * 0.01f), fps(fps)
{
}

App::App(const Screen& screen, const char* title, Color bgColor, Color border_color)
   : m_default_bg_color(bgColor),
     m_screen(screen),
     m_wav("audio7.wav"),
     m_default_border_color(border_color),
     m_fs_rect({
        .x = m_screen.w_padding,
        .y = m_screen.h_padding,
        .width = m_screen.width / 6,
        .height = m_screen.height / 2 + (2 * m_screen.w_padding)
     }),
     m_comp_sig_rect(
        {
           .x = m_screen.w_padding + m_screen.width / 6 + m_screen.h_padding,
           .y = m_screen.h_padding,
           .width = (m_screen.width - m_screen.w_padding * 2) - (m_screen.width / 6 + m_screen.h_padding),
           .height = m_screen.height / 2 + (2 * m_screen.w_padding)
        }),
     m_part_sig_rect({
        .x = m_screen.w_padding,
        .y = m_screen.height / 2 + (2 * m_screen.w_padding) + m_screen.h_padding * 2,
        .width = m_screen.width - m_screen.w_padding * 2.0f,
        .height = m_screen.height - (3 * m_screen.h_padding + m_screen.height / 2 + (2 * m_screen.w_padding))
     }),
     m_devider_start_pos({
        .x = m_part_sig_rect.x + m_fs_rect.width,
        .y = m_part_sig_rect.y
     }),
     m_devider_end_pos({
        .x = m_part_sig_rect.x + m_fs_rect.width,
        .y = m_part_sig_rect.y + m_part_sig_rect.height,
     })


{
   InitWindow(m_screen.width, m_screen.height, title);
   SetTargetFPS(m_screen.fps);
   SetWindowMonitor(1);
   SetWindowState(FLAG_WINDOW_RESIZABLE);
   update_audio_files();
   game_loop();
}

// Implement the game_loop function
void App::game_loop()
{
   while (!WindowShouldClose())
   {
      BeginDrawing();
      update_audio_files();

      update_screen_size();
      render();

      EndDrawing();
   }

   cleanup();
}

void App::render_borders()
{
   //files overview rect
   DrawRectangleLinesEx(m_fs_rect, 3, m_default_border_color);

   // composite signal rect
   DrawRectangleLinesEx(m_comp_sig_rect, 3, m_default_border_color);

   // partial signals rect
   DrawRectangleLinesEx(m_part_sig_rect, 3, m_default_border_color);

   // options devider
   DrawLineEx(m_devider_start_pos, m_devider_end_pos, 3, m_default_border_color);
}

void App::render_axis()
{
   // TODO: implement ty
}

// here we render gui stuff that does not change i think
void App::render()
{
   ClearBackground(m_default_bg_color);
   render_axis();
   render_borders();
   render_audio_file_names();
}

void event_handler()
{
   // TODO: implement ty
}

void App::cleanup()
{
   CloseWindow();
}

void App::update_screen_size()
{
   if (IsWindowResized())
   {
      // NEW SCREEN
      m_screen.height = GetScreenHeight();
      m_screen.width = GetScreenWidth();
      m_screen.h_padding = GetScreenHeight() * 0.01f;
      m_screen.w_padding = GetScreenWidth() * 0.01f;

      // NEW UI RECTANGLES
      // NOTE: h_padding is used for spacing rectangles both vertically and horisontally maybe fix later
      Rectangle new_fs_rect = {
         .x = m_screen.w_padding, .y = m_screen.h_padding, .width = m_screen.width / 6,
         .height = m_screen.height / 2 + (2 * m_screen.w_padding)
      };

      Rectangle new_comp_sig_rect =
      {
         .x = m_screen.w_padding + m_screen.width / 6 + m_screen.h_padding, .y = m_screen.h_padding,
         .width = (m_screen.width - m_screen.w_padding * 2) - (m_screen.width / 6 + m_screen.h_padding),
         .height = m_screen.height / 2 + (2 * m_screen.w_padding)
      };
      Rectangle new_part_sig_rect = {
         .x = m_screen.w_padding, .y = m_screen.height / 2 + (2 * m_screen.w_padding) + m_screen.h_padding * 2,
         .width = m_screen.width - m_screen.w_padding * 2.0f,
         .height = m_screen.height - (3 * m_screen.h_padding + m_screen.height / 2 + (2 * m_screen.w_padding))
      };

      //NEW OPTIONS DEVIDER VECTORS
      Vector2 new_start_pos =
      {
         .x = new_part_sig_rect.x + new_fs_rect.width,
         .y = new_part_sig_rect.y,
      };

      Vector2 new_end_pos =
      {
         .x = new_part_sig_rect.x + new_fs_rect.width,
         .y = new_part_sig_rect.y + new_part_sig_rect.height,
      };

      m_fs_rect = new_fs_rect;
      m_comp_sig_rect = new_comp_sig_rect;
      m_part_sig_rect = new_part_sig_rect;
      m_devider_start_pos = new_start_pos;
      m_devider_end_pos = new_end_pos;
   }
}

void App::update_audio_files()
{
   m_files.clear();

   for (const auto& file : std::filesystem::directory_iterator("../audio files"))
   {
      m_files.push_back(file);
   }
}

void App::render_audio_file_names()
{
   for (const auto& file : m_files)
   {
      std::cout << "file name: " << file.path().filename().generic_string() << "\n";
   }
}


