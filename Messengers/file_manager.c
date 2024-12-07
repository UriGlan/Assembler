

#include "Messengers.h"

/*opens a file in read mode
 * input: path to file
 * output: pointer to file in read mode */
FILE *receiveFile(char *path) {
    /*Open the file*/
    return openFile(path, READ_ONLY, AS_EXTENSION);
}

/*opens a file in mode specified
 * input: path mode and file type
 * output: open file pointer in the mode*/
FILE *openFile(char *path, char *mode, char *extension) {
    /*Temp file to be returned*/
    FILE *tmp = NULL;
    char full_filename[MAX_FILENAME];
    char prefix[MAX_FILENAME] = "";
    /*copy the name to change it*/
    strcpy(full_filename, path);
    /*Add the .as extension to the full path*/
    strcat(full_filename, extension);
    strcat(prefix, full_filename);
    /*Open the file. if fopen return null, exit the function and print error to screen*/
    if (!(tmp = fopen(prefix, mode))) {
        fprintf(stderr, "Unable to open file %s in mode: %s.\n", full_filename, mode);
        return NULL;
    }
    /*Return pointer to the file*/
    return tmp;
}

/*export all needed files after assembler work if finished
 * input: name of file
 * output: between 0-3 files of type ob ext ent*/
void exportFiles(char *name) {
    /*FILE pointers*/
    FILE *object = NULL;
    FILE *entries = NULL;
    FILE *externs = NULL;
    /*Word holder*/
    unsigned short int *value;
    /*Extern flag*/
    boolean isExtern = FALSE;
    /*Pointer to wordNode*/
    word_ptr word = NULL;
    /*Pointer to entry*/
    entry_ptr entry = NULL;
    /*Pointer to data*/
    data_ptr data = NULL;
    /*open an object file in write mode*/
    object = openFile(name, WRITE_ONLY, OB_EXTENSION);
    /*assign wordNode pointer with wordNode head*/
    word = getHeadWord();
    /*Print the number of words and number of data */
    fprintf(object, "%d %d\n", getWordNodeSize(), countData());
    /*go through the entire words list*/
    while (word) {
        /*Assign value with corresponding word*/
        switch (word->method) {
            case IMMEDIATE:
                value = (unsigned short int *) (&(word->holder.immediate));
                break;
            case DIRECT:
                value = (unsigned short int *) (&(word->holder.index));
                break;
            case REGISTER:
                value = (unsigned short int *) (&(word->holder.reg));
                break;
            default:
                value = (unsigned short int *) (&(word->holder.first));
        }
        /*Print the address and word in binary*/
        fprintf(object, "%d %s\n", word->address, convertToWeirdBinary(*value));
        /*If we found an external word, set flag to 0*/
        if (word->isExternal) {
            isExtern = TRUE;
        }
        word = word->next;
    }
    /*Assign pointer with data list head*/
    data = getHeadData();
    /*print all the data and addresses*/
    while (data) {
        fprintf(object, "%d %s\n", data->address, convertToWeirdBinary(data->value));
        data = data->next;
    }
    /*Assign pointer with entry list head*/
    entry = getHeadEntry();
    /*If the list is not empty*/
    if (entry) {
        /*open a file in write mode for entries*/
        entries = openFile(name, WRITE_ONLY, ENT_EXTENSION);
        /*go through the entry list and write the labels and addresses*/
        while (entry) {
            fprintf(entries, "%s %d\n", entry->label, entry->address);
            entry = entry->next;
        }
    }
    /*If we found an extern word earlier*/
    if (isExtern) {
        /*open an extern file in write mode*/
        externs = openFile(name, WRITE_ONLY, EXT_EXTENSION);
        /*assign pointer with word list head*/
        word = getHeadWord();
        /*Go through the list*/
        while (word) {
            /*if the word is external*/
            if (word->isExternal) {
                /*print the label and address*/
                fprintf(externs, "%s %d\n", word->externalLabel, word->address);
            }
            word = word->next;
        }
    }
    /*Clean up*/
    closeAllFiles(object, entries, externs);
}

/*close all files*/
void closeAllFiles(FILE *object, FILE *entries, FILE *externs) {
    if (object)
        fclose(object);
    if (entries)
        fclose(entries);
    if (externs)
        fclose(externs);
}
