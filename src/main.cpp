#include <iostream>
#include "WavReader.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>

int main()
{
    Wav wav;

    auto signal = wav.extract_signal("audio5.wav");

    std::cout << "sample rate: " << signal.samplerate << "\n";

    for (size_t i = 0; i < signal.samples.size(); i += 1500)
    {
        std::cout << std::format("sample [{}]: {}\n", i, signal.samples[i]);
    }
}
