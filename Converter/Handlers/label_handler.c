
#include "handlers.h"

/*handling label
 * input: line counter, label's word, label
 * output:return is label is valid*/
 boolean handleLabel(int lineCounter, char **word, char **label) {
    /*If getLabel returned error string*/
    if (!strcmp((*label), ILLEGAL_LABEL)) {
        addError("Illegal label", lineCounter, (*word));
        (*label) = NULL;
    }
    /*if label is reserved name*/
    else if (!strcmp((*label), RESERVED_NAME)) {
        addError("Label name is reserved", lineCounter, NULL);
        (*label) = NULL;
    }
    /*Get next word.*/
    (*word) = strtok(NULL, " \t\n");
    /*if next word is null, add error and go to next line*/
    if (!(*word)) {
        addError("Data or Instruction is required after label", lineCounter, NULL);
        return FALSE;
    }
    return TRUE;
}


