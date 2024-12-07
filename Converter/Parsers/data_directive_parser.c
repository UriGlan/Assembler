
#include "parsers.h"

/* parsing the .data directive
 * input: dc , line counter, word and label
 * output: adding all the numbers to the data list*/
void parseDataDirective(int *DC, int lineCounter, char *word, char *label) {
    /*if label exist*/
    if (label) {
        /*adding label to symbols table*/
        addSymbol(label, *DC, FALSE, FALSE, lineCounter);
    }
    /*add each number of .data to list*/
    splitNumbersAndAdd(word, lineCounter, DC);
}
