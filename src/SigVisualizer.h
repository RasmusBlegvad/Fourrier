#pragma once
#include "Wav.h"
#include <cstdint>
#include <vector>

class SigVisualizer
{
private:
public:
    SigVisualizer() = default;
    ~SigVisualizer() = default;

    struct Screen
    {
        int HEIGHT;
        int WIDTH;
        int H_PADDING;
        int W_PADDING;
    };


    void plot_signal(const SigProccesing::t_signal &signal, const struct Screen &screen);
    void plot_signal(const SigProccesing::f_signal &signal, const struct Screen &screen);

    void plot_axis(const struct Screen &screen);
};
