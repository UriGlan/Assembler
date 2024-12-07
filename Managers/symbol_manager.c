

#include "Managers.h"

static sym_ptr head = NULL;

/*adding a label to the list
 * input: label, address, flags and line number
 * output: add a label to list*/
void addSymbol(char *label, int address, boolean isExternal, boolean isOperation, int line) {
    /*tmp symbol*/
    sym_ptr tmp = NULL;
    /*check if such symbol already exists*/
    checkIfSymbolExist(label, line);
    /*allocate memory for new symbol and symbol's label*/
    tmp = malloc(sizeof(symbol));
    checkAllocation(tmp);
    tmp->label = malloc(sizeof(char) * MAX_LINE);
    checkAllocation(tmp->label);
    /*set label data*/
    strcpy(tmp->label, label);
    tmp->address = (short) address;
    tmp->isExternal = isExternal;
    tmp->isOperation = isOperation;
    tmp->next = NULL;
    /*if list is empty*/
    /*make head point to temp*/
    if (!head) {
        head = tmp;
    }
        /*if list isn't empty*/
    else {
        /*create pointer to head*/
        sym_ptr p = head;
        /*get to the last node*/
        while (p->next)
            p = p->next;
        /*set last node's next to tmp*/
        p->next = tmp;
    }
}

/*matching the symbol's address to the ic counter after first iteration
 * input: ic
 * output: void. updates symbols address*/
void updateSymbols(int IC) {
    sym_ptr ptr = head;
    while (ptr) {
        if ((!ptr->isExternal) && (!ptr->isOperation)) {
            ptr->address += IC;
        }
        ptr = ptr->next;
    }
}


/*output: empty symbols list*/
void freeSymbols() {
    sym_ptr ptr = head;
    if (!ptr)
        return;

    while (ptr) {
        sym_ptr tmp = ptr;
        ptr = ptr->next;
        free(tmp->label);
        free(tmp);
    }
    head = NULL;
}

/*adding error is symbol already exist
 * input:label and line number
 * output: error if same label exist*/
void checkIfSymbolExist(char *label, int line) {
    sym_ptr ptr = head;
    while (ptr) {
        if (!strcmp(ptr->label, label)) {
            addError("Tried to redefine an already existing symbol with the same label", line, label);
            return;
        }
        ptr = ptr->next;
    }
}

/*finds symbol with the same name as param1: label
 * input: label
 * output: symbol with name as label*/
sym_ptr searchSymbol(char *label) {
    sym_ptr ptr = head;
    while (ptr) {
        if (!strcmp(ptr->label, label)) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}