#pragma once

class RAM;

class PIA {
	public:
		PIA(RAM* memory);
		void setCycle(short int&& value);
		void tick();
	private:
        RAM* memory = nullptr;
        short int currentInterval = -1;
        short int lastInterval = -1;
};
