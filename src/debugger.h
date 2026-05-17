#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <stdint.h>
#include "cpu.h"

#define MAX_BREAKPOINTS 32

typedef struct {
    uint32_t addresses[MAX_BREAKPOINTS];
    int count;
} BreakpointList;

/**
 * debugger_run - Start interactive debugging session
 * @cpu: Pointer to CPU struct
 *
 * Presents a prompt and accepts commands (step, continue, breakpoint, etc.).
 * Runs until user quits or CPU halts.
 */
void debugger_run(CPU *cpu);

/**
 * debugger_add_breakpoint - Add a breakpoint at an address
 * @bp_list: Pointer to breakpoint list
 * @addr: Address to break at
 *
 * Returns 0 on success, -1 if list is full.
 */
int debugger_add_breakpoint(BreakpointList *bp_list, uint32_t addr);

/**
 * debugger_remove_breakpoint - Remove a breakpoint
 * @bp_list: Pointer to breakpoint list
 * @addr: Address of breakpoint to remove
 *
 * Returns 0 on success, -1 if not found.
 */
int debugger_remove_breakpoint(BreakpointList *bp_list, uint32_t addr);

/**
 * debugger_has_breakpoint - Check if there's a breakpoint at an address
 * @bp_list: Pointer to breakpoint list
 * @addr: Address to check
 *
 * Returns 1 if breakpoint exists, 0 otherwise.
 */
int debugger_has_breakpoint(BreakpointList *bp_list, uint32_t addr);

/**
 * debugger_print_regs - Print all registers and flags in formatted table
 * @cpu: Pointer to CPU struct
 */
void debugger_print_regs(CPU *cpu);

/**
 * debugger_print_help - Print list of available commands
 */
void debugger_print_help(void);

#endif // DEBUGGER_H
