#include <iostream>
#include "WavReader.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>

int HEIGHT = 16 * 60;
int WIDTH = 16 * 80;
int H_PADDING = 1;
Color MY_BACKGROUND_COLOR = GetColor(0x505050);

int main()
{
    Wav wav;

    // Extract signal from the WAV file
    auto sig = wav.extract_signal("audio6.wav");

    const float sig_time = sig.samples.size() / static_cast<float>(sig.samplerate);

    InitWindow(WIDTH, HEIGHT, "Fourier");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MY_BACKGROUND_COLOR);

        float largest_val_in_sig = *std::max_element(sig.samples.begin(), sig.samples.end());

        // scaling the signal to fill out the entire window minus padding at top and bottom of 50 pixels
        float y_scale = (HEIGHT - 2 * H_PADDING) / (2 * largest_val_in_sig);
        float smallest_pos_val = 1.0f / y_scale;

        int step_size = sig.samples.size() / WIDTH;

        // for loop to draw data points
        for (size_t i = 0; i < WIDTH; i++)
        {
            int idx = i * step_size;
            float y_pos = std::abs(sig.samples[idx] * y_scale);

            y_pos = std::max(y_pos, 1.0f);

            Vector2 start_pos = Vector2{.x = static_cast<float>(i), .y = (HEIGHT / 2) - (y_pos)};
            Vector2 end_pos = Vector2{.x = static_cast<float>(i), .y = (HEIGHT / 2) + (y_pos)};
            DrawLineEx(start_pos, end_pos, 1, RED);
            DrawText(TextFormat("%i", sig.samplerate), WIDTH / 4, HEIGHT / 4, 30, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();
}