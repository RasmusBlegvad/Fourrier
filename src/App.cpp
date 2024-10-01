#include "App.h"
#include <fstream>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


// TODO LIST:


App::Screen::Screen(int w, int h, int fps)
   : width(w), height(h), h_padding(h * 0.01f), w_padding(w * 0.01f), fps(fps)
{
}

App::App(const Screen& screen, const char* title, Color bgColor, Color border_color)
   : m_default_bg_color(bgColor),
     m_screen(screen),
     // TODO: hmm det her wav fis er lidt sus fix det
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
   m_files.reserve(9);
   load_audio_files();
   InitWindow(m_screen.width, m_screen.height, title);
   SetTargetFPS(m_screen.fps);
   SetWindowMonitor(1);
   SetWindowState(FLAG_WINDOW_RESIZABLE);
   game_loop();
}

// Implement the game_loop function
void App::game_loop()
{
   while (!WindowShouldClose())
   {
      Vector2 mouse_pos = GetMousePosition();
      BeginDrawing();
      update_screen_size();
      render();
      is_filename_pressed(mouse_pos);
      event_handler();

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

void App::event_handler()
{
   // TODO: Refactor into UI class
   if (GuiButton({
                    .x = m_fs_rect.x + m_fs_rect.width - m_screen.w_padding, .y = m_fs_rect.y + m_screen.h_padding,
                    .width = m_screen.h_padding, .height = m_screen.h_padding
                 }, "R"))
   {
      m_files.clear();
      load_audio_files();
   }
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

void App::load_audio_files()
{
   for (const auto& file : std::filesystem::directory_iterator("../audio files"))
   {
      m_files.push_back(file);
   }
}

void App::render_audio_file_names()
{
   m_file_name_pos.clear();
   int filename_spacing = m_fs_rect.height / m_files.size();

   for (int i = 0; i < m_files.size(); ++i)
   {
      int spacing = i * filename_spacing;
      const char* filename = m_files[i].path().filename().generic_string().c_str();
      float x_pos = m_fs_rect.x + m_screen.h_padding;
      float y_pos = (m_fs_rect.y + m_screen.h_padding) + spacing;
      DrawText(filename, x_pos, y_pos, 20, WHITE);
      m_file_name_pos.push_back(Vector3{.x = x_pos, .y = y_pos, .z = static_cast<float>(i)});
   }
}

std::tuple<bool, std::string> App::is_mouse_over_filename(const Vector2& mouse_pos)
{
   for (int i = 0; i < m_files.size(); ++i)
   {
      // Store the filename in a string (safer than using c_str() directly)
      std::string filename = m_files[i].path().filename().generic_string();
      Vector2 text_size = MeasureTextEx(GetFontDefault(), filename.c_str(), 20, 1);
      Rectangle text_bounding_box = {m_file_name_pos[i].x, m_file_name_pos[i].y, text_size.x, text_size.y};

      if (CheckCollisionPointRec(mouse_pos, text_bounding_box))
      {
         DrawText(filename.c_str(), m_file_name_pos[i].x, m_file_name_pos[i].y, 20, GREEN);
         return std::make_tuple(true, filename);
      }
   }
   return std::make_tuple(false, "");
}

void App::is_filename_pressed(const Vector2& mouse_pos)
{
   auto [is_mouse_over, filename] = is_mouse_over_filename(mouse_pos);

   if (is_mouse_over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
   {
      m_wav.set_signal(m_wav.extract_signal(filename));
   }
}

