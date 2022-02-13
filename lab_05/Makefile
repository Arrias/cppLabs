all: lab_05

obj/clist.o: src/clist.c include/clist.h
	mkdir -p obj
	gcc -Wall -Werror -pedantic -Wextra  -c src/clist.c -o obj/clist.o -I include

obj/point_list.o: src/point_list.c include/point_list.h
	mkdir -p obj
	gcc -Wall -Werror -pedantic -Wextra  -c src/point_list.c -o obj/point_list.o -I include

obj/main.o: src/main.c include/point_list.h
	mkdir -p obj
	gcc -Wall -Werror -pedantic -Wextra  -c src/main.c -o obj/main.o -I include

lab_05: obj/clist.o obj/point_list.o obj/main.o
	gcc obj/clist.o obj/main.o obj/point_list.o -o lab_05

clean:
	rm -R obj lab_05