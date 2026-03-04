
#
# Operating System Design / Diseño de Sistemas Operativos
# (c) ARCOS.INF.UC3M.ES
#
# @file 	Makefile
# @brief 	Makefile for OSD file system laboratory
# @date		Last revision 01/04/2020
#


# Variables

CC=gcc
CFLAGS=-g -Wall -Werror -I.
AR=ar
MAKE=make

LIBFS_OBJS=./filesystem/blocks_cache.o ./filesystem/filesystem.o ./filesystem/crc.o ./zlib/crc32.o
LIBFS_NAME=libfs.a


# Rules

all: init create_disk test

init:
	@echo ""
	@echo "Diseño de Sistemas Operativos / Operating System Design"
	@echo "P2: Diseño e implementación de sistema de un ficheros"
	@echo "Recordatorio de uso de make:"
	@echo "* make       -> compilar / to compile"
	@echo "* make clean -> borrar archivos intermedios / to remove temporal files"
	@echo ""

create_disk: create_disk.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(LIBFS_NAME)
	$(CC) $(CFLAGS) -o test test.c pr_54_module_tests.c libfs.a cmocka.dll

$(LIBFS_NAME): $(LIBFS_OBJS)
	$(AR) rcv $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -f $(LIBFS_NAME) $(LIBFS_OBJS) test create_disk create_disk.o
	rm -fr ./create_disk.dSYM ./test.dSYM

