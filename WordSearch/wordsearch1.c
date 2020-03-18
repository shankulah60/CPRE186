
#include <stdio.c>
#include <stdlib.h>
#include <string.h>
#define MAXTABLEn40
#define MAXWORDS 100


int main()
{
	char WordSearch [MAXTABLE][MAXTABLE];
	//For reading in the words
	char* wordlist[MAXWORDS];
	int wordCount;
	wordCount = readWords(wordlist, argv[1]) - 1;
}


//Read in words
int readWords(char* wl[MAXWORDS], char* filename){
	int num = 0;
	char line[10];
	char *p;
	FILE* f = fopen(filename,"r");
	while (!feof(f)) {
		fgets(line, 10, f);
		if (!feof(f) && p != NULL) {
			trimws(line);
			wl[num] = (char *)  malloc(strlen(line));
			strcpy(wl[num], line);
			num++;
			}
		} 
	fclose(f);
	return num;
}




void fillTable(char ws[MAXTABLE][MAXTABLE], char* wl[MAXWORDS], int numWords)
{
	int count = numWords, loopCounter = 0, length = 0, row = 0, col = 0, i = 0; j= 0;
	while(count > 0)
	{
		length = strlen(wl[count]);  //<----- May cause a problem (numbering)
		row = getRandomint();
		col = getRandomint();
		//Check if it fits horizontally (both directions)
		if(row + length <= MAXTABLE)
		{
			for(i = 0; i < 12; i++)
			{
				ws[row + i][col] = 
			}
		}
		else if(row - length >= 0)
		{
			for(i= 0; i < 12; i++)
			{
				ws[row - i][col] = 
			}
		}
		//Check if it fits vertically (both directions)
		else if(col + length <= MAXTABLE)
		{
			for(i = 0; i < 12; i++)
			{
				ws[row][col + j] = 
			}
		}
		else if(col - length >= 0)
		{
			for(i = 0; i < 12; i++)
			{
				ws[row][col - j] = 
			}
		}
		//Check if it fits diagonally (All directions [4])
		/*
			Type 1 -> Up and to the right
			Type 2 -> Up and to the left
			Type 3 -> Down and to the right
			Type 4 -> Down and to the left
		*/
		if(diagCheck(row, col, length, ) == 1)
		{
			diagFill(row, col, length, 1);
		}
	}
	
	count -= 1;
	
}

int diagCheck(int row, int col, int len, int type, char ws[MAXTABLE][MAXTABLE])
{
	int flag = 0;
	if(type == 1)
	{
		
	}
}

int getRandomint()
{
	int r = (rand() % (MAXTABLE + 1));
	return r;
}