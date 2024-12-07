
#include "parsers.h"

/* parsing label addressing type
 * input: word , line counter, ic increment value, first -> second  words, is source flag
 * output: parsing the label operand, returns if should continue handling*/
boolean parseLabel(char *word, int line, int *increment_value_IC, word_ptr first, word_ptr *second, boolean isSource) {
    char *ptr = word;
/*check if first char is letter*/
    if (isalpha(*ptr)) {
        /*checks for invalid chars*/
        while (*ptr != '\0') {
            /*contains invalid characters, add error*/
            if ((!isdigit(*ptr)) && (!isalpha(*ptr))) {
                addError("Invalid character", line, word);
                free(first);
                return FALSE;
            }
            /*progress ptr*/
            ptr++;
        }

        /* set second word data*/
        (*second) = malloc(sizeof(word_node));
        (*second)->line = line;
        (*second)->method = DIRECT;
        (*second)->isExternal = FALSE;
        (*second)->missingLabel = malloc(sizeof(char) * MAX_LINE);
        (*second)->externalLabel = NULL;
        strcpy((*second)->missingLabel, word);
        (*second)->holder.immediate.number = 0;
        (*second)->holder.immediate.are = EXTERNAL;
        (*second)->next = NULL;
        /*set first word data if source*/
        if (isSource) {
            first->holder.first.source = DIRECT;
        } else {
            first->holder.first.destination = DIRECT;
        }
        (*increment_value_IC)++;
    }
        /*if the label didn't start with a letter add error*/
    else {
        addError("Labels must start with a letter", line, word);
        free(first);
        free((*second));
        return FALSE;
    }
    return TRUE;
}