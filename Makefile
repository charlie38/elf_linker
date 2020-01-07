CC=gcc
CFLAGS=-g -Wall -Werror
SOURCES=$(wildcard *.c)
DEPS=$(patsubst %.c,%.dep,$(SOURCES))
OBJ=$(patsubst %.c,%.o,$(SOURCES))

.PHONY: clean

all : read clean

clean:
	rm *.dep *.o

read: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

-include $(DEPS)

%.dep: %.c
	@$(CC) $(CFLAGS) -MM $< >$@
