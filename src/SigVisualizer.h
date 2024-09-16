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
    };

    void plot_signal(const Wav::Signal &signal, const struct Screen &screen);
};
