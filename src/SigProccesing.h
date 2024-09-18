#pragma once

#include <vector>
#include <cstdint>
#include <complex>

namespace  SigProccesing
{
    struct t_signal
    {
        std::vector<double> samples;
        uint32_t samplerate;
    };

    struct f_signal
    {
        std::vector<std::complex<double>> samples;
        std::vector<double> magnitudes;
        uint32_t samplerate;

    };

    f_signal DFT(const t_signal &sig);

    t_signal generate_sine(double frequency, double duration, uint32_t samplerate, double phase = 0);
};
