#include "handlers.h"


/*handling directive
 * input: dc, line counter, directive's word, label, and directive type
 * output: parse the directive by type, return if should continue to handle directive*/
boolean handleDirective(int *DC, int lineCounter, char *word, char *label,
                        directive directive) {
    switch (directive) {
        case DATA:
            /*in case of type .data*/
            parseDataDirective(DC, lineCounter, word, label);
            break;
        case STRING:
            /*get next word*/
            word = strtok(NULL, "\n");
            return parseStringDirective(DC, lineCounter, word, label);

        case ENTRY:
            /*if we have a label, print a warning*/
            if (label)
                printf("[WARNING] line %d: Ignoring label \"%s\"\n before entry directive.", lineCounter,
                       label);
            return parseEntryDirective(lineCounter, word);
        case EXTERN:
            /*if there's a label, print a warning*/
            if (label)
                printf("Warning, line %d: Ignoring label \"%s\" before extern directive.\n", lineCounter,
                       label);
            return parseExternDirective(lineCounter, word);
        default:
            /*add error if directive type is not something we support*/
            addError("Invalid directive", lineCounter, word);
            return FALSE;
    }
    return TRUE;
}




