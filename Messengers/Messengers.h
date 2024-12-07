

#ifndef ASSEMBLER_INNERMESSENGER_H
#define ASSEMBLER_INNERMESSENGER_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../Utils/definitions.h"
#include "../Utils/data_structures.h"
#include "../Managers/Managers.h"
#include "../Utils/assembler_utils.h"


/*opens a file in read mode
 * input: path to file
 * output: pointer to file in read mode */
FILE *receiveFile(char *);

/*opens a file in mode specified
 * input: path mode and file type
 * output: open file pointer in the mode*/
FILE *openFile(char *, char *, char *);

/*return if error in node list exist*/
boolean isError();

/*adds error to the list of errors
 * input:error, line of error and a message
 * output: void. adds error to list of errors*/
void addError(char *, int, char *);

/* returns the last line an error appears in*/
int getLastErrorLine();

/*write the errors to an errors file
 * input: filename
 * output: void. writes to stderr*/
void printErrors(char *);

/*clean up the errors list*/
void freeErrors();

/*input: ic and dc also the name of file
 * output: between 0-3 files of type ob ext ent*/
void exportFiles(char *);

/*close all files*/
void closeAllFiles(FILE *, FILE *, FILE *);

#endif
