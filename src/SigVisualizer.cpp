#include "SigVisualizer.h"
#include <raylib.h>
#include <algorithm>

void SigVisualizer::plot_signal(const Wav::Signal &sig, const struct Screen &screen)
{
    float largest_val_in_sig = *std::max_element(sig.samples.begin(), sig.samples.end());

    // scaling the signal to fill out the entire window minus padding at top and bottom of 50 pixels
    float y_scale = (screen.HEIGHT - 2 * screen.H_PADDING) / (2 * largest_val_in_sig);
    float smallest_pos_val = 1.0f / y_scale;

    int step_size = sig.samples.size() / screen.WIDTH;

    // for loop to draw data points
    for (size_t i = 0; i < screen.WIDTH; i++)
    {
        int idx = i * step_size;
        float y_pos = std::abs(sig.samples[idx] * y_scale);

        y_pos = std::max(y_pos, 1.0f);

        Vector2 start_pos = Vector2{.x = static_cast<float>(i), .y = (screen.HEIGHT / 2) - (y_pos)};
        Vector2 end_pos = Vector2{.x = static_cast<float>(i), .y = (screen.HEIGHT / 2) + (y_pos)};
        DrawLineEx(start_pos, end_pos, 1, RED);
        DrawText(TextFormat("%i", sig.samplerate), screen.WIDTH / 4, screen.HEIGHT / 4, 30, WHITE);
    }
}