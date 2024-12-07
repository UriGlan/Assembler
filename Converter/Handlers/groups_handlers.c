
#include "handlers.h"

/*handling operation of group 1, means take 1 parameter
 * input: word, line number, ic value, first -> fourth word
 * output: after parsing by type ( immediate, register,label or jump), next 1-4 words set.
 * returns if should continue handle*/
boolean handleGroup1(char *word, int line, int *increment_value_IC, word_ptr first, word_ptr *second,
                     word_ptr *third, word_ptr *fourth) {
    /*If first word is an immediate number*/
    if (*word == IMMEDIATE_SIGN) {
        if (!parseImmediate(word, line, increment_value_IC, first, second, FALSE))
            return FALSE;
    }
/*Check if word is a register*/
    else if (isRegister(word)) {
        if (!parseRegister(word, line, increment_value_IC, first, second, FALSE))
            return FALSE;
    }
        /*check if word  is Jump with parameters*/
    else if (isJump(word)) {
        if (!parseJump(word, line, increment_value_IC, first, second, third, fourth))
            return FALSE;
    }
/*If word not immediate/register/word must be label*/
    else {
        if (!parseLabel(word, line, increment_value_IC, first, second, FALSE))
            return FALSE;
    }
/*if string has more arguments*/
    if ((strtok(NULL, " ,\t\n"))) {
        addError("Too many arguments", line, NULL);
        free(first);
        free((*second));
        if (third)
            free(*third);
        if (fourth)
            free(*fourth);
        return FALSE;
    }
    return TRUE;
}

/*handling operation of group 2, means take 2 parameter
 * input: word, line number, ic value, first -> third word
 * output: after parsing by type ( immediate, register or label), next 1-3 words set.
 * returns if should continue handle*/
boolean handleGroup2(char *word, int line, int *increment_value_IC, word_ptr first, word_ptr *second,
                     word_ptr *third) {
    /*If first word is an immediate number*/
    if (*word == IMMEDIATE_SIGN) {
        if (!parseImmediate(word, line, increment_value_IC, first, second, TRUE))
            return FALSE;
    }
/*if first word is register*/
    else if (isRegister(word)) {
        if (!parseRegister(word, line, increment_value_IC, first, second, TRUE))
            return FALSE;
    }
/*If word not immediate/register/word must be label*/
    else {
        if (!parseLabel(word, line, increment_value_IC, first, second, TRUE))
            return FALSE;
    }
/*Move to second word*/
    if ((word = strtok(NULL, " ,\t\n"))) {
        /*if immediate*/
        if (*word == IMMEDIATE_SIGN) {
            if (!parseImmediate(word, line, increment_value_IC, first, third, FALSE))
                return FALSE;
        }
            /*if register*/
        else if (isRegister(word)) {
            /*if first param was register as well we put them is the same word*/
            if ((*second)->method == REGISTER) {
                first->holder.first.destination = REGISTER;
                (*second)->holder.reg.destination = (unsigned int) (word[1] - '0');
            } else {
                if (!parseRegister(word, line, increment_value_IC, first, third, FALSE))
                    return FALSE;
            }
        }
            /*If word not immediate/register/word must be label*/
        else {
            if (!parseLabel(word, line, increment_value_IC, first, third, FALSE))
                return FALSE;
        }
/*check if the string has more arguments*/
        if ((strtok(NULL, " ,\t\n"))) {
            addError("Too many arguments", line, NULL);
            free(first);
            free((*second));
            free((*third));
            return FALSE;
        }
    }
/*Check if there's less than 2 arguments*/
    else {
        addError("This command is expecting 2 parameters", line, NULL);
        free(first);
        free((*second));
        return FALSE;
    }
    return TRUE;
}
