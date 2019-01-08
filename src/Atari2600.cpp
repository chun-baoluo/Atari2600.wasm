#include <stdint.h>

#include "Atari2600.h"
#include "CPU.h"
#include "PIA.h"
#include "RAM.h"
#include "ROMReader.h"
#include "TIA.h"

Atari2600::Atari2600()
{
    this->reader = new ROMReader();
}

bool Atari2600::isReady()
{
    return this->romLoaded;
}

void Atari2600::nextFrame(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
    for(int scanline = 0; scanline <= 262; scanline++) {
        this->nextScanline(scanline);
    }
}

void Atari2600::nextScanline(int scanline)
{
	auto color = TIA::Colors::NTSC[this->ram->get(0x09)];
	// printf("COLORBK: 0x%04X\n", color);
    for(int clock = 0; clock < 228; clock += 3) {
		this->pia->tick();
		this->cpu->pulse();
    }
}

void Atari2600::start()
{
	std::vector<uint8_t> rom = this->reader->read();

    if(rom.empty()) {
        return;
    }

	this->ram = new RAM(rom, this->pia);
    this->cpu = new CPU(this->ram);
	this->pia = new PIA(this->ram);
	this->tia = new TIA();

    this->reader->clear();
    this->romLoaded = true;
}

void Atari2600::stop()
{
    this->romLoaded = false;
}
