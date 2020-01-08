CC=gcc
CFLAGS=-g -Wall -Werror
SOURCES=$(wildcard *.c)
DEPS=$(patsubst %.c,%.dep,$(SOURCES))

.PHONY: clean

all : read test6 merge clean

clean:
	rm *.dep *.o

read: main_read_print.o print_elf_head.o print_elf_rel.o print_elf_sect.o print_elf_symt.o \
	read_elf_head.o read_elf_rel.o read_elf_sect.o read_elf_symt.o util_bis.o \
	write_elf_head.o write_elf_section_header.o
	$(CC) $(CFLAGS) -o $@ $^

merge: main_fusion.o fusion_progbits.o fusion_rel.o fusion_symtab.o read_elf_head.o \
	read_elf_rel.o read_elf_sect.o read_elf_symt.o util_bis.o write_elf_head.o \
	write_elf_section.o section.o print_elf_symt.o ; 
	$(CC) $(CFLAGS) -o $@ $^

test6: main_test_6.o fusion_progbits.o fusion_rel.o fusion_symtab.o read_elf_head.o \
	read_elf_rel.o read_elf_sect.o read_elf_symt.o util_bis.o write_elf_head.o \
	write_elf_section_header.o section.o print_elf_symt.o  
	$(CC) $(CFLAGS) -g -o $@ $^

-include $(DEPS)

%.dep: %.c
	@$(CC) $(CFLAGS) -MM $< >$@
