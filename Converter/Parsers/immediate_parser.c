

#include "parsers.h"

/* parsing immediate addressing type
 * input: word , line counter, ic increment value, first -> second  words, isSource flag
 * output: adding all the numbers to the data list, returns if should continue handling*/
boolean parseImmediate(char *word, int line, int *increment_value_IC, word_ptr first,
                       word_ptr *second, boolean isSource) {
    int num;
    char *ptr;
    char *error_ptr;
    unsigned int methodOpcode;
    ptr = word;
    ptr++;
    /*extract the number value*/
    num = strtol(ptr, &error_ptr, DECIMAL);
    /*get op code from first word*/
    methodOpcode = first->holder.first.opcode;
/*if command is LEA and operand is source, error&quit*/
    if (methodOpcode == OPCODE_LEA && isSource) {
        addError("This command can't take an immediate number as a operand", line, NULL);
        free(first);
        return FALSE;
    }
    /*if command is not cmp, prn and operand is destination error&quit*/
    if (methodOpcode != OPCODE_CMP && methodOpcode != OPCODE_PRN && !isSource) {
        addError("This command can't take an immediate number as a second operand", line, NULL);
        free(first);
        return FALSE;
    }
/*if number contains string value, add error*/
    if (*error_ptr != 0) {
        addError("Invalid number", line, NULL);
        free(first);
        return FALSE;
    }
/*if the number isn't within range, add error*/
    if (num > MAX_NUM_IMMEDIATE || num < MIN_NUMBER_IMMEDIATE) {
        addError("Immediate number is out of range", line, NULL);
        free(first);
        return FALSE;
    }
        /*If syntax is correct set word*/
    else {
        (*second) = malloc(sizeof(word_node));
        (*second)->method = IMMEDIATE;
        (*second)->isExternal = FALSE;
        (*second)->line = line;
        (*second)->missingLabel = NULL;
        (*second)->externalLabel = NULL;
        (*second)->holder.immediate.number = (unsigned int) num;
        (*second)->holder.immediate.are = ABSOLUTE;
        (*second)->next = NULL;
        if (isSource) {
            first->holder.first.source = IMMEDIATE;
        } else {
            first->holder.first.destination = IMMEDIATE;
        }
        (*increment_value_IC)++;
    }
    return TRUE;
}
