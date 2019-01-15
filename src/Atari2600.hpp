#pragma once

#include <SDL2/SDL.h>

#include "CPU.hpp"
#include "PIA.hpp"
#include "RAM.hpp"
#include "ROMReader.hpp"
#include "TIA.hpp"

class Atari2600 {
    public:
        Atari2600();
        bool isReady();
        void nextFrame(SDL_Renderer* renderer);
        void start();
        void stop();
    private:
        CPU* cpu = nullptr;
		PIA* pia = nullptr;
        RAM* ram = nullptr;
        ROMReader* reader = nullptr;
		TIA* tia = nullptr;
        bool romLoaded = false;

        void nextScanline(int scanline, SDL_Renderer* renderer, bool draw);
};
