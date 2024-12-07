#include "converter.h"



static unsigned currentLineNumber = 1;

/*Line counter basic functios*/
void resetCurrentLineNumber(){
    currentLineNumber = 1;
}
void increaseCurrentLineNumber(){
    currentLineNumber++;
}
int getCurrentLineNumber(){
    return currentLineNumber;
}


/*Global state basics functions*/
static State globalState = startProgram;

void setGlobalState(State newState)
{
    globalState = newState;
}
State getGlobalState()
{
    State current = globalState;
    return current;
}
void (*setState)(State) = &setGlobalState;
State (*globalStateParam)() = &getGlobalState;



/*checks if the current pointer is a label decleration*/
boolean isLabelDeclaration(char *s)
{
    return strchr(s, ':') != NULL ? TRUE : FALSE;
}


/*check if the macro is open (start of the macro)*/
boolean isMacroOpen(char *s)
{
    return !strcmp(s, "mcr") ? TRUE : FALSE;
}

/*check if the macro is close (end of the macro)*/
boolean isMacroClose(char *s)
{
    return !strcmp(s, "endmcr") ? TRUE : FALSE;
}

/*Does the pointer is with the instruction*/
boolean isInstructionStrict(char *s)
{

    return ((!strcmp(s, STR_DIRECTIVE_DATA) || !strcmp(s, STR_DIRECTIVE_STRING) || !strcmp(s, STR_DIRECTIVE_ENTRY) || !strcmp(s, STR_DIRECTIVE_EXTERN))) ? TRUE : FALSE;
}

/*Hash table for the specific function*/
static Item *symbols[HASHSIZE] = {0};
static Item *macros[HASHSIZE] = {0};


/*creat a clone string (settings)*/
char *cloneString(char *s)
{
    char *copy;
    if (!(*s))
        return "";
    copy = (char *)calloc(strlen(s), sizeof(char *));
    strcpy(copy, s);
    return copy;
}

unsigned hash(char *s)
{
    unsigned hashval = 1;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/*the installetion of the hash*/
Item *install(char *name, ItemType type)
{
    unsigned hashval;
    Item *np;
    np = (Item *)malloc(sizeof(Item));

    if (np == NULL)
    {

        return NULL;
    }
    else
    {
        np->name = cloneString(name);
        if (type == Symbol)
        {
            np->val.s.attrs.code = 0;
            np->val.s.attrs.entry = 0;
            np->val.s.attrs.external = 0;
            np->val.s.attrs.data = 0;
            np->val.s.base = 0;
            np->val.s.value = 0;
            np->val.s.offset = 0;
        }
        else if (type == Macro)
        {
            np->val.m.start = -1;
            np->val.m.end = -1;
        }

        hashval = hash(name);
        np->next = (type == Symbol ? symbols[hashval] : macros[hashval]);
        if (type == Symbol)
            symbols[hashval] = np;
        else
            macros[hashval] = np;
    }

    return np;
}

/*searching in the hash*/
Item *lookup(char *s, ItemType type)
{
    Item *np;
    int i = hash(s);
    for (np = (type == Symbol ? symbols[i] : macros[i]); np != NULL; np = np->next)
        if (!strcmp(s, np->name))
            return np;

    return NULL;
}

/*The next functions is regarding the macro themselvs:
get, add and checks if it is possiable for macros*/
boolean isPossiblyUseOfMacro(char *s)
{
    return !isLabelDeclaration(s) && !isOperation(s) && !isComment(s) && !isInstructionStrict(s) && !isMacroClose(s) && !isMacroOpen(s);
}

Item *getMacro(char *s)
{
    return lookup(s, Macro);
}


Item *addMacro(char *name, int start, int end)
{
    Item *macro = lookup(name, Macro);

    if (macro != NULL)
    {
        return NULL;
    }
    else
    {
        macro = install(name, Macro);

        if (start != -1)
            macro->val.m.start = start;
        if (end != -1)
            macro->val.m.end = end;
    }

    return macro;
}

/*The main function:
its gets the file amd the current line, and adds the macro to the hash table. 
also its "expend" the macros in the new target file*/
void expend_macros(char *line, char *token, FILE *src, FILE *target)
{
    void (*currentLineNumberPlusPlus)() = &increaseCurrentLineNumber;
    static char macroName[MAX_LABEL_LENGTH] = {0}, *next;
    static long start = 0, end = 0;
    static boolean isReadingMacro = FALSE;

    if (!isReadingMacro)
    {
        if (!isMacroOpen(token))
        {
            fprintf(target, "%s", line);
            (*currentLineNumberPlusPlus)();
        }
    }

    if (!isPossiblyUseOfMacro(token) && !isMacroOpen(token) && !isMacroClose(token))
        return;

    if (isMacroOpen(token))
    {
        next = strtok(NULL, " \t\n\f\r");
        start = ftell(src);
        strcpy(macroName, next);
        isReadingMacro = TRUE;
    }
    else if (isMacroClose(token))
    {
        end = ftell(src) - strlen(line) + 1;
        addMacro(macroName, start, end);
        isReadingMacro = FALSE;
        start = end = 0;
        memset(macroName, 0, MAX_LABEL_LENGTH);
    }
    else if (isPossiblyUseOfMacro(token))
    {
        Item *p = getMacro(token);
        if (p != NULL)
        {
            long c, toCopy = p->val.m.end - p->val.m.start;
            long lastPosition = 0;
            fseek(target, -strlen(line), SEEK_CUR);
            lastPosition = ftell(src);
            fseek(src, p->val.m.start, SEEK_SET);

            while (--toCopy && (c = fgetc(src)) != EOF)
                fputc(c, target);

            fseek(src, lastPosition, SEEK_SET);
        }
    }
}
/*this function gets a file and a target file, and rewrite the first file to the target file while expending the macros*/
void macroIteration(FILE *src, FILE *target)
{
    char line[MAX_LINE_LENGTH] = {0};
    char lineClone[MAX_LINE_LENGTH] = {0};
    char *token, c;
    int i = 0;
    void (*resetCurrentLineCounter)() = &resetCurrentLineNumber;
    (*resetCurrentLineCounter)();

    while (((c = fgetc(src)) != EOF))
    {
        line[i++] = c;

        if (i >= MAX_LINE_LENGTH - 2 && !isspace(c))
            c = '\n';

        if ((*globalStateParam)() == assemblyCodeFailedToCompile)
            return;

        if (c == '\n')
        {
            if (i > 0)
            {
                strncpy(lineClone, line, i);
                token = strtok(lineClone, " \t\n\f\r");
                if (token != NULL)
                    expend_macros(line, token, src, target);

                memset(lineClone, 0, i);
                memset(line, 0, i);
                i = 0;
            }
        }
    }

    if (i > 0)
    {
        strcpy(lineClone, line);
        token = strtok(lineClone, " \t\n\f\r");
        if (token != NULL)
            expend_macros(line, token, src, target);
    }

    if ((*globalStateParam)() != assemblyCodeFailedToCompile)
        (*setState)(firstRun);

    fseek(target, 0, SEEK_SET);
}