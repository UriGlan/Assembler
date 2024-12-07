
#include "assembler_utils.h"

/*Array holding information about each opcode
 * name
 * opcode code
 * group: how many params can hold*/
static opcode opCodes[16] = {{"mov",  0,  2},
                             {"cmp",  1,  2},
                             {"add",  2,  2},
                             {"sub",  3,  2},
                             {"not",  4,  1},
                             {"clr",  5,  1},
                             {"lea",  6,  2},
                             {"inc",  7,  1},
                             {"dec",  8,  1},
                             {"jmp",  9,  1},
                             {"bne",  10, 1},
                             {"red",  11, 1},
                             {"prn",  12, 1},
                             {"jsr",  13, 1},
                             {"rts",  14, 0},
                             {"stop", 15, 0}};
/*Array of register string, for comparing with input*/
static char *registers[8] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

/*checks if pointer is null after allocation
 * input: pointer
 * output: error message in null */
void checkAllocation(void *ptr) {
    if (!ptr) {
        fprintf(stderr,"Unable to allocate memory.\n");
        exit(0);
    }
}

/*get a label by string and check if valid
 * input: label as string
 * output: label is exist, null if it does'nt
 * and if illegal or reserved by flags*/
char *getLabel(char *word) {
    char *ptr = word;
    /*if last char is ':'*/
    if (word[strlen(word) - 1] == ':') {
        /*if first letter is valid*/
        if (isalpha(*word)) {
            /*if label is bigger the permitted length*/
            if (strlen(word) > MAX_LABEL_LENGTH){
                return ILLEGAL_LABEL;
            }
            /*set null terminator instead of ':'*/
            word[strlen(word) - 1] = 0;

            /*If there's a char which is not a digit or a letter, return an error flag*/
            while ((*ptr) != '\0') {
                if (!isalpha(*ptr)) {
                    if (!isdigit(*ptr)) {
                        return ILLEGAL_LABEL;
                    }
                }
                ptr++;
            }
            /*If the word is an operation, return reserved word flag*/
            if (isOperation(word)) {
                return RESERVED_NAME;
            }
            /*If the word is a register, return reserved word flag*/
            if (isRegister(word)) {
                return RESERVED_NAME;
            }
            return word;
        }
            /*if first letter is invalid, return error flag*/
        else {
            return ILLEGAL_LABEL;
        }
    }
        /*if last letter is not ':', return null*/
    else {
        return NULL;
    }
}

/* finds out directive type base on string input
 * input: string
 * output: directive type*/
directive getDirective(char *word) {
    /*if first char is '.'*/
    if (*word == DIRECTIVE_PREFIX) {
        /*return enum matching to the directive*/
        if (!strcmp(word, STR_DIRECTIVE_DATA)) {
            return DATA;
        } else if (!strcmp(word, STR_DIRECTIVE_STRING)) {
            return STRING;
        } else if (!strcmp(word, STR_DIRECTIVE_ENTRY)) {
            return ENTRY;
        } else if (!strcmp(word, STR_DIRECTIVE_EXTERN)) {
            return EXTERN;
        }
            /*if string is unknown*/
        else {
            return ERROR;
        }
    }
        /*if this isn't a directive*/
    else {
        return DIRECTIVE_NONE;
    }
}

/*checks if word is comment
 * input: word
 * output: isComment*/
boolean isComment(char *word) {
    return (boolean) (*word == COMMENT_SIGN);
}

/*determine if word is jump address param
 * input: word
 * output: isJump address type*/
boolean isJump(char *word) {
    char * rest, *tmp, word_i;
    /*start from second char of word to promise label before (*/
    unsigned i;
    /*counters for right bracket left bracket and comma*/
    int rBracketCounter = 0, lBracketCounter = 0, commaCounter = 0;

/*get rest of the word*/
    rest = strtok(NULL, " \t\n");
    /*if the is nothing more*/
    if (rest == NULL)
        return FALSE;
/*allocating memory for the entire param*/
    tmp = (char *) malloc(strlen(rest) + strlen(word) + 1);
    checkAllocation(tmp);
    /*building the entire param into tmp and then copy to word*/
    strcpy(tmp, word);
    strcat(tmp, ",");
    strcat(tmp, rest);
    strcpy(word, tmp);
    /*for each char in word*/
    for (i = 0; i < strlen(word); i++) {
        word_i = *(word + i);
        /*found comma after right bracket found once*/
        if (word_i == ',' && rBracketCounter == 1)
            commaCounter++;
        /*right bracket must appear first*/
        if (word_i == '(' && lBracketCounter == 0 && commaCounter == 0)
            rBracketCounter++;
        /*left bracket must appear last*/
        if (word_i == ')' && commaCounter == 1 && rBracketCounter == 1)
            lBracketCounter++;
    }
    /*if all found once return true*/
    return (boolean) (lBracketCounter == 1 && rBracketCounter == 1 && commaCounter == 1);
}

/*check is string is known operation
 * input: string
 * output: isOperation boolean
 * */
boolean isOperation(char *word) {
    int i;
    /*go over all opcodes*/
    for (i = 0; i < OPCODES_AMOUNT; i++) {
        if (!strcmp(word, opCodes[i].str)) {
            return TRUE;
        }
    }
    return FALSE;
}

/*checks if string is register
 * input: string
 * output: isRegister boolean * */
boolean isRegister(char *word) {
    int i;
    /*if has a structure of register*/
    if (strlen(word) == REGISTER_LENGTH && word[0] == REGISTER_PREFIX && isdigit(word[1])) {
        for (i = 0; i < NUM_OF_REGISTERS; i++) {
            if (!strcmp(word, registers[i])) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

/*returns op code table*/
opcode *getOpCodes() {
    return opCodes;
}





/*convert int x to weird binary where 1=/ 0=.
 * input: number x
 * output: weird binary representation*/
char *convertToWeirdBinary(int x) {
    /*allocating memory to 14 bits*/
    char *bin_str = malloc(BITS);
    unsigned i;
    for (i = 0; i < BITS; i++) {
        /*creating mask for input*/
        unsigned int mask = 1u << (BITS - 1 - i);
        /* if bit is 1 return / else .*/
        bin_str[i] = (x & mask) ? '/' : '.';
    }
    /*ending the string with '/0'*/
    bin_str[BITS] = '\0';
    return bin_str;
}

/*return a substring between 2 indexes
 * input: string, from index, to index
 * output: substring of buff from index to index*/
char *getSubString(char *buff, size_t from, size_t to) {
    size_t size = to - from + 1;
    /*allocating sub_buff memory*/
    char *sub_buff = malloc(size + 1);
    /*copy memory from in length of size*/
    memcpy(sub_buff, &(buff[from]), size);
    /*ending the string with '/0'*/
    sub_buff[size] = '\0';
    return sub_buff;
}
