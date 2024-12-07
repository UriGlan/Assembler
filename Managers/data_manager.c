
#include "Managers.h"

/*pointer to the first node*/
static data_ptr head = NULL;

/*adding a number to the data list
 * input: a  number, line number and dc
 * output: add to the data list if valid*/
void addNumber(char *number, int line, int *DC) {
    /*temporary data node*/
    data_ptr tmp = NULL;
    /*pointer for strtol error checking*/
    char *ptr = NULL;
    /*temporary holder for the converted number*/
    long int tmpNum;

    /*get number value of string*/
    tmpNum = strtol(number, &ptr, DECIMAL);
    /*if strtok contains a char add error*/
    if (*ptr != '\0') {
        addError("Invalid number contains chars", line, number);
        return;
    }

    /*if number is out of 14-bit range add error*/
    if ((tmpNum < MIN_NUMBER_DATA) || (tmpNum > MAX_NUMBER_DATA)) {
        addError("Number is out of range", line, number);
        return;
    }
    /*create new pointer to data, allocate memory*/
    tmp = malloc(sizeof(data));
    checkAllocation(tmp);
    /*assign value*/
    tmp->value = (short int) tmpNum;
    tmp->next = NULL;
    /*if the list is empty*/
    if (!head) {
        /*make head point to temp*/
        head = tmp;
    }
        /*if list is not empty*/
    else {
        /*pointer to head*/
        data_ptr p = head;
        /*make p point to last node*/
        while (p->next)
            p = p->next;
        /*make tmp the last node*/
        p->next = tmp;
    }
    (*DC)++;
}

/*spiting numbers received in .data directive and add it to node
 * input: string as a parameter, line number and dc
 * output: splits it the numbers and add to data list.*/
void splitNumbersAndAdd(char *word, int line, int *DC) {
    /*if nothing followed .data add error*/
    if (!(word = strtok(NULL, " ,\t\n"))) {
        /*add error and return*/
        addError("Data directive is missing arguments after declaration", line, NULL);
        return;
    }
        /*if word is not null*/
    else {
        /*add all words*/
        addNumber(word, line, DC);
        while ((word = strtok(NULL, " ,\t\n"))) {
            addNumber(word, line, DC);
        }
    }
}

/*adding a char to data list
 * input: a char
 * output: add to data list*/
void addChar(char c) {
    /*temporary data node*/
    data_ptr tmp = malloc(sizeof(data));
    /*Assign node with character and set next to NULL*/
    tmp->value = c;
    tmp->next = NULL;
    /*if list is empty*/
    if (!head) {
        /*make head point to temp*/
        head = tmp;
    }
        /*if list is not empty*/
    else {
        /*pointer to head*/
        data_ptr p = head;
        /*make p point to last node*/
        while (p->next)
            p = p->next;
        /*make tmp the last node*/
        p->next = tmp;
    }
}

/*checking if string is valid, if so, adding each char to data list
 * input: a string, line number
 * output: add to data list*/
void addString(char *string, int line, int *DC) {
    /*if we only received a " add error*/
    if (!strcmp(string, "\"")) {
        addError("String directive is missing string argument after declaration", line, NULL);
        return;
    }
    /*Check if string is surrounded by quotation marks*/

    /*Loop adding each character to the data list*/
    if ((*string == '"') && (string[strlen(string) - 1] == '"')) {
        /*change right quotation marks to null terminator*/
        /*and point string to character after left quotation mark*/
        string[strlen(string) - 1] = '\0';
        string++;
    }
        /*if it's not surrounded by quotation marks add error*/
    else {
        addError("Missing \" around string", line, NULL);
        return;
    }
    /*loops through all the data*/
    while (*string != '\0') {
        /*add the character*/
        addChar(*string);
        string++;
        /*increment data count*/
        (*DC)++;
    }
    /*add null terminator*/
    addChar(0);
    /*increment data count*/
    (*DC)++;
}

/*counts data list size
 * output: data list size*/
int countData() {
    /*Temp counter variable*/
    int counter = 0;
    /*pointer to head*/
    data_ptr ptr = head;
    /*if head is null, return counter (0)*/
    if (!ptr)
        return counter;

    /*go through the list and count each node*/
    while (ptr) {
        counter++;
        ptr = ptr->next;
    }
    /*Return the number of nodes*/
    return counter;
}

/*updates the data addresses AFTER we have all our operation words
 * input: ic
 * output: all data list addresses are updated*/
void updateDataAddresses(int IC) {
    /*pointer to head*/
    data_ptr ptr;
    ptr = head;
    /*if head is null, return*/
    if (!ptr) {
        return;
    }
    /*go through every node and assign it an address*/
    while (ptr) {
        ptr->address = IC;
        /*increment the address to be assigned to the next node*/
        IC++;
        ptr = ptr->next;
    }
}

/*Clear the data list*/
void freeData() {
    /*temp pointer to head*/
    data_ptr ptr = head;
    /*if head is null, return*/
    if (!ptr)
        return;
    /*free each data node*/
    while (ptr) {
        data_ptr tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    /*make the head pointer null*/
    head = NULL;
}

/*return pointer to head. used when exporting files*/
data_ptr getHeadData() {
    data_ptr tmp = head;
    return tmp;
}
