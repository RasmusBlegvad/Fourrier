#include "SigVisualizer.h"
#include <raylib.h>
#include <algorithm>
#include <iostream>

void SigVisualizer::plot_axis(const struct Screen &screen)
{
    // Y-axis
    DrawLine(50, 50, 50, screen.HEIGHT - 50, WHITE);
    // X-axis
    DrawLine(50, screen.HEIGHT - 50, screen.WIDTH - 50, screen.HEIGHT - 50, WHITE);
    // Y axis-label
    DrawText("A", 20, 50, 30, WHITE);
    // X axis-label
    DrawText("t", screen.WIDTH - 72, screen.HEIGHT - 43, 30, WHITE);
}

void SigVisualizer::plot_signal(const SigProccesing::t_signal &sig, const struct Screen &screen)
{
    double largest_val_in_sig = *std::ranges::max_element(sig.samples.begin(), sig.samples.end());

    // scaling the signal to fill out the entire window minus padding at top and bottom of 50 pixels
    float y_scale = (screen.HEIGHT - 2 * screen.H_PADDING) / (2 * largest_val_in_sig);
    float smallest_pos_val = 1.0f / y_scale;

    int drawable_width = screen.WIDTH - 2 * screen.W_PADDING;
    int step_size = sig.samples.size() / drawable_width;

    // for loop to draw data points
    for (size_t i = 0; i < drawable_width; i++)
    {
        int idx = i * step_size;
        double y_pos = std::abs(sig.samples[idx] * y_scale);

        y_pos = std::max(y_pos, 1.0);
        double x_pos = static_cast<float>(i + screen.W_PADDING);

        auto start_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) - y_pos};
        auto end_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) + y_pos};
        DrawLineEx(start_pos, end_pos, 1, RED);
    }
}

void SigVisualizer::plot_signal(const SigProccesing::f_signal &sig, const struct Screen &screen)
{
    double largest_val_in_sig = *std::ranges::max_element(sig.magnitudes.begin(), sig.magnitudes.end());

    // scaling the signal to fill out the entire window minus padding at top and bottom of 50 pixels
    float y_scale = (screen.HEIGHT - 2 * screen.H_PADDING) / (2 * largest_val_in_sig);
    float smallest_pos_val = 1.0f / y_scale;

    int drawable_width = screen.WIDTH - 2 * screen.W_PADDING;
    int step_size = sig.samples.size() / drawable_width;

    // for loop to draw data points
    for (size_t i = 0; i < drawable_width; i++)
    {
        int idx = i * step_size;
        double y_pos = std::abs(sig.magnitudes[idx] * y_scale);

        y_pos = std::max(y_pos, 1.0);
        double x_pos = static_cast<float>(i + screen.W_PADDING);

        auto start_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) - y_pos};
        auto end_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) + y_pos};
        DrawLineEx(start_pos, end_pos, 1, RED);
    }
}
