#include "App.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <iostream>

App::Screen::Screen(int w, int h, int h_pad, int w_pad, int fps)
    : width(w), height(h), h_padding(h_pad), w_padding(w_pad), fps(fps)
{
}

App::App(const Screen& screen, const char* title, Color bgColor)
    : m_default_bg_color(bgColor),
      m_screen(screen),
      m_wav("audio7.wav")

{
    InitWindow(m_screen.width, m_screen.height, title);
    SetTargetFPS(m_screen.fps);
    game_loop();
}

// Implement the game_loop function
void App::game_loop()
{
    const Wav::Signal& signal = m_wav.get_signal();
    bool plot = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(m_default_bg_color);

        if (GuiButton({0, 0, 100, 100}, "change plot"))
        {
            plot = !plot;
        }

        // Simplified plot logic
        SigVisualizer::plot_types plot_type = plot ? SigVisualizer::WAVEFORM : SigVisualizer::ENVELOPE;
        plot_signal(signal, m_screen.width, m_screen.height, m_screen.h_padding, m_screen.w_padding, plot_type);

        EndDrawing();
    }

    cleanup();
}

void App::render()
{
}


void App::cleanup()
{
    CloseWindow();
}
