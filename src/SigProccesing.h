#pragma once

#include <vector>
#include <cstdint>
#include <complex>

#include "Wav.h"

namespace SigProccesing
{
    // Wav::Signal DFT(const Wav::Signal& sig);
    //
    // Wav::Signal FDFT(const Wav::Signal& sig);
    //
    // Wav::Signal generate_sine(double frequency, double duration, uint32_t samplerate, double phase = 0);

    double mooving_avg(const std::vector<double>& samples, int avg_window_size, int start_idx, double y_scale);
};
