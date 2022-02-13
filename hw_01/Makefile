all: hw_01

obj/stego.o: src/stego.c include/stego.h include/bmp.h
	mkdir -p obj
	gcc -Wall -Werror -pedantic -Wextra -c src/stego.c -o obj/stego.o -I include

obj/bmp.o: src/bmp.c include/bmp.h
	mkdir -p obj
	gcc -Wall -Werror -pedantic -Wextra -c src/bmp.c -o obj/bmp.o -I include

obj/main.o: src/main.c include/stego.h include/bmp.h
	mkdir -p obj
	gcc -Wall -Werror -pedantic -Wextra -c src/main.c -o obj/main.o -I include

hw_01: obj/bmp.o obj/main.o obj/stego.o
	gcc obj/bmp.o obj/main.o obj/stego.o -o hw_01

clean:
	rm -R obj lab_05