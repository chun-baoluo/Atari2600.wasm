#include <stdint.h>

#include "Atari2600.h"
#include "CPU.h"
#include "ROMReader.h"

Atari2600::Atari2600()
{
    this->reader = new ROMReader();
}

bool Atari2600::isReady()
{
    return this->romLoaded;
}

void Atari2600::nextFrame()
{
    // 0 is the pre-render line
    for(int scanline = 0; scanline <= 262; scanline++) {
        this->nextScanline(scanline);
    }
}

void Atari2600::nextScanline(int scanline)
{
    for(int clock = 0; clock < 241; clock++) {
        this->cpu->pulse();
    }
}

void Atari2600::start()
{
	std::vector<uint8_t> rom = this->reader->read();

    if(rom.empty()) {
        return;
    }

    this->cpu = new CPU(rom);
    // this->ppu = new PPU();

    this->reader->clear();
    this->romLoaded = true;
}

void Atari2600::stop()
{
    this->romLoaded = false;
}
