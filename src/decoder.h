#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include "cpu.h"

/**
 * decoder_read_opcode - Read and advance past the opcode
 * @cpu: Pointer to CPU struct
 *
 * Reads the byte at PC and increments PC.
 * Returns the opcode byte.
 */
uint8_t decoder_read_opcode(CPU *cpu);

/**
 * decoder_read_operand8 - Read 8-bit operand and advance PC
 * @cpu: Pointer to CPU struct
 *
 * Returns the 8-bit operand at PC and increments PC.
 */
uint8_t decoder_read_operand8(CPU *cpu);

/**
 * decoder_read_operand32 - Read 32-bit operand and advance PC (little-endian)
 * @cpu: Pointer to CPU struct
 *
 * Returns the 32-bit operand at PC and increments PC by 4.
 */
uint32_t decoder_read_operand32(CPU *cpu);

/**
 * decoder_get_mnemonic - Get human-readable mnemonic for opcode
 * @opcode: The opcode byte
 *
 * Returns a string like "MOV", "ADD", "HLT", etc.
 * Returns "???" for unknown opcodes.
 */
const char *decoder_get_mnemonic(uint8_t opcode);

/**
 * decoder_get_operand_count - Get expected number of operands for an opcode
 * @opcode: The opcode byte
 *
 * Returns the expected operand count (0-3).
 * Used by the disassembler.
 */
int decoder_get_operand_count(uint8_t opcode);

#endif // DECODER_H
