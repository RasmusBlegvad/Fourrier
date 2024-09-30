#pragma once
#include <filesystem>
#include <raylib.h>
#include "Wav.h"

class App
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

   explicit App(const Screen& screen = Screen{}, const char* title = "Fourrie", Color bgColor = GetColor(0x181818FF),
                Color border_color = GetColor(0x505050FF));

private:
   Color m_default_bg_color;
   Color m_default_border_color;
   Screen m_screen;
   Wav m_wav;

   // UI ELEMTS
   Rectangle m_fs_rect;
   Rectangle m_comp_sig_rect;
   Rectangle m_part_sig_rect;
   Vector2 m_devider_start_pos;
   Vector2 m_devider_end_pos;

   // maybe this should be in a file manager class at somepoint so that we can have functions for deleting, renaming, moving and dropping files into the
   // program from the ui but as of now i am only testing whether i can even get the program to show me what files i have)
   std::vector<std::filesystem::directory_entry> m_files;

   void game_loop();
   void render_axis();
   void render_borders();
   void render();
   void cleanup();
   void event_handler();
   void load_audio_files();
   void render_audio_file_names();
   void update_screen_size();
};
