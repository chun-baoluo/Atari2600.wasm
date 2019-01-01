#pragma once

#include "CPU.h"
#include "RAM.h"
#include "ROMReader.h"

class Atari2600 {
    public:
        Atari2600();
        bool isReady();
        void nextFrame();
        void start();
        void stop();
    private:
        CPU* cpu = nullptr;
        RAM* ram = nullptr;
        ROMReader* reader = nullptr;
        bool romLoaded = false;

        void nextScanline(int scanline);
};
