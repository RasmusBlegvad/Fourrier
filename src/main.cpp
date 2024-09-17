#include <iostream>
#include "Wav.h"
#include "SigVisualizer.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>

Color MY_BACKGROUND_COLOR = GetColor(0x181818FF);
std::string file = "audio3.wav";
bool plot = false;

int main()
{
    Wav wav;
    SigVisualizer vis;
    SigVisualizer::Screen screen = {16 * 60, 16 * 90, 50, 50};

    // Extract signal from the WAV file
    auto sig = wav.extract_signal(file);

    const float sig_time = sig.samples.size() / static_cast<float>(sig.samplerate);

    InitWindow(screen.WIDTH, screen.HEIGHT, "Fourier");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MY_BACKGROUND_COLOR);

        // Y-axis
        DrawLine(50, 50, 50, screen.HEIGHT - 50, WHITE);
        // X-axis
        DrawLine(50, screen.HEIGHT - 50, screen.WIDTH - 50, screen.HEIGHT - 50, WHITE);
        // Y axis-label
        DrawText("A", 20, 50, 30, WHITE);
        // X axis-label
        DrawText("t", screen.WIDTH - 72, screen.HEIGHT - 43, 30, WHITE);

        if (GuiButton((Rectangle){0, 0, 100, 40}, "Plot"))
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