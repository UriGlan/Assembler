


#ifndef ASSEMBLER_CONVERTER_H
#define ASSEMBLER_CONVERTER_H

#include <stdio.h>
#include "Handlers/handlers.h"
#include "../Utils/data_structures.h"
#include "../Managers/Managers.h"
#include "../Utils/definitions.h"

/*convert an assembly file to needed files or error file if invalid
 * input: file pointer, line counters*/
void convertFile(FILE *, line_counters *, char *name);

/*updating addresses of symbols word and data after first iteration
 * input: new instruction counter*/
void updateAllAddresses(int);

/*first iteration on the file, here we will update all the addresses and start decoding
 *input: file pointer, ic and dc
 * output: updated addressees and symbol table and semi decoded file*/
void firstIteration(FILE *, int *, int *);

/*update all the remaining addressees*/
void secondIteration();

void macroIteration(FILE *, FILE *);

#endif
