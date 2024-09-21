#pragma once
#include "Wav.h"


namespace SigVisualizer
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


    void plot_signal(const Wav::Signal& sig, int screenWidth, int screenHeight, int h_padding, int w_padding,
                     plot_types plot_type);
    //void plot_signal(const SigProccesing::f_signal& signal, const struct Screen& screen);

    void plot_axis_t_sig(const struct Screen& screen, const Wav::Signal& sig);
    //void plot_axis_f_sig(const struct Screen& screen, const SigProccesing::f_signal& sig);
};
