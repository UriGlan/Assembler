
#ifndef ASSEMBLER_HANDLERS_H
#define ASSEMBLER_HANDLERS_H


#include "../Parsers/parsers.h"
#include "../../Utils/assembler_utils.h"

/*handling directive
 * input: dc, line counter, directive's word, label, and directive type
 * output: parse the directive by type, return if should continue to handle directive*/
boolean handleDirective(int *, int, char *, char *, directive);

/*handling operation of group 1, means take 1 parameter
 * input: word, line number, ic value, first -> fourth word
 * output: after parsing by type ( immediate, register,label or jump), next 1-4 words set.
 * returns if should continue handle*/
boolean handleGroup1(char *, int, int *, word_ptr, word_ptr *,
                     word_ptr *, word_ptr *);

/*handling operation of group 2, means take 2 parameter
 * input: word, line number, ic value, first -> third word
 * output: after parsing by type ( immediate, register or label), next 1-3 words set.
 * returns if should continue handle*/
boolean handleGroup2(char *, int, int *, word_ptr, word_ptr *, word_ptr *);


/*handling label
 * input: line counter, label's word, label
 * output:return is label is valid*/
boolean handleLabel(int, char **, char **);

/*handling a sentence. we analyze the sentence word by word.
 * and handle each word by its type. last we add the result words ( first -> fourth) to the list
 * input: word, line number, instruction counter and the label*/
void handleOperation(char *, int, int *, char *);

/*sets the first word default values and opcode
 * input: line number, opcode, first word pointer to set*/
void setFirstWordDefault(int, opcode, word_ptr);

#endif
