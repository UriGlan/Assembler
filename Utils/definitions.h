
#ifndef ASSEMBLER_DEFINITIONS_H
#define ASSEMBLER_DEFINITIONS_H

/*boolean enum*/
typedef enum boolean {
    FALSE, TRUE
} boolean;

/*Addressing method enum - NONE means first word*/
typedef enum addressing_type {
    NONE = -1, IMMEDIATE = 0, DIRECT = 1, JUMP = 2, REGISTER = 3
} addressing_type;

/*type of directives*/
typedef enum directive {
    DIRECTIVE_NONE, DATA, STRING, ENTRY, EXTERN, ERROR
} directive;

/*group types*/
typedef enum group_types {
    GROUP_1 = 1, GROUP_2 = 2
} group_types;
/*ARE types*/
typedef enum are_types {
    ABSOLUTE, EXTERNAL, RELOCATABLE
} are_types;

/*this is an indentifyer that is in usr in both macro and symbols hashTable*/
typedef enum
{
    Macro,
    Symbol
} ItemType;

/* MacroData is a struct that holds the additional unique data that helps us to define when a macro starts and where its ends*/
typedef struct
{
    int start;
    int end;
} MacroData;

/*Attributes for the type of symbol that are saved in the symbol table*/

typedef struct
{
    unsigned int code : 1;
    unsigned int data : 1;
    unsigned int entry : 1;
    unsigned int external : 1;
} Attributes;

/*SymbolData is a struct that holds the additional unique data fields in the symbols hash table.
value - the value of the memory address 
base and offset - both representing the value of the memory adress that the symbols appears in
attrs - holding the type of the symbol (data, entry, external, code).
 */

typedef struct
{

    unsigned value;
    unsigned base;
    unsigned offset;
    Attributes attrs;
} SymbolData;


/*defines the item and their types */
typedef struct Item
{
    char *name;
    union
    {
        SymbolData s;
        MacroData m;
    } val;
    struct Item *next;
} Item;

/*the  definition of state type */
typedef enum
{
    assemblyCodeFailedToCompile,
    startProgram,
    parsingMacros,
    firstRun,
    secondRun,
    exportFilesState,
    exitProgram
} State;




/*types to be compared with input*/
#define STR_DIRECTIVE_DATA ".data"
#define STR_DIRECTIVE_STRING ".string"
#define STR_DIRECTIVE_ENTRY ".entry"
#define STR_DIRECTIVE_EXTERN ".extern"
/*File permissions*/
#define READ_ONLY "r"
#define WRITE_ONLY "w"
/*decimal base*/
#define DECIMAL 10
/*register prefix*/
#define REGISTER_PREFIX 'r'
/*register length*/
#define REGISTER_LENGTH 2
/*Maximum filename size*/
#define MAX_FILENAME 256
/*Maximum line buffer size*/
#define MAX_LINE 256
/*Number of registers*/
#define NUM_OF_REGISTERS 8
/*IC and DC Default value*/
#define IC_DEFAULT_VAL 100
#define DC_DEFAULT_VAL 0
/*num of bits*/
#define BITS 14
/*Maximum and minimum values that can be stored in 12 bits*/
#define MAX_NUMBER_DATA 8191
#define MIN_NUMBER_DATA (-8192)
#define MAX_NUM_IMMEDIATE 2047
#define MIN_NUMBER_IMMEDIATE (-2048)
/*memory size*/
#define MEMORY_SIZE 256
/*Max Label length*/
#define MAX_LABEL_LENGTH 31
/*Max Line length*/
#define MAX_LINE_LENGTH 81
/*Hashdize for the macro-hash table*/
#define HASHSIZE ((MAX_NUMBER_DATA / (MAX_LABEL_LENGTH + 1)) / 4)
/*illegal flags for label*/
#define RESERVED_NAME "reserved"
#define ILLEGAL_LABEL "illegal"
/*immediate sign*/
#define IMMEDIATE_SIGN '#'
/* comment sign*/
#define COMMENT_SIGN ';'
/*directive prefix*/
#define DIRECTIVE_PREFIX '.'
/*null line number in case file is empty*/
#define NULL_LINE (-1)
/*number of opcodes*/
#define OPCODES_AMOUNT 16
/*Extensions for file */
#define AS_EXTENSION ".as"
#define OB_EXTENSION ".ob"
#define ENT_EXTENSION ".ent"
#define EXT_EXTENSION ".ext"
/*Opcodes*/
#define OPCODE_CMP 1
#define OPCODE_LEA 6
#define OPCODE_JMP 9
#define OPCODE_BNE 10
#define OPCODE_PRN 12
#define OPCODE_JSR 13
#define OPCODE_RTS 14
#define OPCODE_STOP 15

#endif
