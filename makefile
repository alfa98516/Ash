# sources 
SRC     = main.c linkedlist/linkedlist.c parser/parser.c parser/lexer.c
TESTSRC = testing/testing.c parser/lexer.c
OBJ     = $(SRC:.c=.o)
TESTOBJ = $(TESTSRC:.c=.o)


# target
TARGET     = ash
TARGETTEST = test

# cflags
CC       = gcc
STD      = -std=gnu2x
WARN     = -Wpedantic
DEBUG    = -g -DDEBUG
LIBS     = -lutil
SANITIZE = -fsanitize=undefined,address
CFLAGS   = $(STD) $(WARN) $(DEBUG) $(SANITIZE)

# default build
all: $(TARGET)

# linking 
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# building
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# test build
# Intended for testing specific header files. 
testing: $(TARGETTEST)

$(TARGETTEST): $(TESTOBJ) 
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

testing.o: testing/testing.c
	$(CC) $(CFLAGS) -c $< -o $@

echo:
	echo $(OBJ)

clean:
	rm -f $(OBJ) $(TESTOBJ) $(TARGET) $(TARGETTEST)
.PHONY: all clean testing
