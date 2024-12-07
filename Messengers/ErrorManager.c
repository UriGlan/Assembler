

#include "Messengers.h"

/*pointer to head*/
static err_ptr head = NULL;

/*adds error to the list of errors
 * input:error, line of error and a message
 * output: void. adds error to list of errors*/
void addError(char *err, int line, char *str) {
    /*create a new error node*/
    err_ptr tmp = malloc(sizeof(error));
    checkAllocation(tmp);

    /*assign error string*/
    tmp->message = err;
    /*assign error line*/
    tmp->line = line;
    /*if we received another string*/
    if (str) {
        /*check if last char is newline, if so, remove it*/
        if (str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] = 0;
        }
        /*assign the string to str*/
        tmp->input = malloc(sizeof(char) * MAX_LINE);
        checkAllocation(tmp->input);
        strcpy(tmp->input, str);
    }
        /*if we didn't receive another string*/
    else {
        /*set str to null*/
        tmp->input = NULL;
    }
    /*set next to null*/
    /*point head to temp*/
    tmp->next = NULL;
    if (!head) {
        head = tmp;
    }
        /*if head is not null*/
    else {
        err_ptr p = head;
        while (p->next)
            p = p->next;
        /*point it to the new error*/
        p->next = tmp;
    }

}

/*return if error in node list exist*/
boolean isError() {
    if (head)
        return TRUE;
    else
        return FALSE;
}

/* returns the last line an error appears in*/
int getLastErrorLine() {
    err_ptr p;
    int maxLine = 1;
    p = head;
    if (!p)
        return 0;
    while (p) {
        if (p->line > maxLine)
            maxLine = p->line;
        p = p->next;
    }
    return maxLine;
}

/*write the errors to an errors file
 * input: filename
 * output: void. writes to srderr*/
void printErrors(char *filename) {
    err_ptr ptr;
    int maxLine = getLastErrorLine();
    int index = 1;
    /*create filename for this input file*/
    char error_filename[MAX_FILENAME];
    strcat(error_filename, filename);
        /*write the errors line by line*/
        while (index <= maxLine) {
            ptr = head;
            while (ptr) {
                if (ptr->line == index) {
                    if (ptr->input)
                        fprintf(stderr, "%s: [ERROR] line %d:\t %s \"%s\".\n",filename, ptr->line, ptr->message, ptr->input);
                    else {
                        fprintf(stderr, "%s: [ERROR] line %d:\t %s.\n",filename, ptr->line, ptr->message);
                    }
                }
                ptr = ptr->next;
            }
            index++;
        }
        ptr = head;
        /*print errors with NULL_LINE value such as file is empty or memory exceeded*/
        while (ptr) {
            if (ptr->line < 0) {
                if (ptr->input)
                    fprintf(stderr, "%s: [ERROR] %s: \"%s\"\n.",filename, ptr->message, ptr->input);
                else {
                    fprintf(stderr, "%s: [ERROR] %s.\n",filename, ptr->message);
                }
            }
            ptr = ptr->next;
        }

}

/*clean up the errors list*/
void freeErrors() {
    err_ptr ptr = head;
    if (!ptr)
        return;

    while (ptr) {
        err_ptr tmp = ptr;
        ptr = ptr->next;
        free(tmp->input);
        free(tmp);
    }
    head = NULL;
}
