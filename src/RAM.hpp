#pragma once

#include <stdint.h>
#include <vector>

class CPU;
class PIA;
class TIA;

class RAM
{
    public:
		RAM(std::vector<uint8_t> rom);
        uint8_t get(uint16_t address);
        void set(uint16_t address, uint8_t value);
        void setComponents(CPU* cpu, PIA* pia, TIA* tia);
    private:
        CPU* cpu = nullptr;
		PIA* pia = nullptr;
		TIA* tia = nullptr;
        std::vector<uint8_t> map;
};
