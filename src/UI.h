#pragma once
#include <raylib.h>
#include <vector>
#include <string>

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
   void define_ui_rectangles(const Screen& screen);
   //___________________________________________________________________________________________________________________


   //DRAWING / RENDERING STUFF TO THE SCREEN____________________________________________________________________________
   void render_audio_file_names();
   void render_borders();
   void render();
   void render_axis();
   void update_screen_size();

   //___________________________________________________________________________________________________________________

   // USER INTERACTION__________________________________________________________________________________________________
   std::tuple<bool, std::string> is_mouse_over_filename(const Vector2& mouse_pos);
   void is_filename_pressed(const Vector2& mouse_pos);
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

   std::vector<Vector3> file_name_pos;

   FileManager fm;
};
