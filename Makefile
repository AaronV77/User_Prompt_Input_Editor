#/*-------------------------------------------------------------------
#Author: Aaron Anthony Valoroso
#Date: March 3rd, 2018
#License: BSD-3-Clause
#Email: valoroso99@gmail.com
#--------------------------------------------------------------------*/

HEADER_FILES = $(wildcard include/*.h)
SOURCE_FILES = $(wildcard src/*.c)

all: astring_lib main

astring_lib:
	$(MAKE) -C include/AString/src archive

main:
	gcc src/main.c -Iinclude -Iinclude/AString/src/ include/AString/src/astring.a -o src/$@

run:
	./src/main

run_debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./src/main

clean:
	rm -f src/*.o src/main
	$(MAKE) -C AString/src clean
