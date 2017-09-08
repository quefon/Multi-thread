all:hw12
.PHONY:all
hw12:hw12.c	
	gcc -pthread hw12.c -o pi
clean:
	rm pi
