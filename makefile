CC=gcc
CF=-g -Wall
NME=test

all: clean $(NME)

$(NME): main.c
	$(CC) $< $(CF) -o $@

clean:
	clear
	$(RM) $(NME) *.o
diff:
	clear
	git diff
	git status
