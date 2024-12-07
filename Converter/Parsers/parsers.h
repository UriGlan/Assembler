


#ifndef ASSEMBLER_PARSERS_H
#define ASSEMBLER_PARSERS_H

#include <stdio.h>
#include <string.h>
#include "../../Utils/data_structures.h"
#include "../Parsers/parsers.h"
#include "../../Utils/definitions.h"
#include "../../Messengers/Messengers.h"

/* parsing the .data directive
 * input: dc , line counter, word and label
 * output: adding all the numbers to the data list*/
void parseDataDirective(int *, int, char *, char *);

/* parsing the .entry directive
 * input: line counter, word
 * output: adding to entry list, return if should continue handling directive*/
boolean parseEntryDirective(int, char *);

/* parsing the .extern directive
 * input:line counter, word
 * output: adding to symbols list, return if should continue handling directive*/
boolean parseExternDirective(int, char *);

/* parsing immediate addressing type
 * input: word , line counter, ic increment value, first -> second  words, isSource flag
 * output: adding all the numbers to the data list, returns if should continue handling*/
boolean parseImmediate(char *, int, int *, word_ptr, word_ptr *, boolean);

/* parsing jump with params addressing type
 * input: word , line counter, ic increment value, first -> fourth  words
 * output: parsing the jump operands, returns if should continue handling*/
boolean parseJump(char *, int, int *, word_ptr, word_ptr *, word_ptr *, word_ptr *);

/* parsing label addressing type
 * input: word , line counter, ic increment value, first -> second  words, is source flag
 * output: parsing the label operand, returns if should continue handling*/
boolean parseLabel(char *, int, int *, word_ptr, word_ptr *, boolean);

/* parsing register addressing type
 * input: word , line counter, ic increment value, first -> second  words, is source flag
 * output: parsing the register operand, returns if should continue handling*/
boolean parseRegister(const char *, int, int *, word_ptr, word_ptr *, boolean);

/* parsing the .string directive
 * input: dc , line counter, word and label
 * output: adding all the chars of string to the data list, return if should continue handling*/
boolean parseStringDirective(int *, int, char *, char *);

#endif
