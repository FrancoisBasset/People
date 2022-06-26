main: build libpeople.a main.o curses.o xdef.o xmenu.o xadd.o launchx.o
	gcc -g -Werror build/main.o build/curses.o build/xdef.o build/xmenu.o build/xadd.o build/launchx.o build/libpeople.a -o build/people -lncurses -lX11

main.o: build main.c
	gcc -g -Werror -c main.c -o build/main.o

launchx.o: build launchx.c
	gcc -g -Werror -c launchx.c -o build/launchx.o

xadd.o: build xadd.c
	gcc -g -Werror -c xadd.c -o build/xadd.o

xmenu.o: build xmenu.c
	gcc -g -Werror -c xmenu.c -o build/xmenu.o

xdef.o: build xdef.c
	gcc -g -Werror -c xdef.c -o build/xdef.o

curses.o: build curses.c
	gcc -g -Werror -c curses.c -o build/curses.o

libpeople.a: build file.o index.o people.o utils.o
	ar -q build/libpeople.a build/file.o build/index.o build/people.o build/utils.o

file.o: build file.c
	gcc -g -Werror -c file.c -o build/file.o

index.o: build index.c
	gcc -g -Werror -c index.c -o build/index.o

people.o: build people.c
	gcc -g -Werror -c people.c -o build/people.o

utils.o: build utils.c
	gcc -g -Werror -c utils.c -o build/utils.o

build:
	mkdir build

clean:
	rm -rf build
	rm -rf package/usr/bin/people
	rm -rf people.deb

check:
	cppcheck --language=c --enable=all --template=gcc --suppress=missingIncludeSystem .

vg:
	valgrind build/people -gui

pkg: main
	cp build/people package/usr/bin/people
	dpkg-deb --build ./package people.deb
