#ifndef ALU_H
#define ALU_H

#include <stdint.h>
#include "cpu.h"

/**
 * alu_add - Perform unsigned addition
 * @a: First operand
 * @b: Second operand
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_add(uint32_t a, uint32_t b, uint32_t *result);

/**
 * alu_sub - Perform unsigned subtraction
 * @a: First operand
 * @b: Second operand
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_sub(uint32_t a, uint32_t b, uint32_t *result);

/**
 * alu_mul - Perform unsigned multiplication
 * @a: First operand
 * @b: Second operand
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_mul(uint32_t a, uint32_t b, uint32_t *result);

/**
 * alu_div - Perform unsigned division
 * @a: Dividend
 * @b: Divisor
 * @result: Pointer to store the result
 *
 * Returns 0 on success, -1 on division by zero.
 */
int alu_div(uint32_t a, uint32_t b, uint32_t *result);

/**
 * alu_and - Perform bitwise AND
 * @a: First operand
 * @b: Second operand
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_and(uint32_t a, uint32_t b, uint32_t *result);

/**
 * alu_or - Perform bitwise OR
 * @a: First operand
 * @b: Second operand
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_or(uint32_t a, uint32_t b, uint32_t *result);

/**
 * alu_xor - Perform bitwise XOR
 * @a: First operand
 * @b: Second operand
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_xor(uint32_t a, uint32_t b, uint32_t *result);

/**
 * alu_not - Perform bitwise NOT
 * @a: Operand
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_not(uint32_t a, uint32_t *result);

/**
 * alu_shl - Perform left shift
 * @a: Value to shift
 * @n: Shift amount
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_shl(uint32_t a, uint32_t n, uint32_t *result);

/**
 * alu_shr - Perform right shift
 * @a: Value to shift
 * @n: Shift amount
 * @result: Pointer to store the result
 *
 * Returns 0 on success.
 */
int alu_shr(uint32_t a, uint32_t n, uint32_t *result);

/**
 * alu_update_flags - Update CPU flags based on operation result
 * @cpu: Pointer to CPU struct
 * @result: The operation result
 * @a: First operand (for overflow detection)
 * @b: Second operand (for overflow detection)
 * @operation: Operation type (OP_ADD, OP_SUB, etc.)
 *
 * Sets Zero, Carry, Overflow, and Negative flags appropriately.
 */
void alu_update_flags(CPU *cpu, uint32_t result, uint32_t a, uint32_t b, uint8_t operation);

/**
 * alu_flag_string - Get human-readable flag state
 * @cpu: Pointer to CPU struct
 * @buffer: Character buffer to write flag string to (must be at least 20 bytes)
 *
 * Writes a string like "[Z:1 C:0 N:0 V:0]" to the buffer.
 */
void alu_flag_string(CPU *cpu, char *buffer);

#endif // ALU_H
