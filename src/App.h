#pragma once

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

    void game_loop();
    void render_axis();
    void render_borders();

private:
    Color m_default_bg_color;
    Color m_default_border_color;
    Screen m_screen;
    Wav m_wav;

    Rectangle m_fs_rect;
    Rectangle m_comp_sig_rect;
    Rectangle m_part_sig_rect;


    void render();

    void event_handler();
    void cleanup();
};
