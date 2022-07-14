CFLAGS = -Werror -O3

main: build libpeople.a main.o curses.o xdef.o xmenu.o xadd.o xlist.o launchx.o
	gcc $(CFLAGS) build/main.o build/curses.o build/xdef.o build/xmenu.o build/xadd.o build/xlist.o build/launchx.o build/libpeople.a -o build/people -lncurses -lX11

libpeople.a: build file.o index.o people.o utils.o
	ar -q build/libpeople.a build/file.o build/index.o build/people.o build/utils.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o build/$@

build:
	mkdir build

clean:
	rm -rf build
	rm -rf package/usr/bin/people
	rm -rf people.deb

check:
	cppcheck --language=c --enable=all --template=gcc --suppress=missingIncludeSystem .

vg: main
	valgrind build/people -gui

pkg: main
	cp build/people package/usr/bin/people
	dpkg-deb --build ./package people.deb

start: main
	startx ./build/people -gui

install:
	cp build/people /usr/bin/people

uninstall:
	rm -f /usr/bin/people
