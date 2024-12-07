# Declaration of variables
CC = gcc
CC_FLAGS = -g -Wall -ansi -pedantic

# List of directories to search for .c files:
dirs = . Converter Managers Messengers Utils Converter/Handlers Converter/Parsers

# Make a list of *.c source files found in dirs
SOURCES = $(shell find ./ -name '*.c')
INCLUDES = $(shell find ./ -name '*.h')

# File names
EXEC = assembler
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(EXEC): $(OBJECTS) $(INCLUDES)
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.c  $(INCLUDES)
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
