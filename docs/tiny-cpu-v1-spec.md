# Tiny CPU — Learning Specification (v1)

This is a deliberately small **software simulator** of a CPU, implemented in C. It is not a physical processor and is not intended to model any specific commercial CPU.

The original prototype on `main` is preserved. This branch starts a clean, incremental implementation so each component can be understood and tested.

## Learning goals

- Understand registers, RAM, the program counter (PC), opcodes, and the fetch-decode-execute cycle.
- Build the smallest useful CPU before adding an assembler, disassembler, debugger, stack, or advanced instructions.
- Apply defensive C practices: initialize state, validate indices and addresses, avoid undefined behavior, and test edge cases.

## v1 architecture

- **Word/data width:** 8 bits for register values and immediate values (0–255).
- **Memory:** 256 bytes, addresses 0–255. Instructions and data share this memory.
- **Registers:** four 8-bit general-purpose registers: R0–R3.
- **Program counter:** `uint16_t`, so it can represent 256 after the last valid address instead of wrapping to 0.
- **Flags:** one Zero flag, set after arithmetic when the result is 0.
- **Halted state:** a boolean indicating that execution has stopped.
- **Instruction encoding:** every instruction occupies exactly 3 bytes: `[opcode, operand1, operand2]`. Fixed-width instructions make the first implementation easier to inspect. Unused operands must be zero in test programs.

## Instruction set

| Mnemonic | Opcode | Operand 1 | Operand 2 | Meaning |
|---|---:|---|---|---|
| `LDI` | `0x01` | Register index | Immediate byte | `R[operand1] = operand2` |
| `ADD` | `0x02` | Destination register | Source register | Add source to destination, keeping the low 8 bits; update Zero flag |
| `SUB` | `0x03` | Destination register | Source register | Subtract source from destination, keeping the low 8 bits; update Zero flag |
| `OUT` | `0x04` | Register index | Unused (0) | Print the register value |
| `JMP` | `0x05` | Target address | Unused (0) | Set PC to target address |
| `JZ` | `0x06` | Target address | Unused (0) | Jump if Zero flag is set |
| `HLT` | `0xFF` | Unused (0) | Unused (0) | Halt execution |

Register operands must be in the range 0–3. Each fetched instruction must fit completely in RAM. Invalid opcodes, invalid register indices, and out-of-bounds fetches must be reported as errors rather than silently accessing invalid memory.

The PC advances by 3 during normal execution. A taken jump replaces the next PC with its target address. For v1, programs should place jump targets at instruction boundaries.

## First example program

This program sets R0 to 5, R1 to 3, adds R1 to R0, prints R0, and halts.

```text
Address  Bytes         Assembly
0        01 00 05      LDI R0, 5
3        01 01 03      LDI R1, 3
6        02 00 01      ADD R0, R1
9        04 00 00      OUT R0
12       FF 00 00      HLT
```

Expected output: `8`.

## Implementation order

1. Define the CPU state in `cpu.h`.
2. Implement initialization/reset and safe instruction fetch.
3. Implement `cpu_step` (one instruction) and then `cpu_run`.
4. Add each instruction with small tests.
5. Add memory LOAD/STORE, then a text assembler and labels.
6. Add disassembly/debugging only after execution is reliable.
7. Add compiler warnings and tests for invalid instructions, registers, jumps, memory bounds, and arithmetic wraparound.

## Design rule

Do not add features merely because they sound advanced. Every feature must have a clear purpose, a small test, and an explanation of its behavior.
