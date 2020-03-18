#define _CRT_SECURE_NO_WARNINGS
# define MAXWORDS 50
#define WORDSIZE 12
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>



struct point {  //represents a point in the grid
	int x;
	int y;
};


char grid[100][100];  //the grid maximun size is 61X61


int grid_size;  //size of the grid is grid_size*grid_size2
int grid_size2;

char nullchar = '-';   //the NULL character chosen for the grid because the grid will never have lowercase alphabets so any lowercase alphabet can be used as NULL character

int max_words;  //number of words that are inserted in the grid
int flag = 0;

enum direction {   //enumerator for direction in the grid in which the word is inserted
	UP = 1,       //start the count from 1
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};



//function used to shift pont start in direction d

struct point shift_point(struct point start, enum direction d) { //start is the position of the point to be shifted in the grid, d is the direction in which the point has to shift
	int i = start.x;
	int j = start.y;
	struct point new_point;  //final position of the shifted point depends on the direction d
	switch (d) {
		//eight directions in which the point can move
	case UP:
		new_point.x = i - 1; //Move up a row
		new_point.y = j;
		break;
	case DOWN:
		new_point.x = i + 1;  //Move down a row
		new_point.y = j;
		break;
	case LEFT:
		new_point.x = i;
		new_point.y = j - 1; //Column moves left
		break;
	case RIGHT:
		new_point.x = i;
		new_point.y = j + 1; //Column moves right
		break;
	case UP_LEFT:
		new_point.x = i - 1; //Row moves up
		new_point.y = j - 1; //Column moves left
		break;
	case UP_RIGHT:
		new_point.x = i - 1; //Row moves up
		new_point.y = j + 1; //Column moves right
		break;
	case DOWN_LEFT:
		new_point.x = i + 1; //Row moves down
		new_point.y = j - 1; //Column moves to left
		break;
	case DOWN_RIGHT:
		new_point.x = i + 1; //Row moves down
		new_point.y = j + 1; //Column moves right
		break;
	default:
		new_point.x = i; //Row stays the same
		new_point.y = j; //Column stays the same
		break;
	}
	//Handle out of bounds errors
	if (new_point.x < -1 || new_point.x > grid_size || new_point.y < -1 || new_point.y > grid_size2) {
		flag = 1; 
		printf("out of bounds exception\n"); //exception handling
	}
	return new_point;  //return the new point
}


int check_insert(char* word, struct point start, enum direction d) {  //check to see if word can be inserted at start
	int i = 0;   //loop variable
	struct point new_point = start;
	while (i < (int)strlen(word)) //Iterates through the word char array
	{
		//Attempt to shift the point to the new point
		if (grid[new_point.x][new_point.y] == nullchar || grid[new_point.x][new_point.y] == word[i]) {
			new_point = shift_point(new_point, d);
			i++;
		}
		else {
			return 0;   //insertion not possible; return false
		}

		if (flag == 1)
			return 0;  //set in shift_point function due to array out of bounds exception
	}
	return 1;  //success
}


void insertWordInGrid(char *word, int i)   //function to insert word in grid
{  //i th word is being inserted

	struct point place; // the word is to inserted in the grid at point
	enum direction d;
	int trynum = 0;
	do {
		place.x = rand() % grid_size; //set to a random row
		place.y = rand() % grid_size2; //set to a random column
		d = (rand() % 8); //get a direction; any one out of 8 with equal probability
		trynum++;
		
	} while (!((check_insert(word, place, d))|| (trynum>100)));  //run the loop until we cant insert the word; give up after 100 times 
	

	int j = 0;

	struct point new_point = place;
	while (j < (int)strlen(word)) {
		grid[new_point.x][new_point.y] = (char)toupper(word[j]);   //insertion into the grid
		new_point = shift_point(new_point, d);   //shift according to direction
		j++;
	}
	
}

char generate_random_char() {   //function to generate a random char
	return 'A' + rand() % 26;
}

void fill_grid() {  //fill the remaining places with random characters
	int i, k;
	for (i = 0; i < grid_size; i++) {
		for (k = 0; k < grid_size2; k++) {
			if (grid[i][k] == nullchar) {
				grid[i][k] = generate_random_char(); //Set every null value to a random character
			}
		}
	}
}


void printGrid()   //function to print the grid
{
	int i, j;
	for (i = 0; i < grid_size; i++) {
		for (j = 0; j < grid_size2; j++) {
			


			printf("%c ", grid[i][j]);
		
		}
		printf("\n");
	}
}


void trimws(char* s)
{
	int x;
	x = strlen(s) - 1;
	while (isspace(s[x]) && (x >= 0))
	{
		s[x] = '\0';
		x -= 1;
	}
}



//Read in words
int readWords(char* wl[MAXWORDS], char* filename) {
	int num = 0;
	char line[WORDSIZE+2];//should be wordsize +1 to accomodate the null terminator
	char *p =NULL;
	FILE* f = fopen(filename, "r");
	while (!feof(f) && (strcmp(line," ")) ){
		fgets(line, WORDSIZE+2, f);//two works for whatever reason
		if (!feof(f)) {
			trimws(line);
			wl[num] = (char *)malloc(strlen(line));
			strcpy(wl[num], line);
			num++;
		}
	}
	fclose(f);
	return num;
}




int main() {
	srand(1);   //seed the random number generator
	
	char filename[100];

	printf("What is the text file name to read in words from? \n");
	scanf(" %s", &filename);

	char* wordlist[MAXWORDS];
	int wordCount;
	wordCount = readWords(wordlist, filename);
	
	printf("\nEnter the first size of the grid... (size should be less than 60 characters)\n");
	scanf("%d", &grid_size);
	printf("\nEnter the second size of the grid... (size should be less than 60 characters)\n");
	scanf("%d", &grid_size2);
	
	int i, j;

	for (i = 0; i < grid_size; i++) 
	{   //initialize the grid to null char 'z'   
		for (j = 0; j < grid_size2; j++) 
		{
			grid[i][j] = '-';
			
		}

	}
	
	max_words = wordCount;//maximum number of words to be inserted in the grid
	for (i = 0; i < max_words; i++)
	{
         insertWordInGrid(wordlist[i], i);
	}

	printGrid();
	fill_grid();
	printf("\n\n\n");
	printGrid();
	printf("\n"); //For waiting
	scanf(" %s", &filename); //For waiting
	
	return 0;
}