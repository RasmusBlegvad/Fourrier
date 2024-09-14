#include <iostream>
#include "WavReader.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main()
{

    WavReader::wav_reader("audio3.wav");
}
