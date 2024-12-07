


#include "parsers.h"

/* parsing register addressing type
 * input: word , line counter, ic increment value, first -> second  words, is source flag
 * output: parsing the register operand, returns if should continue handling*/
boolean parseRegister(const char *word, int line, int *increment_value_IC, word_ptr first,
                      word_ptr *second, boolean isSource) {
    /*if register is source in lea method add error*/
    if (first->holder.first.opcode == OPCODE_LEA && isSource) {
        addError("This command can't take a register as a source operand", line, NULL);
        free(first);
        return FALSE;
    }
    /*set second word data*/
    (*second) = malloc(sizeof(word_node));
    (*second)->method = REGISTER;
    (*second)->isExternal = FALSE;
    (*second)->line = line;
    (*second)->missingLabel = NULL;
    (*second)->externalLabel = NULL;
    (*second)->holder.reg.are = ABSOLUTE;
    (*second)->next = NULL;
    /*set first word data , if source*/
    if (isSource) {
        (*second)->holder.reg.source = (unsigned int) (word[1] - '0');
        (*second)->holder.reg.destination = 0;
        first->holder.first.source = REGISTER;
    } else {
        (*second)->holder.reg.destination = (unsigned int) (word[1] - '0');
        (*second)->holder.reg.source = 0;
        first->holder.first.destination = REGISTER;
    }
    (*increment_value_IC)++;
    return TRUE;
}
