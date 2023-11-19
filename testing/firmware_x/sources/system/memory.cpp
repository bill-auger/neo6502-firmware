// 
// Author: Rien Matthijsse
// 
#include "pico/stdlib.h"
#include "memory.h"
#include "roms.h"

/// <summary>
/// 64k RAM
/// </summary>
uint8_t mem[MEMORY_SIZE];

// address and data registers
uint16_t address;
uint8_t  data;

/// <summary>
/// initialise memory
/// </summary>
void initmemory() {
  address = 0x0000UL;
  data = 0x00;

  // lets install some ROMS
  if (loadROMS()) {
  }
  mem[KBD] = 0x00;
  mem[DSP] = 0x00;
}

/// <summary>
/// store a byte into memory
/// </summary>
void writememory() {

  // if ((0x8000 <= address && address <= 0xCFFF) || (0xF000 <= address && address <= 0xFFF9)) { // exclude writing ROM
  //   Serial.printf("access violation @[%04X]\n", address);
  // }
  // else
  //   mem[address] = data;
}
