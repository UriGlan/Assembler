

#ifndef ASSEMBLER_ASSEMBLER_UTILS_H
#define ASSEMBLER_ASSEMBLER_UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "definitions.h"
#include "data_structures.h"

/*checks if pointer is null after allocation
 * input: pointer
 * output: error message in null */
 void checkAllocation(void *);

/*get a label by string and check if valid
 * input: label as string
 * output: label is exist, null if it does'nt
 * and if illegal or reserved by flags*/
char *getLabel(char *);

/* finds out directive type base on string input
 * input: string
 * output: directive type*/
directive getDirective(char *);

/*checks if word is comment
 * input: word
 * output: isComment*/
boolean isComment(char *);

/*return a substring between 2 indexes
 * input: string, from index, to index
 * output: substring of buff from index to index*/
char *getSubString(char *, size_t, size_t);

/*check is string is known operation
 * input: string
 * output: isOperation boolean
 * */
boolean isOperation(char *);

/*checks if string is register
 * input: string
 * output: isRegister boolean * */
boolean isRegister(char *);

/*determine if word is jump address param
 * input: word
 * output: isJump address type*/
boolean isJump(char *);

/*returns op code table*/
opcode *getOpCodes();

/*convert int x to weird binary where 1=/ 0=.
 * input: number x
 * output: weird binary representation*/
char *convertToWeirdBinary(int);

#endif
