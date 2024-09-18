#pragma once
#include "Wav.h"


namespace  SigVisualizer
{
    struct Screen
    {
        int HEIGHT;
        int WIDTH;
        int H_PADDING;
        int W_PADDING;
    };

    enum plot_types
    {
        WAVEFORM = 1,
        ENVELOPE = 2,
    };


    void plot_signal(const SigProccesing::t_signal &signal, const struct Screen &screen,plot_types plot_type);
    void plot_signal(const SigProccesing::f_signal &signal, const struct Screen &screen);

    void plot_axis_t_sig(const struct Screen &screen,const SigProccesing::t_signal &sig);
};
