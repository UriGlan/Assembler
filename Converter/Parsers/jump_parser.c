
#include "parsers.h"

/* parsing jump with params addressing type
 * input: word , line counter, ic increment value, first -> fourth  words
 * output: parsing the jump operands, returns if should continue handling*/
boolean parseJump(char *word, int line, int *increment_value_IC, word_ptr first, word_ptr *second, word_ptr *third,
                  word_ptr *fourth) {
    size_t rBracketIndex, lBracketIndex, commaIndex;
    char * label,* param1, *param2;
    addressing_type param1Type;
    addressing_type param2Type;
    /*if opcode is not jmp bne or jsr add error*/
    unsigned int methodOpcode = first->holder.first.opcode;
    if (methodOpcode != OPCODE_JMP && methodOpcode != OPCODE_BNE && methodOpcode != OPCODE_JSR) {
        addError("Jump with parameters registration can only work with: jmp,bne and jsr", line, NULL);
        free(first);
        return FALSE;
    }
    /*getting the indexes of '(' |','| ')'*/
    rBracketIndex = strcspn(word, "(");
    lBracketIndex = strcspn(word, ")");
    commaIndex = strcspn(word, ",");
    /*extracting from word the label and two params according to above indexes*/
    label = getSubString(word, 0, rBracketIndex - 1);
    param1 = getSubString(word, rBracketIndex + 1, commaIndex - 1);
    param2 = getSubString(word, commaIndex + 1, lBracketIndex - 1);
    /*parsing the label of jump*/
    parseLabel(label, line, increment_value_IC, first, second, FALSE);
    /*If param1 is an immediate number*/
    if (*param1 == IMMEDIATE_SIGN) {
        param1Type = IMMEDIATE;
        if (!parseImmediate(param1, line, increment_value_IC, first, third, TRUE))
            return FALSE;
    }
/*if  param1 is register*/
    else if (isRegister(param1)) {
        param1Type = REGISTER;
        parseRegister(param1, line, increment_value_IC, first, third, TRUE);
    }
/*if we didn't receive immediate number/register/index, it must be a label*/
    else {
        param1Type = DIRECT;
        if (!parseLabel(param1, line, increment_value_IC, first, third, TRUE))
            return FALSE;
    }
/*Move to second param*/

    /*If param1 is an immediate number*/
    if (*param2 == IMMEDIATE_SIGN) {
        param2Type = IMMEDIATE;
        if (!parseImmediate(param2, line, increment_value_IC, first, fourth, FALSE))
            return FALSE;
    }
    /*if param2 is register*/
    else if (isRegister(param2)) {
        param2Type = REGISTER;
        /*if param 1 was also register*/
        if ((*third)->method == REGISTER) {
            (*third)->holder.reg.destination = (unsigned int) (param2[1] - '0');
        } else {
            parseRegister(param2, line, increment_value_IC, first, fourth, FALSE);
        }
    }
        /*if word is not immediate/index/register must be a label*/
    else {
        param2Type = DIRECT;
        if (!parseLabel(param2, line, increment_value_IC, first, fourth, FALSE))
            return FALSE;
    }
    /*applying first word data*/
    first->holder.first.source = 0;
    first->holder.first.destination = JUMP;
    first->holder.first.param1 = param1Type;
    first->holder.first.param2 = param2Type;
    return TRUE;
}
