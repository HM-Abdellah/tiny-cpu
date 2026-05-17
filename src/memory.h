#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "cpu.h"

/**
 * mem_read8 - Read 8-bit value from memory
 * @cpu: Pointer to CPU struct
 * @addr: Memory address
 * @value: Pointer to store the read value
 *
 * Returns 0 on success, -1 on bounds error.
 */
int mem_read8(CPU *cpu, uint32_t addr, uint8_t *value);

/**
 * mem_read16 - Read 16-bit value from memory (little-endian)
 * @cpu: Pointer to CPU struct
 * @addr: Memory address
 * @value: Pointer to store the read value
 *
 * Returns 0 on success, -1 on bounds error.
 */
int mem_read16(CPU *cpu, uint32_t addr, uint16_t *value);

/**
 * mem_read32 - Read 32-bit value from memory (little-endian)
 * @cpu: Pointer to CPU struct
 * @addr: Memory address
 * @value: Pointer to store the read value
 *
 * Returns 0 on success, -1 on bounds error.
 */
int mem_read32(CPU *cpu, uint32_t addr, uint32_t *value);

/**
 * mem_write8 - Write 8-bit value to memory
 * @cpu: Pointer to CPU struct
 * @addr: Memory address
 * @value: Value to write
 *
 * Returns 0 on success, -1 on bounds error.
 */
int mem_write8(CPU *cpu, uint32_t addr, uint8_t value);

/**
 * mem_write16 - Write 16-bit value to memory (little-endian)
 * @cpu: Pointer to CPU struct
 * @addr: Memory address
 * @value: Value to write
 *
 * Returns 0 on success, -1 on bounds error.
 */
int mem_write16(CPU *cpu, uint32_t addr, uint16_t value);

/**
 * mem_write32 - Write 32-bit value to memory (little-endian)
 * @cpu: Pointer to CPU struct
 * @addr: Memory address
 * @value: Value to write
 *
 * Returns 0 on success, -1 on bounds error.
 */
int mem_write32(CPU *cpu, uint32_t addr, uint32_t value);

/**
 * mem_dump - Dump n bytes of memory to stdout in hex format
 * @cpu: Pointer to CPU struct
 * @addr: Starting address
 * @n: Number of bytes to dump
 */
void mem_dump(CPU *cpu, uint32_t addr, int n);

#endif // MEMORY_H
