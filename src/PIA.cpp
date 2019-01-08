#include <stdint.h>
#include <stdio.h>

#include "PIA.h"
#include "RAM.h"

PIA::PIA(RAM*& memory)
{
	this->memory = memory;
}

void PIA::setCycle(short int&& value)
{
	this->initializedCycle = value;
	this->currentCycle = value;
	printf("BEF: 0x%d\n", this->currentCycle);
	printf("BEF2: %d\n", this->initializedCycle);
}

void PIA::tick()
{
	if (this->initializedCycle < 0) {
		return;
	}

	if (this->currentCycle == 0) {
		uint8_t before = this->memory->get(0x284);
		this->memory->set(0x284, before - 1);
		uint8_t after = this->memory->get(0x284);

		this->currentCycle = this->initializedCycle;
		printf("BEF: 0x%02X\n", before);
		printf("AFT: 0x%02X\n", after);

		if (before == 0x00 && after == 0xFF) {
			this->initializedCycle = -1;
			this->memory->set(0x285, this->memory->get(0x285) | 0xC0); // Underflow
		}
	}

	this->currentCycle--;
}
