
#include "handlers.h"

/*handling a sentence. we analyze the sentence word by word.
 * and handle each word by its type. last we add the result words ( first -> fourth) to the list
 * input: word, line number, instruction counter and the label*/
void handleOperation(char *word, int line, int *IC, char *label) {
    /*Index for loops*/
    int i;
    /*Found a command flag*/
    int found = FALSE;
    /*found matching opcode*/
    opcode foundOpCode;
    /*ic increment value*/
    int increment_value_IC = 0;
    /*Pointers to word nodes, up to 4*/
    word_ptr first = NULL;
    word_ptr second = NULL;
    word_ptr third = NULL;
    word_ptr fourth = NULL;
    /*Check if command is known*/
    for (i = 0; i < OPCODES_AMOUNT; i++) {
        /*if it is, init a new word object*/
        if (!strcmp(word, getOpCodes()[i].str)) {
            /*Set "found command" flag to true*/
            found = TRUE;
            /*save the opcode*/
            foundOpCode = getOpCodes()[i];
            /*Allocate memory for the first word*/
            first = malloc(sizeof(word_node));
            checkAllocation(first);
            /*Set all of first word's parameters*/
            setFirstWordDefault(line, foundOpCode, first);
            /*Add one to the increment value*/
            increment_value_IC++;
        }
    }
    /*add error if the command wasn't found*/
    if (!found) {
        addError("Unknown operation", line, word);
        return;
    }

    /*get parameters after word*/
    if ((word = strtok(NULL, " ,\t\n"))) {
        /*If the command is group 2, means take 2  parameters*/
        if (foundOpCode.group == GROUP_2) {
            if (!handleGroup2(word, line, &increment_value_IC, first, &second, &third))
                return;
        }
            /*if the command is group 1, means takes 1 parameters*/
        else if (foundOpCode.group == GROUP_1) {
            if (!handleGroup1(word, line, &increment_value_IC, first, &second, &third, &fourth))
                return;
        }
            /*if the command is group 0, means no parameters*/
        else {
            addError("This command doesn't takes parameters", line, NULL);
            free(first);
            return;
        }
    }
        /*If we didn't receive any parameters for the command*/
    else {
        if (first->holder.first.opcode != OPCODE_RTS && first->holder.first.opcode != OPCODE_STOP) {
            addError("This command is missing parameters", line, NULL);
            free(first);
            return;
        }
    }
    /*is label exist add it symbols table*/
    if (label)
        addSymbol(label, *IC, FALSE, TRUE, line);
    /*add needed words*/
    if (first)
        addWord(first);
    if (second)
        addWord(second);
    if (third)
        addWord(third);
    if (fourth)
        addWord(fourth);
    /*Increment the IC as needed*/
    *IC += increment_value_IC;
}

/*sets the first word default values and opcode
 * input: line number, opcode, first word pointer to set*/
void setFirstWordDefault(int line, opcode methodOpcode, word_ptr first) {
    first->method = NONE;
    first->isExternal = FALSE;
    first->missingLabel = NULL;
    first->externalLabel = NULL;
    first->line = line;
    first->holder.first.are = ABSOLUTE;
    first->holder.first.destination = 0;
    first->holder.first.source = 0;
    first->holder.first.opcode = methodOpcode.code;
    first->holder.first.param1 = 0;
    first->holder.first.param2 = 0;
    first->next = NULL;
}
