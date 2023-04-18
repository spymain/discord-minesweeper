#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fio.h"

#define BOMB_RATIO 0.2

int main(int argc, char *argv[]){
	char *board;
	int sidelen, bombs, head;
	if(argc < 2 || !atoi(argv[1])){
		printf(
				"Usage: %s <sidelength> [bombs] [outfile]\n",
				argv[0]
		);
		return -1;
	}

	srand(time(NULL));

	sidelen = atoi(argv[1]);
	bombs = argc > 2 && atoi(argv[2]) ? atoi(argv[2]) : (int)((double)(sidelen*sidelen) * BOMB_RATIO);
	board = malloc(sizeof(char)*sidelen*sidelen);
	memset(board, 0, sidelen * sidelen);

	printf(
			"Generating %i x %i with %i bombs...",
			sidelen,
			sidelen,
			bombs
	);

	for(int i = 0; i < bombs;)//Fill board with bombs
		if(!board[(head = rand() % (sidelen * sidelen))]){
			board[head] = 9;
			i++;
		}

	for(int i = 0; i < sidelen; i++)				//Top Row
		if(board[i] == 0){	//Not a bomb
			if(board[i + sidelen] == 9)		board[i]++;	//down

			if(i > 0){		//can check left side
				if(board[i - 1] == 9)		board[i]++;	//left
				if(board[i - 1 + sidelen] == 9)	board[i]++;	//downleft
			}

			if(i < sidelen - 1){	//can check right side
				if(board[i + 1] == 9) 		board[i]++;	//right
				if(board[i + 1 + sidelen] == 9)	board[i]++;	//downright
			}
		}
	for(int i = sidelen; i < (sidelen * (sidelen - 1)); i++ )	//Middle part
		if(board[i] == 0){	//Not a bomb
			if(board[i - sidelen] == 9)		board[i]++;	//up
			if(board[i + sidelen] == 9)		board[i]++;	//down
			if(i % sidelen){	//can check left side
				if(board[i - 1] == 9)		board[i]++;	//left
				if(board[i - 1 + sidelen] == 9)	board[i]++;	//downleft
				if(board[i - 1 - sidelen] == 9)	board[i]++;	//upleft
			}
			if(i + 1 % sidelen){	//can check right side
				if(board[i + 1] == 9)		board[i]++;	//right
				if(board[i + 1 + sidelen] == 9)	board[i]++;	//downright
				if(board[i + 1 - sidelen] == 9)	board[i]++;	//upright
			}
		}
	for(int i = sidelen * (sidelen - 1); i < sidelen*sidelen; i++)	//Bottom Row
		if(board[i] == 0){	//Not a bomb
			if(board[i - sidelen] == 9)		board[i]++;	//up
			if(i % sidelen){	//can check left side
				if(board[i - 1] == 9)		board[i]++;	//left
				if(board[i - 1 - sidelen] == 9)	board[i]++;	//upleft
			}
			if(i + 1 % sidelen){	//can check right side
				if(board[i + 1] == 9)		board[i]++;	//right
                                if(board[i + 1 - sidelen] == 9)	board[i]++;	//upright
			}
		}
	puts("Finished.\n");
	//Print board
	for(int i = 0; i < sidelen*sidelen; i++){
		if(!(i % sidelen)) puts("");
		printf(
				" %c ",
				board[i] < 9 ? board[i] == 0 ? ' ' : '0' + board[i] : 'B'
		);
	}
	puts("\n");
	//Print to file
	if(argc > 3){
		printf("Saving to %s...", argv[3]);
		discordFormat(board, sidelen, argv[3]);
		puts("Done.");
	}
	free(board);
	return 0;
} 
