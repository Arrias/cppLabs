
all: lab_04

obj/clist.o: src/clist.c include/clist.h
	mkdir -p obj
	gcc -c src/clist.c -o obj/clist.o -I include

obj/main.o: src/main.c include/clist.h
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o -I include

lab_04: obj/main.o obj/clist.o
	gcc obj/main.o obj/clist.o -o lab_04

clean:
	rm -R obj lab_04
