#pragma once

#include <raylib.h>
#include "Wav.h"
#include "SigVisualizer.h"

class App
{
public:
    struct Screen
    {
        int width;
        int height;
        int fps;
        int w_padding;
        int h_padding;

        explicit Screen(int w = 8 * 230, int h = 8 * 150, int h_pad = 50, int w_pad = 50, int fps = 60);
    };

    explicit App(const Screen& screen = Screen{}, const char* title = "Fourrie", Color bgColor = GetColor(0x101010FF));

    void game_loop();

private:
    Color m_default_bg_color;
    Screen m_screen;
    Wav m_wav;

    void render();
    void cleanup();
};
