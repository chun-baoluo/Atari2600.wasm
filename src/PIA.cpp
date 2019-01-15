#include <stdint.h>
#include <stdio.h>

#include "PIA.hpp"
#include "RAM.hpp"

PIA::PIA(RAM* memory)
{
	this->memory = memory;
	this->memory->set(0x284, rand() % 0xFF + 1);
}

void PIA::setCycle(short int&& value)
{
	this->lastInterval = value;
	this->currentInterval = value;
}

void PIA::tick()
{
	if (this->lastInterval < 0) {
		return;
	}

	if (this->currentInterval == 0) {
		uint8_t before = this->memory->get(0x284);
		this->memory->set(0x284, before - 1);
		uint8_t after = this->memory->get(0x284);

		this->currentInterval = this->lastInterval;

		if (before == 0x00 && after == 0xFF) {
			this->lastInterval = -1;
			this->memory->set(0x285, this->memory->get(0x285) | 0xC0); // Underflow
		}
	}

	this->currentInterval--;
}
