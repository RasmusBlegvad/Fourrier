#include <iostream>
#include "Wav.h"
#include "SigVisualizer.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>

Color MY_BACKGROUND_COLOR = GetColor(0x181818FF);
std::string file = "Asine.wav";
bool plot = false;

int main()
{
    Wav wav;
    SigVisualizer vis;
    SigVisualizer::Screen screen = {16 * 60, 16 * 130, 50};

    // Extract signal from the WAV file
    auto sig = wav.extract_signal(file);

    const float sig_time = sig.samples.size() / static_cast<float>(sig.samplerate);

    InitWindow(screen.WIDTH, screen.HEIGHT, "Fourier");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MY_BACKGROUND_COLOR);

        if (GuiButton((Rectangle){350, 280, 100, 40}, "Click Me"))
        {
            plot = !plot;
        }

        if (plot)
        {
            vis.plot_signal(sig, screen);
        }

        EndDrawing();
    }
    CloseWindow();
}