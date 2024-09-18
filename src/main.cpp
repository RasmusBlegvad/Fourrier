#include <iostream>
#include "Wav.h"
#include "SigVisualizer.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>

Color MY_BACKGROUND_COLOR = GetColor(0x181818FF);
std::string file = "audio3.wav";
bool plot = true;

int main()
{

    SigVisualizer::Screen screen = {8 * 120, 8 * 230, 50, 50};

    // Extract signal from the WAV file
    auto const t_sig1 = Wav::extract_signal(file);
    auto const t_sig = SigProccesing::generate_sine(1,3,580);
    // auto const f_sig = sp.DFT(t_sig);

    InitWindow(screen.WIDTH, screen.HEIGHT, "Fourier");
    // 1 = top monitor nice fror testing
    // SetWindowMonitor(1);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MY_BACKGROUND_COLOR);
        if (GuiButton((Rectangle){static_cast<float>(screen.WIDTH - 5 - 100), 5, 100, 40}, "Plot"))
        {
            plot = !plot;
        }

        if (plot)
        {
            SigVisualizer::plot_signal(t_sig, screen,SigVisualizer::ENVELOPE);
        }

        if (!plot)
        {
            SigVisualizer::plot_signal(t_sig1, screen,SigVisualizer::WAVEFORM);
        }



        EndDrawing();
    }
    CloseWindow();
}