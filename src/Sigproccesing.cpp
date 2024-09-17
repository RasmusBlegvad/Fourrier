#include "SigProccesing.h"
#include "Wav.h"
#include <complex>
#include <iostream>
#include <numbers>

using namespace std::complex_literals;

SigProccesing::f_signal SigProccesing::DFT(const SigProccesing::t_signal &sig)
{
    std::complex<double> sum;
    double const N = sig.samples.size();
    double constexpr pi = std::numbers::pi;
    std::vector<std::complex<double>> dft_samples;
    std::vector<double> dft_magnitudes;

    for (size_t i = 0; i < N / 2 - 1; i++)
    {
        // std::cout << i << "\n";
        sum = 0;
        for (size_t j = 0; j < N; j++)
        {
            auto k = static_cast<double>(i);
            auto n = static_cast<double>(j);

            std::complex<double> temp = sig.samples[j] * exp(-1.0i * 2.0 * pi * k * n / N);
            sum += temp;
        }
        dft_samples.push_back(sum);
        dft_magnitudes.emplace_back(std::abs(sum));

    }
    std::cout << "done";
    return {.samples = dft_samples, .magnitudes = dft_magnitudes , .samplerate = sig.samplerate}; // return the dft
}