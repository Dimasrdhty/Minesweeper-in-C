#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
 
#define BOARDSIZE 12
#define WIN 1
#define LOSE 0
#define EASY 4
#define MEDIUM 7
#define HARD 10
#define SIZE 512
#define CHUNK 1024
 
char board[BOARDSIZE][BOARDSIZE];
char gboard[BOARDSIZE][BOARDSIZE];

void display_welcome();
void start_game();
void lose();
void win();
void build_board();
void build_gboard();
void print_board();
void print_minesboard();
int checkmines(int, int);
void updatemines(int, int);
int checkforwin();
void playagain();
int difficulty_game();
void menu();
void highscore_database();
void database_read();
int highscore =1030;

typedef struct
{
	char nama[SIZE];
	int scores;
}database;

database s1;
database s2;

int main()
{
    display_welcome();
    printf("\n");
    system("pause");
	menu();
    return main();
}

void display_welcome()
{
    printf ("\nAssalamualaikum wr. wb");
    printf ("\nMy name is Dimas Radhitya (1806199972)");
    printf ("\nand my name is M Fadil Hafiz (1806148763)");
    printf ("\nThis is our project!");
    printf ("\nHave Fun!!!");
    printf ("\n\n");
}

void start_game(int highscore)
{
    int row, col, a=0;
    build_board();
    build_gboard();
    print_minesboard(highscore);
    while(a<1)
    {
        do 
		{
        printf("Choose :\n");
        printf("Row--> ");
        scanf("%d", &row);
        printf("Col--> ");
        scanf("%d", &col);
        }
		while(row < 1 || row > BOARDSIZE - 2 || col < 1 || col > BOARDSIZE - 2);
        if(board[row][col] == '*')
        {
        	highscore=0;
        	printf ("\nScore : %d", highscore);
            printf("\nKamu kena ranjau!\n");
            print_board();
            lose();
        }
        else
        {
			updatemines(row, col);
        }
        print_minesboard();
		
        if(checkforwin() == WIN)
		{
        	win();
    	}
    }
}

int difficulty_game()
{
	int difficulty, difficulty_level=0;
	system("cls");
	printf("\nPlease choose the difficulty:");
	printf("\n1. Easy (4 ranjau)\n2. Medium (7 ranjau)\n3. Hard (10 ranjau)\nChoose: ");
	scanf ("%d", &difficulty);
	fflush(stdin);
	difficulty_level = difficulty;
	if (difficulty_level==3)
    {
		difficulty_level=HARD;
	}
	else if (difficulty_level==2)
    {
    	difficulty_level=MEDIUM;
	}
    else if (difficulty_level==1)
    {
    	difficulty_level=EASY;
	}
	system("cls");
	return difficulty_level;
}

void print_board()
{
    int i, j;
 
    printf("  ");
    for(i = 0; i < BOARDSIZE - 1; i++)
        printf("%d ", i);
    printf("\n");

    for(i = 0; i < BOARDSIZE; i++)
    {
        for(j = 0; j < BOARDSIZE; j++)
        {
			printf("%c ", board[i][j]);
        }
		if(i > 0 &&  i < BOARDSIZE - 1)
        {
			printf("%d", i);
		}        
		printf("\n");
    } 
}
 
void print_minesboard()
{
    int i, j;
    system("cls");
    highscore = highscore_func(highscore);
    printf ("\nScore : %d\n", highscore);
    printf("  ");
    for(i = 1; i < BOARDSIZE - 1; i++)
    {
        printf("%d ", i);
    }
	printf("\n");

    for(i = 0; i < BOARDSIZE; i++)
    {
	    for(j = 0; j < BOARDSIZE; j++)
        {
			if(i == 0 || i == BOARDSIZE - 1)
            {
				gboard[i][j] = ' ';
			}
		}
	}
 
    for(j = 0; j < BOARDSIZE; j++)
    {
		for(i = 0; i < BOARDSIZE; i++)
        {
			if(j == 0 || j == BOARDSIZE - 1)
        	{
				gboard[i][j] = ' ';
			}
		}
	}
	
    for(i = 0; i < BOARDSIZE; i++)
    {
        for(j = 0; j < BOARDSIZE; j++)
        {
            printf("%c ", gboard[i][j]);
        }
        if(i > 0 &&  i < BOARDSIZE - 1)
        {
			printf("%d", i);
        }
		printf("\n");
    }
    
}
 
void build_board(int difficulty_level)
{
    int i, j,count=0,random;
	difficulty_level = difficulty_game();
	for(i = 0; i < BOARDSIZE; i++)
    {
		for(j = 0; j < BOARDSIZE; j++)
        {
			board[i][j] = '-';
		}
	}
    srand(time(NULL));
    for(j = 0; j < BOARDSIZE; j++)
    {
        if (count<difficulty_level+1)
    	{
			random = rand() % (BOARDSIZE - 2) + 1;
			board[random][j] = '*';
			if(board[random][j] == '*')
			{
				count+=1;
			}
		}
    }
    for(i = 0; i < BOARDSIZE; i++)
    {
		for(j = 0; j < BOARDSIZE; j++)
        {
			if(i == 0 || i == BOARDSIZE - 1)
        	{
				board[i][j] = ' ';
			}
        }
    }
 
    for(j = 0; j < BOARDSIZE; j++)
    {
		for(i = 0; i < BOARDSIZE; i++)
        {
			if(j == 0 || j == BOARDSIZE - 1)
            {
				board[i][j] = ' ';
			}
		}
	}
}

void build_gboard()
{
    int i, j;
    for(i = 0; i < BOARDSIZE; i++)
    {
	    for(j = 0; j < BOARDSIZE; j++)
        {
		    gboard[i][j] = '-';
		}
	}

    for(i = 0; i < BOARDSIZE; i++)
    {
		for(j = 0; j < BOARDSIZE; j++)
        {
			if(i == 0 || i == BOARDSIZE - 1)
            {
				gboard[i][j] = ' ';
			}
		}
	}
 
    for(j = 0; j < BOARDSIZE; j++)
    {
		for(i = 0; i < BOARDSIZE; i++)
        {
			if(j == 0 || j == BOARDSIZE - 1)
            {
				gboard[i][j] = ' ';
			}
		}
	}
}

int checkmines(int row, int col)
{
    int mines = 0;
    if(board[row - 1][col] == '*')
        {mines++;}
    if(board[row + 1][col] == '*')
        {mines++;}
    if(board[row][col - 1] == '*')
        {mines++;}
    if(board[row][col + 1] == '*')
        {mines++;}
 
    if(board[row - 1][col + 1] == '*')
        {mines++;}
    if(board[row - 1][col - 1] == '*')
        {mines++;}
    if(board[row + 1][col + 1] == '*')
        {mines++;}
    if(board[row + 1][col - 1] == '*')
        {mines++;}
    return mines;
}

void lose()
{
    char lagi;
    printf("\nKamu kalah!");
    printf("\nApakah kamu mau main lagi? (y/n)--> ");
    scanf(" %c", &lagi);
 
    if(toupper(lagi) == 'Y')
    {
    	int highscore=1030;
        system("cls");
        start_game(highscore);
    }
 
    else
        exit(0);
}

void win()
{
    char ans;
 
    printf("\nYeay! Kamu menang!");
    printf("\nApakah kamu mau main lagi? (y/n)--> ");
    scanf(" %c", &ans);
 
    if(toupper(ans) == 'Y')
    {
    	int highscore=1030;
        system("cls");
        start_game(highscore);
    }
 
    else
        exit(0);
}
 
void updatemines(int row, int col)
{
    int mines = 0;
    int i = 0;
 
        mines = checkmines(row, col);
        gboard[row][col] = (char)(((int)'0') + mines);
        mines = 0;
        while(mines < 1 && i < row)
        {
            mines = checkmines(row - i, col);
            gboard[row - i][col] = (char)(((int)'0') + mines);
            i++;
        }
        i = 0;
        mines = 0;
        while(mines < 1 && row + i < BOARDSIZE - 2)
        {
            mines = checkmines(row + i, col);
            gboard[row + i][col] = (char)(((int)'0') + mines);
            i++;
        }
        i = 0;
        mines = 0;
        while(mines < 1 && i < col)
        {
            mines = checkmines(row, col - i);
            gboard[row][col - i] = (char)(((int)'0') + mines);
            i++;
        }
        i = 0;
        mines = 0;
        while(mines < 1 && col + i < BOARDSIZE - 2)
        {
            mines = checkmines(row, col + i);
            gboard[row][col + i] = (char)(((int)'0') + mines);
            i++;
        }
        i = 0;
        mines = 0;
        while(mines < 1 && col + i < BOARDSIZE - 2 && i < row)
        {
            mines = checkmines(row - i, col + i);
            gboard[row + i][col + i] = (char)(((int)'0') + mines);
            i++;
        }
        i = 0;
        mines = 0;
        while(mines < 1 && i < row && i < row && i < col)
        {
            mines = checkmines(row - i, col - i);
            gboard[row - i][col - i] = (char)(((int)'0') + mines);
            i++;
        }
        i = 0;
        mines = 0;
        while(mines < 1 && row + i < BOARDSIZE - 2 && col + i < BOARDSIZE - 2)
        {
            mines = checkmines(row + i, col + i);
            gboard[row + i][col + i] = (char)(((int)'0') + mines);
            i++;
        }
        i = 0;
        mines = 0;
        while(mines < 1 && row + i < BOARDSIZE - 2 && i < col)
        {
            mines = checkmines(row + i, col - i);
            gboard[row + i][col - i] = (char)(((int)'0') + mines);
            i++;
        }
}

int checkforwin()
{
    int i, j;
 
    for(i = 1; i < BOARDSIZE - 1; i++)
        for(j = 1; j < BOARDSIZE - 1; j++) {
            if(gboard[i][j] == '-' && board[i][j] != '*')
                return LOSE;
        }
 
    return WIN;
}

int highscore_func(highscore)
{
	highscore-=30;
	return highscore;
}

void menu()
{
	int choose_menu;
	system("cls");
	printf ("\nPilih menu :\n");
	printf ("1. Play\n");
	printf ("2. Highscore\n");
	printf ("Pilih (1/2):");
	scanf  ("%d", &choose_menu);
    if (choose_menu==1)
	{
		start_game(highscore);
	}
	else if (choose_menu==2)
	{
		highscore_database();
	}
	else
	{
		printf ("\nPilih lg");
		getch();
		menu();
	}
}

void database_read()
{
	system ("cls");
	printf ("\n");
	printf("\nHighscore :\n\n");
	char buf[CHUNK];
	FILE *file;
	size_t nread;

	file = fopen("highscore.txt", "r");
	if (file) {
    char str1[1000], str2[200], str3[200], str4[200];
        fscanf(file, "%s %s %s %s", str1, str2, str3, str4);
        printf("%s\n", str1);
        printf("%s\n", str2);
        printf("%s\n", str3);
        printf("%s\n", str4);
    if (ferror(file)) {
        printf ("File Error");
    }
    fclose(file);
	}
}

void highscore_database()
{
	database_read();
	printf ("\n\n");
	system ("pause");
	menu();
}
