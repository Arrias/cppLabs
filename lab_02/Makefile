all: lab_02

obj/test.o: src/test.c
	mkdir -p obj
	gcc -c src/test.c -o obj/test.o -I include

lab_02: obj/test.o
	gcc obj/test.o -o lab_02

launch: lab_02
	./lab_02

clean:
	rm -R obj lab_02
