#pragma once

#include "Wav.h"
#include "UI.h"

class App
{
public:
   explicit App(const char* title = "Fourrie");

private:
   Wav wav;
   UI ui;

   void game_loop();
};
