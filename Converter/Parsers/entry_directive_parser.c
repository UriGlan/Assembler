



#include "parsers.h"
/* parsing the .entry directive
 * input: line counter, word
 * output: adding to entry list, return if should continue handling directive*/
boolean parseEntryDirective(int lineCounter, char *word) {
    /*if no label found is after the directive, add error*/
    if (!(word = strtok(NULL, " \t\n"))) {
        addError("No label found after ENTRY directive", lineCounter, NULL);
        return FALSE;
    }
    /*add an entry node*/
    addEntry(word, lineCounter);
    /*if there's a next word, add error*/
    if ((strtok(NULL, "\n"))) {
        addError("To many arguments after ENTRY directive", lineCounter, NULL);
        return FALSE;
    }
    return FALSE;
}

