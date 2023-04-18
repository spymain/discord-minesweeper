CC=gcc
CF=-g -Wall
OF=$(CF) -c
NME=test

all: clean $(NME)

$(NME): main.c fio.o
	$(CC) $^ $(CF) -o $@
fio.o: fio.c fio.h
	$(CC) $< $(OF)
clean:
	clear
	$(RM) $(NME) *.o
diff:
	clear
	git diff
	git status
