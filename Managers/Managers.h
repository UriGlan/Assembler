

#ifndef ASSEMBLER_DATAMANAGERS_H
#define ASSEMBLER_DATAMANAGERS_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "../Messengers/Messengers.h"
#include "../Utils/data_structures.h"


/*
 * data_manager.c function
 * */


/*adding a number to the data list
 * input: a  number, line number and dc
 * output: add to the data list if valid*/
void addNumber(char *, int, int *);

/*spiting numbers received in .data directive and add it to node
 * input: string as a parameter, line number and dc
 * output: splits it the numbers and add to data list.*/
void splitNumbersAndAdd(char *, int, int *);

/*adding a char to data list
 * input: a char
 * output: add to data list*/
void addChar(char);

/*checking if string is valid, if so, adding each char to data list
 * input: a string, line number
 * output: add to data list*/
void addString(char *, int, int *);

/*Clear the data list*/
void freeData();

/*counts data list size
 * output: data list size*/
int countData();

/*return pointer to head. used when exporting files*/
data_ptr getHeadData();

/*updates the data addresses AFTER we have all our operation words
 * input: ic
 * output: all data list addresses are updated*/
void updateDataAddresses(int);



/*
 * word_manager.c functions
 * */

/*adding a word to word list
 * input: word_node
 * output: adding it to node list*/
void addWord(word_ptr);

/*updating the address of all the nodes*/
void updateWordAddresses();

/*output:getting word node size*/
int getWordNodeSize();

/*output: void. cleans up the list*/
void freeWords();

/*output: a word with missing label*/
word_ptr getMissingLabel();

/*output: return a pointer to the head of the list*/
word_ptr getHeadWord();




/*
 * symbol_manager.c functions
 * */


/*adding a label to the list
 * input: label, address, flags and line number
 * output: add a label to list*/
void addSymbol(char *, int, boolean, boolean, int);

/*matching the symbol's address to the ic counter after first iteration
 * input: ic
 * output: void. updates symbols address*/
void updateSymbols(int);

/*output: empty symbols list*/
void freeSymbols();

/*adding error is symbol already exist
 * input:label and line number
 * output: error if same label exist*/
void checkIfSymbolExist(char *, int);

/*finds symbol with the same name as param1: label
 * input: label
 * output: symbol with name as label*/
sym_ptr searchSymbol(char *);




/*
 * entry_manager.c functions
 * */

/*adding an entry to the entries list
 * input: a  label, line number
 * output: add to the data list if valid*/
void addEntry(char *, int);

/* checks if an entry with the same label already exists
 * input: label
 * output: is already exist*/
boolean isEntryExist(char *);

/*clears the list of entries*/
void freeEntries();

/* returns first entry without an address*/
entry_ptr getEntryWithAddress();

/* returns a pointer to the head*/
entry_ptr getHeadEntry();


#endif
