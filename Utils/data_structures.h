

#ifndef ASSEMBLER_DATA_STRUCTURES_H
#define ASSEMBLER_DATA_STRUCTURES_H

#include "definitions.h"

/*build of first word*/
typedef struct first_word {
    /*ARE bits*/
    unsigned int are: 2;
    /*Destination operand bits*/
    unsigned int destination: 2;
    /*source operand bits*/
    unsigned int source: 2;
    /*Opcode bits*/
    unsigned int opcode: 4;
    /*params bits*/
    unsigned int param2: 2;
    unsigned int param1: 2;

} first_word;

typedef struct immediate_word {
    /*ARE bits*/
    unsigned int are: 2;
    /*bits used to hold the value/address*/
    unsigned int number: 12;
} immediate_word;

typedef struct index_word {
    /*ARE bits*/
    unsigned int are: 2;
    /*address of label*/
    unsigned int address:12;

} index_word;

typedef struct register_word {
    /*ERA bits*/
    unsigned int are: 2;
    /*Destination register bits*/
    unsigned int destination: 6;
    /*source register bits*/
    unsigned int source: 6;

} register_word;

/*define a Union to hold all type of word*/
typedef union word_holder {
    first_word first;
    immediate_word immediate;
    index_word index;
    register_word reg;
} word_holder;

typedef struct word_node *word_ptr;
typedef struct word_node {
    /*The word itself*/
    word_holder holder;
    /*method code*/
    int method;
    /*line of input*/
    int line;
    int address;
    /*Label of external*/
    char *externalLabel;
    /*Missing label*/
    char *missingLabel;
    boolean isExternal;
    /*Pointer to next*/
    word_ptr next;
} word_node;


typedef struct opcode {
    /*The operation string*/
    char *str;
    /*The opcode*/
    unsigned short code;
    /*its group*/
    unsigned short group;
} opcode;


typedef struct data *data_ptr;
typedef struct data {
    /*address of data word*/
    int address;
    /*value*/
    short int value;
    /*pointer to next*/
    data_ptr next;
} data;

typedef struct symbol *sym_ptr;
typedef struct symbol {
    /*symbol's label*/
    char *label;
    /*symbol's address*/
    short address;
    boolean isExternal;
    boolean isOperation;
    /*pointer to next*/
    sym_ptr next;
} symbol;


typedef struct entry *entry_ptr;
typedef struct entry {
    /*entry's label*/
    char *label;
    /*entry's address*/
    short int address;
    boolean hasAddress;
    /*line of entry*/
    int line;
    /*pointer to next*/
    entry_ptr next;
} entry;


typedef struct error *err_ptr;
/*definition of error type. used in the errors list*/
typedef struct error {
    /*The error itself*/
    char *message;
    /*Line of error*/
    int line;
    /*the error's input string*/
    char *input;
    /*pointer to next*/
    err_ptr next;
} error;

/*structure for line and command counters*/
typedef struct line_counters {
    /*instruction counter*/
    int IC;
    /*data counter*/
    int DC;
} line_counters;


#endif
