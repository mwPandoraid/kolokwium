all: main

obj:
	mkdir -p obj

lib:
	mkdir -p lib

coordinator: lib
	gcc -c coordinator.c -o obj/coordinator.o
	ar rcs lib/libcoordinator.a obj/coordinator.o

agent: lib
	gcc -c agent.c -o obj/agent.o
	ar rcs lib/libagent.a obj/agent.o

main: obj coordinator agent
	gcc -c main.c -o obj/main.o
	gcc obj/main.o -Llib -lcoordinator -lagent -o main

clean:
	rm -rf obj lib main

.PHONY: all coordinator agent main clean
