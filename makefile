# sources 
SRC    := $(filter-out testing.c, $(wildcard *.c))
TESTSRC = testing.c linkedlist.c
OBJ     = $(SRC:.c=.o)
TESTOBJ = $(TESTSRC:.c=.o)


# target
TARGET     = ash
TARGETTEST = test

# cflags
CC       = gcc
STD      = -std=c2x
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

$(TARGETTEST): $(TESTOBJ) testing.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

testing.o: testing.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TESTOBJ) $(TARGET) $(TARGETTEST)

.PHONY: all clean testing
