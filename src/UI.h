#pragma once
#include <vector>
#include "raylib.h"
#include "FileManager.h"
#include "Wav.h"

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

      explicit Screen(int w = 8.0f * 300.0f, int h = 8.0f * 160.0f,
                      int fps = 60);
   };

   explicit UI(const Screen& screen = Screen{}, Color bgColor = GetColor(0x181818FF),
               Color border_color = GetColor(0x454545FF), Color UI_rect_bg = GetColor(0x252525FF));

   // UI Setup functions_________________________________________________________________________________________________
   void define_ui_rectangles();
   void load_font(const std::string& file_name);
   //___________________________________________________________________________________________________________________

   // DRAWING / RENDERING STUFF TO THE SCREEN____________________________________________________________________________
   void render_audio_file_names();
   void render_ui_areas() const;
   void render_axis() const;
   void update_screen_size();
   void render();

   //___________________________________________________________________________________________________________________

   // USER INTERACTION__________________________________________________________________________________________________
   void filename_pressed(const Vector2& mouse_pos, Wav& wav);
   void reload_file_names();
   void event_handler(Wav& wav);
   //___________________________________________________________________________________________________________________

   // PLOTTING__________________________________________________________________________________________________________
   void plot_signal(const Wav::Signal& sig) const;
   void plotting(const Wav::Signal& sig) const;
   void graph_zoom() const;
   //___________________________________________________________________________________________________________________


   Screen screen;

private:
   // COLROS
   Color bg_color;
   Color border_color;
   Color UI_rect_bg;

   Rectangle fs_rect{};
   Rectangle comp_sig_rect{};
   Rectangle part_sig_rect{};
   Rectangle comp_plotting_rect{};
   Vector2 devider_start_pos{};
   Vector2 devider_end_pos{};
   Rectangle graph_display_window{};
   Rectangle part_sig_options_rec;

   Font font{};

   std::vector<Vector3> file_name_pos;

   FileManager fm;

   // for debouncing buttons:
};
