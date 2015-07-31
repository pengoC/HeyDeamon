EXE=watch_process
all:
	gcc -g -o $(EXE) watch_process.c

clean:
	rm -f $(EXE)
