#include <stdio.h>
#include <string.h>
#include "alu.h"

int alu_add(uint32_t a, uint32_t b, uint32_t *result) {
    *result = a + b;
    return 0;
}

int alu_sub(uint32_t a, uint32_t b, uint32_t *result) {
    *result = a - b;
    return 0;
}

int alu_mul(uint32_t a, uint32_t b, uint32_t *result) {
    *result = a * b;
    return 0;
}

int alu_div(uint32_t a, uint32_t b, uint32_t *result) {
    if (b == 0) {
        fprintf(stderr, "[CPU ERROR] Division by zero\n");
        return -1;
    }
    *result = a / b;
    return 0;
}

int alu_and(uint32_t a, uint32_t b, uint32_t *result) {
    *result = a & b;
    return 0;
}

int alu_or(uint32_t a, uint32_t b, uint32_t *result) {
    *result = a | b;
    return 0;
}

int alu_xor(uint32_t a, uint32_t b, uint32_t *result) {
    *result = a ^ b;
    return 0;
}

int alu_not(uint32_t a, uint32_t *result) {
    *result = ~a;
    return 0;
}

int alu_shl(uint32_t a, uint32_t n, uint32_t *result) {
    *result = a << (n & 0x1F);  // Limit shift to 31 bits
    return 0;
}

int alu_shr(uint32_t a, uint32_t n, uint32_t *result) {
    *result = a >> (n & 0x1F);  // Limit shift to 31 bits
    return 0;
}

void alu_update_flags(CPU *cpu, uint32_t result, uint32_t a, uint32_t b, uint8_t operation) {
    // Clear all flags
    cpu->flags = 0;

    // Zero flag: set if result is 0
    if (result == 0) {
        cpu->flags |= FLAG_ZERO;
    }

    // Negative flag: set if MSB is 1
    if ((int32_t)result < 0) {
        cpu->flags |= FLAG_NEGATIVE;
    }

    // Carry and Overflow flags (for arithmetic operations)
    if (operation == OP_ADD) {
        // Carry: set if unsigned overflow
        if (result < a || result < b) {
            cpu->flags |= FLAG_CARRY;
        }
        // Overflow: set if signed overflow
        // (same sign inputs, different sign output)
        int32_t a_signed = (int32_t)a;
        int32_t b_signed = (int32_t)b;
        int32_t result_signed = (int32_t)result;
        if ((a_signed > 0 && b_signed > 0 && result_signed < 0) ||
            (a_signed < 0 && b_signed < 0 && result_signed > 0)) {
            cpu->flags |= FLAG_OVERFLOW;
        }
    } else if (operation == OP_SUB) {
        // Carry: set if unsigned underflow (a < b)
        if (a < b) {
            cpu->flags |= FLAG_CARRY;
        }
        // Overflow: signed underflow detection
        int32_t a_signed = (int32_t)a;
        int32_t b_signed = (int32_t)b;
        int32_t result_signed = (int32_t)result;
        if ((a_signed > 0 && b_signed < 0 && result_signed < 0) ||
            (a_signed < 0 && b_signed > 0 && result_signed > 0)) {
            cpu->flags |= FLAG_OVERFLOW;
        }
    }
}

void alu_flag_string(CPU *cpu, char *buffer) {
    snprintf(buffer, 20, "[Z:%d C:%d V:%d N:%d]",
             (cpu->flags & FLAG_ZERO) ? 1 : 0,
             (cpu->flags & FLAG_CARRY) ? 1 : 0,
             (cpu->flags & FLAG_OVERFLOW) ? 1 : 0,
             (cpu->flags & FLAG_NEGATIVE) ? 1 : 0);
}
