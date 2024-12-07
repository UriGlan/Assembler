

#include "Managers.h"

/*Pointer to head of list*/
static entry_ptr head = NULL;


/*adding an entry to the entries list
 * input: a  label, line number
 * output: add to the data list if valid*/
void addEntry(char *label, int line) {
    /*temp pointer to entry*/
    entry_ptr tmp = NULL;
    /*Check if a similar entry exists*/
    if (!(isEntryExist(label))) {
        addError("Tried to redefine an already existing label", line, label);
        return;
    }
    /*allocate memory for new node*/
    tmp = malloc(sizeof(entry));
    checkAllocation(tmp);
    /*copy the label*/
    tmp->label = malloc(sizeof(char) * MAX_LINE);
    strcpy(tmp->label, label);
    /*assign parameters*/
    tmp->address = 0;
    tmp->line = line;
    tmp->hasAddress = FALSE;
    tmp->next = NULL;
    /*If head is null, assign it with first node*/
    if (!head) {
        head = tmp;
    }
        /*if head is not null*/
    else {
        entry_ptr p = head;
        while (p->next)
            p = p->next;
        p->next = tmp;
    }
}

/* checks if an entry with the same label already exists
 * input: label
 * output: is already exist*/
boolean isEntryExist(char *label) {
    entry_ptr ptr = head;
    /*Go through the list*/
    while (ptr) {
        /*If we find a node with the same label*/
        if (!strcmp(ptr->label, label)) {
            return FALSE;
        }
        ptr = ptr->next;
    }
    /*If such node doesn't exist, return true*/
    return TRUE;
}

/*clears the list of entries*/
void freeEntries() {
    entry_ptr ptr = head;
    if (!ptr)
        return;
    while (ptr) {
        entry_ptr tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    head = NULL;
}

/* returns first entry without an address*/
entry_ptr getEntryWithAddress() {
    entry_ptr ptr = head;
    while (ptr) {
        if (!ptr->hasAddress) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

/* returns a pointer to the head*/
entry_ptr getHeadEntry() {
    entry_ptr tmp = head;
    return tmp;
}