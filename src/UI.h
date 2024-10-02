#pragma once
#include <raylib.h>
#include <vector>

#include "FileManager.h"

class UI
{
public:
   struct Screen
   {
      float width;
      float height;
      int fps;
      float w_padding;
      float h_padding;

      explicit Screen(int w = 8.0f * 200.0f, int h = 8.0f * 120.0f,
                      int fps = 60);
   };

   explicit UI(const Screen& screen = Screen{}, Color bgColor = GetColor(0x181818FF),
               Color border_color = GetColor(0x505050FF));


   //UI Setup functions_________________________________________________________________________________________________
   void define_ui_rectangles();
   //___________________________________________________________________________________________________________________


   //DRAWING / RENDERING STUFF TO THE SCREEN____________________________________________________________________________
   void render_audio_file_names();
   void render_ui_areas();
   void render_axis();
   void update_screen_size();
   void render();

   //___________________________________________________________________________________________________________________

   // USER INTERACTION__________________________________________________________________________________________________
   void filename_pressed(const Vector2& mouse_pos);
   void reload_file_names();
   void event_handler();
   //___________________________________________________________________________________________________________________

   Screen screen;

private:
   Color default_bg_color;
   Color default_border_color;

   Rectangle fs_rect{};
   Rectangle comp_sig_rect{};
   Rectangle part_sig_rect{};
   Vector2 devider_start_pos{};
   Vector2 devider_end_pos{};

   Font font;

   std::vector<Vector3> file_name_pos;

   FileManager fm;
};
