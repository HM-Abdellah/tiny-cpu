#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

#define MAX_SYMBOLS 256
#define MAX_LABEL_LEN 64
#define MAX_LINE_LEN 256

typedef struct {
    char name[MAX_LABEL_LEN];
    uint32_t address;
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

/**
 * assembler_assemble - Two-pass assembler that converts .asm to .bin
 * @input_file: Path to .asm source file
 * @output_file: Path to .bin output file
 *
 * Pass 1: Parse labels and build symbol table.
 * Pass 2: Emit binary, resolving label references.
 *
 * Returns 0 on success, -1 on error (prints error message to stderr).
 */
int assembler_assemble(const char *input_file, const char *output_file);

/**
 * symbol_table_add - Add a label and its address to the symbol table
 * @table: Pointer to symbol table
 * @name: Label name (without colon)
 * @address: Address value
 *
 * Returns 0 on success, -1 if table is full.
 */
int symbol_table_add(SymbolTable *table, const char *name, uint32_t address);

/**
 * symbol_table_lookup - Look up a label's address
 * @table: Pointer to symbol table
 * @name: Label name (without colon)
 * @address: Pointer to store the address
 *
 * Returns 0 if found, -1 if not found.
 */
int symbol_table_lookup(SymbolTable *table, const char *name, uint32_t *address);

/**
 * symbol_table_clear - Clear all symbols
 * @table: Pointer to symbol table
 */
void symbol_table_clear(SymbolTable *table);

#endif // ASSEMBLER_H
