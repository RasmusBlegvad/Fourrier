#include "SigProccesing.h"
#include "Wav.h"

#include <algorithm>
#include <complex>
#include <iostream>
#include <numbers>

namespace SigProccesing
{
    double mooving_avg(const std::vector<double>& samples, const int avg_window_size, const int start_idx,
                       const double y_scale)
    {
        double avg = 0;

        int effective_win_size = std::min(avg_window_size, static_cast<int>(samples.size()) - start_idx);

        for (int i = 0; i < effective_win_size; ++i)
        {
            double temp = samples[i + start_idx] * y_scale;
            avg += temp;
        }
        // std::cout << avg << "\n";
        return effective_win_size > 0 ? avg / effective_win_size : 0.0;
    }

    // Wav::Signal generate_sine(const double frequency, const double duration, const uint32_t samplerate,
    //                           const double phase)
    // {
    //     const double num_samples = duration * samplerate;
    //     std::vector<double> sin_sample;
    //
    //
    //     for (int i = 0; i < num_samples; ++i)
    //     {
    //         double time = static_cast<double>(i) / samplerate;
    //         double sig_sample = std::sin(2.0 * M_PI * frequency * time + phase);
    //         sin_sample.push_back(sig_sample);
    //         // std::cout << sig_sample << "\n";
    //     }
    //
    //     return {.samples = sin_sample, .samplerate = samplerate};
    // }
    //
    // // TODO: LOOK INTO FDFT THIS IS SLOW AS FUCK!!!
    // Wav::Signal DFT(const Wav::Signal& sig)
    // {
    //     using namespace std::complex_literals;
    //     std::complex<double> sum;
    //     double const N = sig.samples.size();
    //     double constexpr pi = std::numbers::pi;
    //     std::vector<std::complex<double>> dft_samples;
    //     std::vector<double> dft_magnitudes;
    //
    //     for (size_t i = 0; i < N / 2 - 1; i++)
    //     {
    //         sum = 0;
    //         for (size_t j = 0; j < N; j++)
    //         {
    //             auto k = static_cast<double>(i);
    //             auto n = static_cast<double>(j);
    //
    //             std::complex<double> temp = sig.samples[j] * exp(-1.0i * 2.0 * pi * k * n / N);
    //             sum += temp;
    //         }
    //         dft_samples.push_back(sum);
    //         dft_magnitudes.emplace_back(std::abs(sum));
    //     }
    //
    //     // normalising magnitude
    //     const double largest_val = *std::max_element(dft_magnitudes.begin(), dft_magnitudes.end());
    //     const double norm_factor = 1.0 / largest_val;
    //     std::vector<double> norm_dft_magnitudes;
    //     for (int i = 0; i < dft_magnitudes.size(); ++i)
    //     {
    //         norm_dft_magnitudes.emplace_back(dft_magnitudes[i] * norm_factor);
    //     }
    //
    //     return {.samples = dft_samples, .samplerate = sig.samplerate}; // return the dft
    // }
    //
    // //TODO: Look into Cooley–Tukey FFT algorithm
    // Wav::Signal FDFT(const Wav::Signal& sig)
    // {
    // }
}
