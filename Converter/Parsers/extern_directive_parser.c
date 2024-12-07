
#include "parsers.h"

/* parsing the .extern directive
 * input:line counter, word
 * output: adding to symbols list, return if should continue handling directive*/
boolean parseExternDirective(int lineCounter, char *word) {
    /*if next word doesnt exist, add errors*/
    if (!(word = strtok(NULL, " \t\n"))) {
        addError("No label found after EXTERN directive", lineCounter, NULL);
        return FALSE;
    }
    /*add extern symbol*/
    addSymbol(word, 0, TRUE, FALSE, lineCounter);
    /*if next word is not null, add error*/
    if ((strtok(NULL, "\n"))) {
        addError("To many arguments after EXTERN directive", lineCounter, NULL);
        return FALSE;
    }
    return FALSE;
}
