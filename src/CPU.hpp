#pragma once

#include <vector>

#include "RAM.hpp"

class CPU
{
    public:
        CPU(RAM* memory);

        int getFlag(char&& flag);
        void lock();
        void pulse();
        void setFlag(char&& flag, int value);
        void setCycle(int cycle);
        void setCycle(int cycle, uint16_t address, uint16_t addressWithOffset);
        void unlock();
    private:
		RAM* memory = nullptr;

		bool active = true;
        uint8_t cycle = 0;

        uint8_t* rom = nullptr;
        uint8_t A = 0x00;
        uint8_t X = 0x00;
        uint8_t Y = 0x00;
        uint8_t S = 0xFF;
        uint8_t P = 0x20;
        uint16_t PC = 0xF000;

		void resetVector();

        uint16_t ADDRAbsolute();
        uint16_t ADDRAbsoluteX();
        uint16_t ADDRImmediate();
        uint16_t ADDRZeropage();
		uint16_t ADDRZeropageX();

        void BIT(uint16_t address);
        void CJMP(char&& flag, bool&& value);
        void CMP(uint16_t address);
		void DEX();
		void DEY();
		void INC(uint16_t address);
		void INX();
        void JMP(uint16_t address);
        void JSR(uint16_t address);
        void LDA(uint16_t address);
        void LDX(uint16_t address);
        void LDY(uint16_t address);
		uint8_t POP();
        void PUSH(uint8_t value);
        void ROL(uint16_t address);
		void RTS();
        void STA(uint16_t address);
        void STY(uint16_t address);
		void STX(uint16_t address);
        void TXS();
};
