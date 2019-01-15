#include <stdint.h>
#include <stdio.h>
#include <vector>

#include "CPU.hpp"
#include "PIA.hpp"
#include "RAM.hpp"

RAM::RAM(std::vector<uint8_t> rom)
{
	std::vector<uint8_t> sliced(0xF000, 0x00);

	sliced.insert(
		sliced.end(),
		std::make_move_iterator(rom.begin()),
		std::make_move_iterator(rom.end())
	);

	this->map = sliced;
}

uint8_t RAM::get(uint16_t address)
{
	switch (address) {
		#include "RAM_read.inc.cpp"
	}

    return this->map[address];
}

void RAM::set(uint16_t address, uint8_t value)
{
	switch (address) {
		#include "RAM_write.inc.cpp"
	}

    this->map[address] = value;
}

void RAM::setComponents(CPU* cpu, PIA* pia)
{
    this->cpu = cpu;
	this->pia = pia;
}
