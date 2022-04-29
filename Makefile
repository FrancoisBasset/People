main: build libpeople.a main.o
	gcc -g -Werror build/main.o build/libpeople.a -o build/main
	
main.o: build main.c
	gcc -g -Werror -c main.c -o build/main.o
	
libpeople.a: build people.o file.o
	ar -q build/libpeople.a build/people.o build/file.o
	
file.o: build file.c
	gcc -g -Werror -c file.c -o build/file.o

people.o: build people.c
	gcc -g -Werror -c people.c -o build/people.o

build:
	mkdir build
	
clean:
	rm -r build

check:
	cppcheck --language=c --enable=all --template=gcc --suppress=missingIncludeSystem .
	valgrind build/main
