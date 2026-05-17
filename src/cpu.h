#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define MEM_SIZE  65536   // 64KB RAM
#define NUM_REGS  8       // R0-R7
#define STACK_BASE 0xFFFF // Stack pointer starts here, grows down

// Flag register bits
#define FLAG_ZERO     0x01  // Bit 0
#define FLAG_CARRY    0x02  // Bit 1
#define FLAG_OVERFLOW 0x04  // Bit 2
#define FLAG_NEGATIVE 0x08  // Bit 3

// Opcodes
#define OP_MOV_RR   0x01  // MOV Rd, Rs
#define OP_MOV_RI   0x02  // MOV Rd, #imm
#define OP_ADD      0x03  // ADD Rd, Rs, Rt
#define OP_SUB      0x04  // SUB Rd, Rs, Rt
#define OP_MUL      0x05  // MUL Rd, Rs, Rt
#define OP_DIV      0x06  // DIV Rd, Rs, Rt
#define OP_AND      0x07  // AND Rd, Rs, Rt
#define OP_OR       0x08  // OR  Rd, Rs, Rt
#define OP_XOR      0x09  // XOR Rd, Rs, Rt
#define OP_NOT      0x0A  // NOT Rd, Rs
#define OP_SHL      0x0B  // SHL Rd, Rs, #n
#define OP_SHR      0x0C  // SHR Rd, Rs, #n
#define OP_CMP      0x0D  // CMP Rs, Rt
#define OP_JMP      0x0E  // JMP addr
#define OP_JZ       0x0F  // JZ  addr
#define OP_JNZ      0x10  // JNZ addr
#define OP_JL       0x11  // JL  addr
#define OP_JG       0x12  // JG  addr
#define OP_CALL     0x13  // CALL addr
#define OP_RET      0x14  // RET
#define OP_PUSH     0x15  // PUSH Rs
#define OP_POP      0x16  // POP  Rd
#define OP_IN       0x17  // IN   Rd
#define OP_OUT      0x18  // OUT  Rs
#define OP_HLT      0xFF  // HLT

typedef struct {
    uint8_t  mem[MEM_SIZE];      // Main memory
    uint32_t reg[NUM_REGS];      // General-purpose registers R0-R7
    uint32_t pc;                 // Program counter
    uint32_t sp;                 // Stack pointer
    uint8_t  flags;              // Flag register (Z, C, V, N)
    int      halted;             // Execution halted flag
} CPU;

/**
 * cpu_init - Initialize the CPU state
 * @cpu: Pointer to CPU struct
 *
 * Sets all registers to 0, PC to 0x0000, SP to STACK_BASE, flags to 0, halted to 0.
 */
void cpu_init(CPU *cpu);

/**
 * cpu_run - Execute fetch-decode-execute loop
 * @cpu: Pointer to CPU struct
 *
 * Runs until cpu->halted is set to 1.
 */
void cpu_run(CPU *cpu);

/**
 * cpu_step - Execute one instruction
 * @cpu: Pointer to CPU struct
 *
 * Fetches, decodes, and executes a single instruction.
 * Returns 0 on success, non-zero on error.
 */
int cpu_step(CPU *cpu);

/**
 * cpu_execute - Execute a single decoded instruction
 * @cpu: Pointer to CPU struct
 * @opcode: The instruction opcode
 *
 * Dispatcher function that routes to specific instruction handlers.
 * Returns 0 on success, non-zero on error (e.g., division by zero).
 */
int cpu_execute(CPU *cpu, uint8_t opcode);

/**
 * cpu_load_binary - Load a binary file into memory
 * @cpu: Pointer to CPU struct
 * @filename: Path to .bin file
 *
 * Reads the binary file and writes it starting at address 0x0000.
 * Returns 0 on success, -1 on error.
 */
int cpu_load_binary(CPU *cpu, const char *filename);

#endif // CPU_H
