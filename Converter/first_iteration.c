#include "converter.h"

/*first iteration on the file, here we will update all the addresses and start decoding
 *input: file pointer, ic and dc
 * output: updated addressees and symbol table and semi decoded file*/
void firstIteration(FILE *fp, int *IC, int *DC) {
    /*Line buffer*/
    char line[MAX_LINE];
    /*Line counter*/
    int lineCounter = 0;
    /*Line fetching loop*/
    while (fgets(line, MAX_LINE, fp)) {
        /*pointer to word*/
        char *word = NULL;
        /*pointer to label*/
        char *label = NULL;
        /*directiveType flag*/
        directive directiveType;
        /*get first word*/
        word = strtok(line, " \t\n");
        /*increment line counter*/
        lineCounter++;
        /*if line is empty, go to next line*/
        if (!word) {
            continue;
        }
        /*if line is comment, go to next line*/
        if (isComment(word)) {
            continue;
        }
        /*If label */
        if ((label = getLabel(word))) {
            /*if label handling is not valid*/
            if (!handleLabel(lineCounter, &word, &label))
                continue;
        }
        /*get directiveType*/
        if ((directiveType = getDirective(word))) {
            /*if directive handling is not valid*/
            if (!handleDirective(DC, lineCounter, word, label, directiveType))
                continue;
        } else {
            /*handle the operation*/
            handleOperation(word, lineCounter, IC, label);
        }
    }
    /*If the file is empty*/
    if (lineCounter == 0) {
        addError("File is empty", NULL_LINE, NULL);
    }

}
