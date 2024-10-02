#include "UI.h"
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

UI::Screen::Screen(int w, int h, int fps)
   : width(w), height(h), h_padding(h * 0.01f), w_padding(w * 0.01f), fps(fps)
{
}

UI::UI(const Screen& screen, Color bgColor, Color border_color)
   : default_bg_color(bgColor), default_border_color(border_color), screen(screen), fm() //, font(LoadFont())
{
   define_ui_rectangles();
}

//UI Setup functions
void UI::define_ui_rectangles()
{
   fs_rect = {
      .x = screen.w_padding,
      .y = screen.h_padding,
      .width = screen.width / 6,
      .height = screen.height / 2 + (2 * screen.w_padding)
   };
   comp_sig_rect =
   {
      .x = screen.w_padding + screen.width / 6 + screen.h_padding,
      .y = screen.h_padding,
      .width = (screen.width - screen.w_padding * 2) - (screen.width / 6 + screen.h_padding),
      .height = screen.height / 2 + (2 * screen.w_padding)
   };

   part_sig_rect = {
      .x = screen.w_padding,
      .y = screen.height / 2 + (2 * screen.w_padding) + screen.h_padding * 2,
      .width = screen.width - screen.w_padding * 2.0f,
      .height = screen.height - (3 * screen.h_padding + screen.height / 2 + (2 * screen.w_padding))
   };

   devider_start_pos = {
      .x = part_sig_rect.x + fs_rect.width,
      .y = part_sig_rect.y
   };

   devider_end_pos = {
      .x = part_sig_rect.x + fs_rect.width,
      .y = part_sig_rect.y + part_sig_rect.height,
   };
}

void UI::render_audio_file_names()
{
   file_name_pos.clear();
   int filename_spacing = fs_rect.height / fm.get_files().size();

   for (int i = 0; i < fm.get_files().size(); ++i)
   {
      int spacing = i * filename_spacing;
      const char* filename = fm.get_files()[i].path().filename().generic_string().c_str();
      float x_pos = fs_rect.x + screen.h_padding;
      float y_pos = (fs_rect.y + screen.h_padding) + spacing;
      DrawText(filename, x_pos, y_pos, 20, WHITE);
      file_name_pos.push_back(Vector3{.x = x_pos, .y = y_pos, .z = static_cast<float>(i)});
   }
}

//DRAWING / RENDERING STUFF TO THE SCREEN
void UI::render_ui_areas()
{
   //files overview rect
   // DrawRectangleRec(fs_rect, GetColor(0x303030FF));
   DrawRectangleLinesEx(fs_rect, 3, default_border_color);

   // composite signal rect
   // DrawRectangleRec(comp_sig_rect, GetColor(0x303030FF));
   DrawRectangleLinesEx(comp_sig_rect, 3, default_border_color);

   // partial signals rect
   // DrawRectangleRec(part_sig_rect, GetColor(0x303030FF));
   DrawRectangleLinesEx(part_sig_rect, 3, default_border_color);

   // options devider
   DrawLineEx(devider_start_pos, devider_end_pos, 3, default_border_color);
}

void UI::update_screen_size()
{
   if (IsWindowResized())
   {
      // NEW SCREEN
      screen.height = GetScreenHeight();
      screen.width = GetScreenWidth();
      screen.h_padding = GetScreenHeight() * 0.01f;
      screen.w_padding = GetScreenWidth() * 0.01f;

      define_ui_rectangles();
   }
}

void UI::render_axis()
{
   DrawLineEx(Vector2{
                 .x = fs_rect.x + fs_rect.width + screen.w_padding * 2,
                 .y = fs_rect.y
              },
              Vector2{
                 .x = fs_rect.x + fs_rect.width + screen.w_padding * 2,
                 .y = fs_rect.y + fs_rect.height - screen.w_padding
              },
              3,
              default_border_color
   );

   DrawLineEx(Vector2{
                 .x = fs_rect.x + fs_rect.width + screen.w_padding * 2,
                 .y = fs_rect.y + fs_rect.height - screen.w_padding
              },
              Vector2{
                 .x = (screen.width - screen.w_padding),
                 .y = fs_rect.y + fs_rect.height - screen.w_padding
              },
              3,
              default_border_color
   );
}


void UI::render()
{
   ClearBackground(default_bg_color);
   update_screen_size();
   render_ui_areas();
   //render_axis();
   render_audio_file_names();
}

// USER INTERACTION:
void UI::filename_pressed(const Vector2& mouse_pos)
{
   for (int i = 0; i < fm.get_files().size(); ++i)
   {
      // Store the filename in a string (safer than using c_str() directly)
      std::string filename = fm.get_files()[i].path().filename().generic_string();
      Vector2 text_size = MeasureTextEx(GetFontDefault(), filename.c_str(), 20, 1);
      Rectangle text_bounding_box = {file_name_pos[i].x, file_name_pos[i].y, text_size.x, text_size.y};

      if (CheckCollisionPointRec(mouse_pos, text_bounding_box))
      {
         DrawText(filename.c_str(), file_name_pos[i].x, file_name_pos[i].y, 20, GREEN);

         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
         {
            std::cout << filename << "\n";
         }
         return; // Exit once the file is clicked
      }
   }
}

void UI::reload_file_names()
{
   if (GuiButton(Rectangle{
                    .x = fs_rect.x + fs_rect.width - screen.w_padding * 2, .y = fs_rect.y + screen.w_padding,
                    .width = 20, .height = 20
                 }, "R"))
   {
      fm.load_audio_files();
   }
}

void UI::event_handler()
{
   Vector2 mouse_pos = GetMousePosition();
   filename_pressed(mouse_pos);
   reload_file_names();
}
