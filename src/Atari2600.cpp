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
	this->tia->setVsync(false);
    for (int scanline = 0; scanline < 262; ++scanline) {
        if (this->tia->getVsync()) break;
        this->nextScanline(renderer, scanline, scanline > 30 && scanline < 252);
        this->cpu->unlock();
    }
    SDL_RenderPresent(renderer);
}

void Atari2600::nextScanline(SDL_Renderer* renderer, short int scanline, bool draw)
{
	for (int clock = 3; clock < 68; clock += 3) {
        this->pia->tick();
    	this->cpu->pulse();
    }

    for (int clock = 68; clock < 228; clock += 3) {
		this->pia->tick();
		this->cpu->pulse();
		if (draw) {
			this->tia->draw(renderer, clock - 68, scanline - 30);
		}
    }
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
    TIA* tia = new TIA(ram);

    ram->setComponents(cpu, pia, tia);

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
