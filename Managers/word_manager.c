
#include "Managers.h"

/*Pointer to head*/
static word_ptr head = NULL;

/*adding a word to word list
 * input: word_node
 * output: adding it to node list*/
void addWord(word_ptr node) {
    /*If head is null*/
    /*point head to node*/
    if (!head) {
        head = node;
    }
        /*If head is not null*/
    else {
        /*Go through the list until the last node*/
        word_ptr p = head;
        while (p->next)
            p = p->next;
        /*Assign the last node's next pointer to the new node*/
        p->next = node;
    }
}

/*updating the address of all the nodes*/
void updateWordAddresses() {
    /*assign default value*/
    int address = IC_DEFAULT_VAL;
    word_ptr ptr = head;
    if (!ptr)
        return;

    while (ptr) {
        ptr->address = address;
        address++;
        ptr = ptr->next;
    }
}

/*output:getting word node size*/
int getWordNodeSize() {
    int counter = 0;
    word_ptr ptr = head;
    /*if empty*/
    if (!ptr)
        return counter;
/*iterate through all the list*/
    while (ptr) {
        counter++;
        ptr = ptr->next;
    }
    return counter;
}

/*output: void. cleans up the list*/
void freeWords() {
    word_ptr ptr = head;
    if (!ptr)
        return;
/*if not empty*/
    while (ptr) {
        word_ptr tmp = ptr;
        ptr = ptr->next;

        free(tmp->missingLabel);
        free(tmp);
    }
    head = NULL;
}

/*output: a word with missing label*/
word_ptr getMissingLabel() {
    word_ptr p = head;
/*iterate through all the nodes*/
    while (p) {
        if (p->missingLabel) {
            /*found*/
            return p;
        }
        p = p->next;
    }
    return NULL;
}

/*output: return a pointer to the head of the list*/
word_ptr getHeadWord() {
    word_ptr tmp;
    tmp = head;
    return tmp;
}
