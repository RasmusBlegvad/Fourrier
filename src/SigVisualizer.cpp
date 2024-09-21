#include "SigVisualizer.h"
#include <raylib.h>
#include <algorithm>
#include <format>
#include <iostream>
#include <complex>

namespace SigVisualizer
{
    void plot_axis_t_sig(int screenWidth, int screenHeight, int h_padding, int w_padding, const Wav::Signal& sig)
    {
        // CONSTANTS USED OFR DRAWING LINES I GUESS
        const int drawable_width = screenWidth - 2 * w_padding;
        const int sig_duration = static_cast<int>(sig.samples.size()) / sig.samplerate;
        const int time_step = drawable_width / sig_duration;

        // X AND Y AXIS
        const auto x_axis_start_pos = Vector2{.x = 50, .y = static_cast<float>((screenHeight - 50))};
        const auto x_axis_end_pos = Vector2{
            .x = static_cast<float>(screenWidth - 50), .y = static_cast<float>((screenHeight - 50))
        };

        const auto y_axis_start_pos = Vector2{.x = 50, .y = 50.0f};
        const auto y_axis_end_pos = Vector2{.x = 50, .y = static_cast<float>(screenHeight - 50)};

        DrawLineEx(y_axis_start_pos, y_axis_end_pos, 1,WHITE);
        DrawLineEx(x_axis_start_pos, x_axis_end_pos, 1,WHITE);

        // TIME MARKERS:
        for (int i = 0; i <= sig_duration; i++) // Iterate based on the signal duration
        {
            // Draw vertical lines at intervals of 'time_step' pixels
            int x_pos = w_padding + i * time_step;
            DrawLine(x_pos, screenHeight - 50, x_pos, screenHeight - 40, WHITE);

            // Draw the actual time at the same interval
            DrawTextEx(GetFontDefault(), TextFormat("%i", i), {
                           .x = static_cast<float>(x_pos) - 3, .y = static_cast<float>(screenHeight - 35)
                       }, 15, 1, WHITE);
        }

        // AMP MARKERS:
        // 1.0
        DrawText("1.0", w_padding - 40, h_padding - GetFontDefault().baseSize / 2 - 2, 15, WHITE);
        DrawLine(w_padding, h_padding, w_padding - 10, h_padding, WHITE);
        // 0.0
        DrawText("0.0", w_padding - 40, screenHeight / 2 - GetFontDefault().baseSize / 2 - 2, 15, WHITE);
        DrawLine(w_padding, screenHeight / 2, w_padding - 10, screenHeight / 2, WHITE);
        // -1.0
        DrawText("-1.0", w_padding - 40, screenHeight - (50 + GetFontDefault().baseSize / 2) - 2, 15, WHITE);
        DrawLine(w_padding, screenHeight - 50, w_padding - 10, screenHeight - 50, WHITE);

        // CENTER LINE:
        constexpr int gap = 10;
        constexpr int dot_len = 10;
        constexpr int total_steps = gap + dot_len;
        for (int i = 0; i <= drawable_width / total_steps; i++)
        {
            DrawLine(w_padding + i * (dot_len + gap), screenHeight / 2,
                     w_padding + i * (dot_len + gap) + dot_len, screenHeight / 2, GetColor(0x808080FF));
        }
    }

    // void plot_axis_f_sig(const struct Screen& screen, const SigProccesing::f_signal& sig)
    // {
    //     // CONSTANTS USED OFR DRAWING LINES I GUESS
    //     const int drawable_width = screen.WIDTH - 2 * screen.W_PADDING;
    //
    //     // X AND Y AXIS
    //     const auto x_axis_start_pos = Vector2{.x = 50, .y = static_cast<float>((screen.HEIGHT - 50))};
    //     const auto x_axis_end_pos = Vector2{
    //         .x = static_cast<float>(screen.WIDTH - 50), .y = static_cast<float>((screen.HEIGHT - 50))
    //     };
    //
    //     const auto y_axis_start_pos = Vector2{.x = 50, .y = 50.0f};
    //     const auto y_axis_end_pos = Vector2{.x = 50, .y = static_cast<float>(screen.HEIGHT - 50)};
    //
    //     DrawLineEx(y_axis_start_pos, y_axis_end_pos, 1,WHITE);
    //     DrawLineEx(x_axis_start_pos, x_axis_end_pos, 1,WHITE);
    //
    //
    //     // CENTER LINE:
    //     constexpr int gap = 10;
    //     constexpr int dot_len = 10;
    //     constexpr int total_steps = gap + dot_len;
    //     for (int i = 0; i <= drawable_width / total_steps; i++)
    //     {
    //         DrawLine(screen.W_PADDING + i * (dot_len + gap), screen.HEIGHT / 2,
    //                  screen.W_PADDING + i * (dot_len + gap) + dot_len, screen.HEIGHT / 2, GetColor(0x808080FF));
    //     }
    // }


    // overlaod 1 plotting time domain signals
    void plot_signal(const Wav::Signal& sig, int screenWidth, int screenHeight, int h_padding, int w_padding,
                     plot_types plot_type)
    {
        // extracting only real values
        std::vector<double> r_samples(sig.samples.size());
        for (int i = 0; i < sig.samples.size(); ++i)
        {
            r_samples[i] = std::real(sig.samples[i]);
        }

        // scaling the signal to fill out the entire window minus padding at top and bottom of 50 pixels
        double largest_val_in_sig = *std::ranges::max_element(r_samples.begin(), r_samples.end());
        double y_scale = (screenHeight - 2 * h_padding) / (2 * largest_val_in_sig);

        int drawable_width = screenWidth - 2 * w_padding;
        int step_size = sig.samples.size() / drawable_width;

        if (plot_type == WAVEFORM)
        {
            // for loop to draw data points
            for (int i = 0; i < drawable_width; i++)
            {
                int idx = i * step_size;
                double y_pos = std::abs(SigProccesing::mooving_avg(r_samples, step_size, idx, y_scale));
                y_pos = std::max(y_pos, 1.0);
                double x_pos = static_cast<float>(i + w_padding);

                auto start_pos = Vector2{.x = x_pos, .y = (screenHeight / 2) - y_pos};
                auto end_pos = Vector2{.x = x_pos, .y = (screenHeight / 2) + y_pos};
                DrawLineEx(start_pos, end_pos, 1, RED);
            }

            plot_axis_t_sig(screenWidth, screenHeight, h_padding, h_padding, sig);
        }
        else if (plot_type == ENVELOPE)
        {
            for (int i = 0; i < drawable_width; i++)
            {
                int idx = i * step_size;
                int y_pos = r_samples[idx] * y_scale;
                int x_pos = (i + w_padding);

                DrawCircle(x_pos, y_pos + (screenHeight / 2), 1, RED);
            }
            plot_axis_t_sig(screenWidth, screenHeight, h_padding, h_padding, sig);
        }
    }

    // overload 2 ploting signals in frequincy domain
    // void plot_signal(const SigProccesing::f_signal& sig, const struct Screen& screen)
    // {
    //     double largest_val_in_sig = *std::ranges::max_element(sig.magnitudes.begin(), sig.magnitudes.end());
    //     // scaling the signal to fill out the entire window minus padding at top and bottom of 50 pixels
    //     float y_scale = (screen.HEIGHT - 2 * screen.H_PADDING) / (2 * largest_val_in_sig);
    //
    //     int drawable_width = screen.WIDTH - 2 * screen.W_PADDING;
    //     int step_size = sig.magnitudes.size() / drawable_width;
    //
    //     // for loop to draw data points
    //     for (size_t i = 0; i < drawable_width; i++)
    //     {
    //         int idx = i * step_size;
    //         double y_pos = std::abs(SigProccesing::mooving_avg(sig.magnitudes, step_size, idx, y_scale));
    //         //y_pos = std::max(y_pos, 1.0);
    //         double x_pos = static_cast<float>(i + screen.W_PADDING);
    //
    //         auto start_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) - y_pos};
    //         auto end_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) + y_pos};
    //         DrawLineEx(start_pos, end_pos, 1, RED);
    //     }
    //     plot_axis_f_sig(screen, sig);
    // }
}
