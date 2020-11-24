# Makefiles help us compile/build stuff. 
# a # is a comment line.
# := can be used to set a varible value.
# Here we set the CC variable to be a string of "gcc"
# CC is generally used to specify your compiler.
# and CFLAGS are used to specify the flags.
CC := gcc
CFLAGS := -o
# These two lines make a list of every .c file in the current folder.
# and a list with the same name of each .c file, but with a .o suffix.
SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(SRC_FILES:.c=.o)

# this deals with dependency management of make files.
.PHONY: all clean

# this is the rule executed when we run make.
# it is executed first because it is the first rule in the file. 
# normally we name our first(defualt) rule the all rule, and make it do everythign we need.
# this rule tells us to try to make all of our .o files from the obj_files list
all: $(OBJ_FILES)

rule_test:
	$(CC) $(CFLAGS) sleep_5.o sleep_5.c

# this rule trys to find a .c file with the same name as the specified .o file
# and compiles the .c file using our compiler / flags specified above.
%.o: %.c
	$(CC) $(CFLAGS) $@ $<

# this rule removes all of our binaries (everything w/ a .o suffix)
clean:
	rm -f *.o