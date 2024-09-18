#include "SigVisualizer.h"
#include <raylib.h>
#include <algorithm>
#include <iostream>

namespace SigVisualizer
{
    void plot_axis_t_sig(const struct Screen &screen,const SigProccesing::t_signal &sig){

        // CONSTANTS USED OFR DRAWING LINES I GUESS
        const int drawable_width = screen.WIDTH - 2 * screen.W_PADDING;
        const int sig_duration =  static_cast<int>(sig.samples.size()) / sig.samplerate;
        const int time_step = drawable_width / sig_duration;

        // X AND Y AXIS
        const auto x_axis_start_pos = Vector2{.x = 50, .y = static_cast<float>((screen.HEIGHT  - 50))};
        const auto x_axis_end_pos = Vector2{.x = static_cast<float>(screen.WIDTH - 50), .y = static_cast<float>((screen.HEIGHT - 50))};

        const auto y_axis_start_pos = Vector2{.x = 50, .y = 50.0f};
        const auto y_axis_end_pos = Vector2{.x = 50, .y = static_cast<float>(screen.HEIGHT - 50)};

        DrawLineEx(y_axis_start_pos,y_axis_end_pos,1,WHITE);
        DrawLineEx(x_axis_start_pos,x_axis_end_pos,1,WHITE);

        // TIME MARKERS:
        for (int i = 0; i <= sig_duration; i++) // Iterate based on the signal duration
        {
            // Draw vertical lines at intervals of 'time_step' pixels
            int x_pos = screen.W_PADDING + i * time_step;
            DrawLine(x_pos, screen.HEIGHT - 50, x_pos, screen.HEIGHT - 40, WHITE);

            // Draw the actual time at the same interval
            DrawTextEx(GetFontDefault(),TextFormat("%i", i),{.x = static_cast<float>(x_pos) - 3, .y = static_cast<float>(screen.HEIGHT - 35)},15, 1, WHITE);
        }

        // AMP MARKERS:
        // 1.0
        DrawText("1.0", screen.W_PADDING - 40, screen.H_PADDING - GetFontDefault().baseSize / 2 - 2, 15, WHITE);
        DrawLine(screen.W_PADDING, screen.H_PADDING, screen.W_PADDING - 10, screen.H_PADDING, WHITE);
        // 0.0
        DrawText("0.0", screen.W_PADDING - 40, screen.HEIGHT / 2 - GetFontDefault().baseSize / 2 - 2, 15, WHITE);
        DrawLine(screen.W_PADDING, screen.HEIGHT / 2, screen.W_PADDING - 10, screen.HEIGHT / 2, WHITE);
        // -1.0
        DrawText("-1.0", screen.W_PADDING - 40, screen.HEIGHT - (50 + GetFontDefault().baseSize / 2) - 2, 15, WHITE);
        DrawLine(screen.W_PADDING, screen.HEIGHT - 50, screen.W_PADDING - 10, screen.HEIGHT - 50, WHITE);

        // CENTER LINE:
        constexpr int gap = 10;
        constexpr int dot_len = 10;
        constexpr int total_steps = gap + dot_len;
        for (int i = 0; i <= drawable_width / total_steps; i++)
        {

            DrawLine(screen.W_PADDING + i * (dot_len + gap),screen.HEIGHT / 2,
                screen.W_PADDING + i * (dot_len + gap) + dot_len,screen.HEIGHT / 2,GetColor(0x808080FF));
        }

    }

    void plot_signal(const SigProccesing::t_signal &sig, const struct Screen &screen,plot_types plot_type)
    {
        // scaling the signal to fill out the entire window minus padding at top and bottom of 50 pixels
        double largest_val_in_sig = *std::ranges::max_element(sig.samples.begin(), sig.samples.end());
        float y_scale = (screen.HEIGHT - 2 * screen.H_PADDING) / (2 * largest_val_in_sig);
        float smallest_pos_val = 1.0f / y_scale;

        int drawable_width = screen.WIDTH - 2 * screen.W_PADDING;
        int step_size = sig.samples.size() / drawable_width;

        if (plot_type == WAVEFORM)
        {
            // for loop to draw data points
            for (size_t i = 0; i < drawable_width; i++)
            {
                int idx = i * step_size;
                double y_pos = std::abs(sig.samples[idx] * y_scale);
                //y_pos = std::max(y_pos, 1.0);
                double x_pos = static_cast<float>(i + screen.W_PADDING);

                auto start_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) - y_pos};
                auto end_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) + y_pos};
                DrawLineEx(start_pos, end_pos, 1, RED);
            }

            plot_axis_t_sig(screen,sig);

        }else if (plot_type == ENVELOPE)
        {
            for (int i = 0; i < drawable_width; i++)
            {
                int idx = i * step_size;
                int y_pos = sig.samples[idx] * y_scale;
                int x_pos = (i + screen.W_PADDING);

                DrawCircle(x_pos, y_pos + (screen.HEIGHT / 2) , 1, RED);

                // auto start_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) - y_pos};
                // auto end_pos = Vector2{.x = x_pos, .y = (screen.HEIGHT / 2) + y_pos};
            }
            plot_axis_t_sig(screen,sig);

        }

    }


    // TODO: Implement plotting that makes sense for DFT
    // TODO: DONT USE LINES
    // TODO: PLOT AXIS IN THIS FUNCTION INSTEAD IF EXTERNAL ONE
    // TODO: MAKE MARKS FOR MAGNITUDE AND FREQUENCY)
    void plot_signal(const SigProccesing::f_signal &sig, const struct Screen &screen)
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
}