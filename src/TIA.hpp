#pragma once

#include "RAM.hpp"

#include <map>
#include <SDL2/SDL.h>

class RAM;

class TIA {
	public:
		static struct Colors {
			static std::map<int, int> NTSC;
		};

        TIA(RAM* ram);
        void draw(SDL_Renderer* renderer, short int clock, short int scanline);
        bool getVsync();
        void setVsync(bool vsync);
	private:
	    bool vsync = false;
	    RAM* ram = nullptr;
};
