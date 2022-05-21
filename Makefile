main: build libpeople.a main.o menu.o
	gcc -g -Werror build/main.o build/menu.o build/libpeople.a -o build/people -lncurses -lmenu

main.o: build main.c
	gcc -g -Werror -c main.c -o build/main.o

menu.o: build menu.c
	gcc -g -Werror -c menu.c -o build/menu.o

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
	valgrind build/people

pkg: main
	cp build/people package/usr/bin/people
	dpkg-deb --build ./package people.deb