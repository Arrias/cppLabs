all: lab_03

obj/mergesort.o: src/mergesort.c include/mergesort.h
	mkdir -p obj
	gcc -c src/mergesort.c -o obj/mergesort.o -I include

obj/main.o: src/main.c include/mergesort.h
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o -I include

lab_03: obj/mergesort.o obj/main.o
	gcc obj/mergesort.o obj/main.o -o lab_03

clean:
	rm -R obj lab_03