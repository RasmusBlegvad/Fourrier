#include <iostream>
#include "Wav.h"
#include "SigVisualizer.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>

Color MY_BACKGROUND_COLOR = GetColor(0x181818FF);
std::string file = "100.wav";
bool plot = true;

int main()
{
    Wav wav;
    SigProccesing sp;
    SigVisualizer vis;
    SigVisualizer::Screen screen = {8 * 120, 8 * 230, 50, 50};

    // Extract signal from the WAV file
    auto const sig_raw = wav.extract_signal(file);
    auto const f_sig = sp.DFT(sig_raw);

    for (auto val : f_sig.magnitudes)
    {
        std::cout << val << "\n";
    }


    InitWindow(screen.WIDTH, screen.HEIGHT, "Fourier");

    // 1 = top monitor nice fror testing
    SetWindowMonitor(1);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MY_BACKGROUND_COLOR);
        // vis.plot_axis(screen);
        if (GuiButton((Rectangle){static_cast<float>(screen.WIDTH - 5 - 100), 5, 100, 40}, "Plot"))
        {
            plot = !plot;
        }

        if (plot)
        {
            vis.plot_signal(f_sig, screen);
        }

        EndDrawing();
    }
    CloseWindow();
}