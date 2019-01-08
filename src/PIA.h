#pragma once

class RAM;

class PIA {
	private:
		RAM* memory = nullptr;
		short int currentCycle = -1;
		short int initializedCycle = -1;
	public:
		PIA(RAM*& memory);
		void setCycle(short int&& value);
		void tick();
};
