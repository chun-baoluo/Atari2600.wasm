#pragma once

#include <SDL2/SDL.h>

#include "CPU.h"
#include "PIA.h"
#include "RAM.h"
#include "ROMReader.h"
#include "TIA.h"

class Atari2600 {
    public:
        Atari2600();
        bool isReady();
        void nextFrame(SDL_Renderer *renderer);
        void start();
        void stop();
    private:
        CPU* cpu = nullptr;
		PIA* pia = nullptr;
        RAM* ram = nullptr;
        ROMReader* reader = nullptr;
		TIA* tia = nullptr;
        bool romLoaded = false;

        void nextScanline(int scanline);
};
