#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stdint.h>
#include "cpu.h"

/**
 * disassembler_disassemble - Disassemble a binary file
 * @filename: Path to .bin file
 *
 * Reads the binary file and prints disassembled instructions to stdout.
 * Detects jump/call targets and labels them as L_<hex_addr>.
 *
 * Returns 0 on success, -1 on error.
 */
int disassembler_disassemble(const char *filename);

/**
 * disassembler_instr_at - Disassemble a single instruction at a memory address
 * @cpu: Pointer to CPU struct
 * @addr: Address to disassemble
 * @buffer: Output buffer for disassembled string (must be at least 64 bytes)
 *
 * Writes a string like "0x0012: ADD R3, R0, R1" to buffer.
 * Does not modify CPU state.
 *
 * Returns the number of bytes this instruction consumed.
 */
int disassembler_instr_at(CPU *cpu, uint32_t addr, char *buffer);

#endif // DISASSEMBLER_H
