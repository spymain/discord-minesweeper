#include <stdio.h>
#include <stdlib.h>
#include "fio.h"

char *defPad = "||";

char *defEmotes[] = {
	":black_large_square:",
	":one:",
	":two:",
	":three:",
	":four:",
	":five:",
	":six:",
	":seven:",
	":eight:",
	":bomb:"
};

void discordFormat(char *b, int sidelen, char *filename){
	FILE *f = fopen(filename, "w");
	for(int i = 0; i < sidelen*sidelen; i++){
		if(i > 0 && !(i % sidelen))fputc('\n', f);
		fputs(defPad, f);
		fputs(
				defEmotes[(int)b[i]],
				f
		);
		fputs(defPad, f);
	}
	fclose(f);
}
