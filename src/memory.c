#include <stdio.h>
#include <string.h>
#include "memory.h"

int mem_read8(CPU *cpu, uint32_t addr, uint8_t *value) {
    if (addr >= MEM_SIZE) {
        fprintf(stderr, "[MEM ERROR] Read out of bounds at 0x%08X\n", addr);
        return -1;
    }
    *value = cpu->mem[addr];
    return 0;
}

int mem_read16(CPU *cpu, uint32_t addr, uint16_t *value) {
    if (addr + 1 >= MEM_SIZE) {
        fprintf(stderr, "[MEM ERROR] Read out of bounds at 0x%08X (16-bit)\n", addr);
        return -1;
    }
    // Little-endian: LSB at addr, MSB at addr+1
    *value = (uint16_t)cpu->mem[addr] | ((uint16_t)cpu->mem[addr + 1] << 8);
    return 0;
}

int mem_read32(CPU *cpu, uint32_t addr, uint32_t *value) {
    if (addr + 3 >= MEM_SIZE) {
        fprintf(stderr, "[MEM ERROR] Read out of bounds at 0x%08X (32-bit)\n", addr);
        return -1;
    }
    // Little-endian
    *value = (uint32_t)cpu->mem[addr] |
             ((uint32_t)cpu->mem[addr + 1] << 8) |
             ((uint32_t)cpu->mem[addr + 2] << 16) |
             ((uint32_t)cpu->mem[addr + 3] << 24);
    return 0;
}

int mem_write8(CPU *cpu, uint32_t addr, uint8_t value) {
    if (addr >= MEM_SIZE) {
        fprintf(stderr, "[MEM ERROR] Write out of bounds at 0x%08X\n", addr);
        return -1;
    }
    cpu->mem[addr] = value;
    return 0;
}

int mem_write16(CPU *cpu, uint32_t addr, uint16_t value) {
    if (addr + 1 >= MEM_SIZE) {
        fprintf(stderr, "[MEM ERROR] Write out of bounds at 0x%08X (16-bit)\n", addr);
        return -1;
    }
    // Little-endian
    cpu->mem[addr] = (uint8_t)(value & 0xFF);
    cpu->mem[addr + 1] = (uint8_t)((value >> 8) & 0xFF);
    return 0;
}

int mem_write32(CPU *cpu, uint32_t addr, uint32_t value) {
    if (addr + 3 >= MEM_SIZE) {
        fprintf(stderr, "[MEM ERROR] Write out of bounds at 0x%08X (32-bit)\n", addr);
        return -1;
    }
    // Little-endian
    cpu->mem[addr] = (uint8_t)(value & 0xFF);
    cpu->mem[addr + 1] = (uint8_t)((value >> 8) & 0xFF);
    cpu->mem[addr + 2] = (uint8_t)((value >> 16) & 0xFF);
    cpu->mem[addr + 3] = (uint8_t)((value >> 24) & 0xFF);
    return 0;
}

void mem_dump(CPU *cpu, uint32_t addr, int n) {
    printf("[Memory dump at 0x%08X (%d bytes)]\n", addr, n);
    for (int i = 0; i < n; i++) {
        if (i % 16 == 0) {
            printf("0x%08X: ", addr + i);
        }
        uint8_t byte;
        if (mem_read8(cpu, addr + i, &byte) == 0) {
            printf("%02X ", byte);
        } else {
            printf("XX ");
        }
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    if (n % 16 != 0) {
        printf("\n");
    }
}
