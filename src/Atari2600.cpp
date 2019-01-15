#include <stdint.h>

#include "Atari2600.hpp"
#include "CPU.hpp"
#include "PIA.hpp"
#include "RAM.hpp"
#include "ROMReader.hpp"
#include "TIA.hpp"

Atari2600::Atari2600()
{
    this->reader = new ROMReader();
}

bool Atari2600::isReady()
{
    return this->romLoaded;
}

void Atari2600::nextFrame(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);
    for (int scanline = 0; scanline <= 262; ++scanline) {
        this->nextScanline(scanline, renderer, scanline > 30 && scanline < 252);
    }
    SDL_RenderPresent(renderer);
}

void Atari2600::nextScanline(int scanline, SDL_Renderer* renderer, bool draw)
{
	int color = TIA::Colors::NTSC[this->ram->get(0x09)];

	for (int clock = 0; clock < 68; clock += 3) {
        this->pia->tick();
    	this->cpu->pulse();
    }

    for (int clock = 68; clock < 228; clock += 3) {
		this->pia->tick();
		this->cpu->pulse();
		if (draw) {
			SDL_SetRenderDrawColor(renderer, color >> (0x08 * 2), color >> 0x08 & 0xFF, color & 0xFF, 255);
        	SDL_RenderDrawPoint(renderer, clock, scanline);
        	SDL_RenderDrawPoint(renderer, clock + 1, scanline);
            SDL_RenderDrawPoint(renderer, clock + 2, scanline);
		}
    }

    this->cpu->unlock();
}

void Atari2600::start()
{
	std::vector<uint8_t> rom = this->reader->read();

    if (rom.empty()) {
        return;
    }

    RAM* ram = new RAM(rom);
    CPU* cpu = new CPU(ram);
    PIA* pia = new PIA(ram);
    TIA* tia = new TIA();

    ram->setComponents(cpu, pia);

	this->ram = ram;
    this->cpu = cpu;
	this->pia = pia;
	this->tia = tia;

    this->reader->clear();
    this->romLoaded = true;
}

void Atari2600::stop()
{
    this->romLoaded = false;
}
