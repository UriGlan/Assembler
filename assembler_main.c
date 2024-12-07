#include "EndToEnd.h"

/*Mamam 14 Final Project
 *
 * In this project we were asked to create the assembler.
 * I build the assembler with an architecture similar the a Gateway:
 * Messengers: file handler to receive and handle file form user and final files,
 *              error manager to handle errors
    Parsers: Multiple parsers each is responsible on its own data type:
                        entry, extern,data,string,immediate number,register,label and jump with parameters
    Handler: Are in charge to call the Parsers. each handler are in charge of multiple parsers
    Converter: In charge of calling the Handlers. and Operate the convection Algorithm:
                First Iteration & Second Iteration.
    Managers: are in charge of handling the data structures of different types and using method on them
    Utils: are where the project definitions and data structures declaration,
            also some util functions we use along the way.

    In conclusion:
        we have the main function who gets multiple strings that represent .as files.
        for each of them we call the file manager to open them and receive a file pointer.
        for each file pointer we call the converter -> who reads line by line and calls the handler->
        that calls the parser-> that manipulate the managers.

        after we done going over all the whole file, we check if there are errors, if so print them to stderr.
        otherwise export to the needed files the data we converted.
    */

int main(int argc, char *argv[]) {
    /*File Pointer to input file*/
    FILE *fp = NULL;
    /*Line counters*/
    line_counters counters;
    /*Check if there are no arguments*/
    if (argc == 1) {
        /*Print error to screen*/
        fprintf(stderr, "No file name entered.\n");
        return 1;
    }
    /*Loop which goes through all of argv's elements*/
    while (--argc) {
        /*Open the file*/
        if ((fp = receiveFile(*(++argv)))) {
            /*init line counters*/
            counters.IC = IC_DEFAULT_VAL;
            counters.DC = DC_DEFAULT_VAL;
            /*convert assembly to binary*/
            convertFile(fp, &counters, *argv);
            /*If there were no errors, export the files*/
            if (!isError()) {
                exportFiles(*argv);
            }
                /*If there were errors, export the error file*/
            else {
                printErrors(*argv);
            }
            /*Cleanup*/
            cleanUp();
        }
    }
    return 0;
}

/*cleans all data structures*/
void cleanUp() {
    freeData();
    freeSymbols();
    freeEntries();
    freeWords();
    freeErrors();
}

