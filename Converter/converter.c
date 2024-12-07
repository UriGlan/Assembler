
#include "converter.h"

/*convert an assembly file to needed files or error file if invalid
 * input: file pointer, line counters*/
void convertFile(FILE * fp, line_counters *counters, char *name){
    FILE * target = openFile(name, "w+", EXT_EXTENSION);
    macroIteration(fp, target);
    firstIteration(target, &counters->IC, &counters->DC);
    updateAllAddresses(counters->IC);
    secondIteration();
}
/*updating addresses of symbols word and data after first iteration
 * input: new instruction counter*/
void updateAllAddresses(int ic) {
    /*update symbols list addresses*/
    updateSymbols(ic);
    /*Update words list addresses*/
    updateWordAddresses();
    /*update data list addresses*/
    updateDataAddresses(ic);
}