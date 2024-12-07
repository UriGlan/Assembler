


#include "parsers.h"

/* parsing the .string directive
 * input: dc , line counter, word and label
 * output: adding all the chars of string to the data list, return if should continue handling*/
boolean parseStringDirective(int *DC, int lineCounter, char *word, char *label) {
    /*if directive wasn't followed by string*/
    if (!word) {
        addError("No string argument found", lineCounter, NULL);
        return FALSE;
    }
    /*if there's a label*/
    if (label) {
        /*add to symbols list*/
        addSymbol(label, *DC, FALSE, FALSE, lineCounter);
    }
    /*add to data*/
    addString(word, lineCounter, DC);
    return FALSE;
}