#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
const size = 4;
struct game
{
	//these are game values
	int	breeze;
	int	smell;
	int	wumpus;
	int	pit;
	int	glitter;
	int	gold;
	//these are agent values
	int	agent;
	int	ok;
	int	pp; //possible pit
	int pw; //possible wumpus
	int	db;	//detected breeze	
	int	ds; //detected smell
	int	old;
}board[4][4];
int		pi,pj,win = 0,score = 0,check = 0;
void ResetBoard()
{
	int		i,j;
			for (i = 0; i<size; i++)
			{
				for (j = 0; j<size; j++)
				{
					board[i][j].breeze = 0;
					board[i][j].smell = 0;
					board[i][j].wumpus = 0;
					board[i][j].pit = 0;
					board[i][j].glitter = 0;
					board[i][j].gold = 0;
					board[i][j].agent = 0;
					board[i][j].ok = 0;
					board[i][j].pw = 0;
					board[i][j].pp = 0;
					board[i][j].db = 0;
					board[i][j].ds = 0;
					board[i][j].old = 0;
				}
			}
}
int Checker (int i, int j)
{
		if (i <=1 && j <=1) return 0;
		else return 1;
}
void FixBoard()
{
	int		i,j;
			for (i = 0; i<size; i++)
			{
				for (j = 0; j<size; j++)
				{
					if (board[i][j].wumpus == 1)
					{
						if ((i+1)<size) board[i+1][j].smell = 1;
						if ((i-1)>=0) board[i-1][j].smell = 1;
						if ((j+1)<size) board[i][j+1].smell = 1;
						if ((j-1)>=0) board[i][j-1].smell = 1;
					}
					else if (board[i][j].pit == 1)
					{
						if ((i+1)<size) board[i+1][j].breeze = 1;
						if ((i-1)>=0) board[i-1][j].breeze = 1;
						if ((j+1)<size) board[i][j+1].breeze = 1;
						if ((j-1)>=0) board[i][j-1].breeze = 1;
					}
					else if (board[i][j].gold == 1)
					{
						board[i][j].glitter = 1;
					}
				}
			}
}
void InitBoard()
{
	int		i,j,flag = 0;
			board[0][0].agent = 1;
			board[0][0].old = 1;
			board[0][0].ok = 1;
			// Randomizing location of wumpus
			while (flag == 0)
			{
				i = rand() % size;
				j = rand() % size;
				if (Checker(i,j)) flag = 1;
			}
			board[i][j].wumpus = 1;
			flag = 0;
			// Randomizing first pit
			while (flag == 0)
			{
				i = rand() % size;
				j = rand() % size;
				if (board[i][j].wumpus != 1 && Checker(i,j)) flag = 1;
			}
			board[i][j].pit = 1;
			flag = 0;
			//Randomizing the gold
			while (flag == 0)
			{
				i = rand() % size;
				j = rand() % size;
				if (board[i][j].wumpus != 1 && board[i][j].pit != 1 && Checker(i,j)) flag = 1;
			}
			board[i][j].gold = 1;
			FixBoard();
}
char ElementReturn(int i, int j)
{
	char	c;
			if (board[i][j].agent == 1) 
			{
				c = 'A';
				pi = i;
				pj = j;
			}
			else if (board[i][j].wumpus == 1) c = 'W';
			else if (board[i][j].pit == 1) c = 'P';
			else if (board[i][j].gold == 1) c = 'G';
			else c = '-';
			return c;
}
DisplayBoard()
{
	int		i,j;
	char	ch;
			for (i = size - 1; i>=0; i--)
			{
				for (j = 0; j<size; j++)
				{
					printf ("\t\t");
					ch = ElementReturn (i,j);
					printf ("%c",ch);
				}
				printf ("\n\n\n");
			}
}
void AgentDetect()
{
	int		i,j,k;
	int		numbreeze = 0,numsmell = 0;
			i = pi;
			j = pj;
			if (board[i][j].glitter == 1) printf ("Glitter detected.\n");
			if (board[i][j].breeze == 0 && board[i][j].smell == 0)
			{
					if ((i+1)<size) board[i+1][j].ok = 1;
					if ((i-1)>=0) board[i-1][j].ok = 1;
					if ((j+1)<size) board[i][j+1].ok = 1;
					if ((j-1)>=0) board[i][j-1].ok = 1;	
			}
			if (board[i][j].breeze == 1)
			{
					printf ("Breeze detected.\n");
					board[i][j].db = 1;	
			}
			else
			{
					printf ("Breeze not detected.\n");
			}
			if (board[i][j].smell == 1)
			{
					printf ("Smell detected.\n");
					board[i][j].ds = 1;
			}
			else
			{
					printf ("Smell not detected.\n");
			}
			//correcting values
			for (i = 0; i<size; i++)
			{
					for (j = 0; j<size; j++)
					{
							if (board[i][j].db == 1)
							{
									numbreeze++;
									if ((i-1)>=0) board[i-1][j].pp++;
									if ((j-1)>=0) board[i][j-1].pp++;
									if ((i+1)<size) board[i+1][j].pp++;
									if ((j+1)<size) board[i][j+1].pp++;
							}
							if (board[i][j].ds == 1)
							{
									numsmell++;
									if ((i-1)>=0) board[i-1][j].pw++;
									if ((j-1)>=0) board[i][j-1].pw++;
									if ((i+1)<size) board[i+1][j].pw++;
									if ((j+1)<size) board[i][j+1].pw++;
							}
					}
			}
			printf ("Number of smells : %d, Number of breezes : %d\n",numsmell,numbreeze);
			for (i = 0; i<size; i++)
			{
					for (j = 0; j<size; j++)
					{
							if (board[i][j].pp<numbreeze && board[i][j].pw<numsmell) board[i][j].ok = 1;
					}
			}
}
void MoveTo(int i, int j)
{
			board[pi][pj].agent = 0;
			board[i][j].agent = 1;
			board[pi][pj].old = board[pi][pj].old + 1;
			pi = i;
			pj = j;
}
int MovePossible(int i, int j)
{
			if (i == pi + 1 && j == pj) return 1;
			else if (i == pi - 1 && j == pj) return 1;
			else if (i == pi && j == pj + 1) return 1;
			else if (i == pi && j == pj - 1) return 1;
			else return 0;
}
void AgentMove()
{
	int		i,j,flag;
			flag = 0;
			printf ("Current position is %d,%d.\n",pi,pj);
			if (board[pi][pj].glitter == 1)
			{
					printf("Picked up gold, you win!\n");
					win = 1;
					score = score + 1000;
					printf("Score : %d\n",score);
			}
			else
			{
				score = score - 1;
				for (i = size-1; i>=0 && flag == 0; i--)
				{
						for (j = 0; j<size && flag == 0; j++)
						{
								if (MovePossible(i,j) == 1 && board[i][j].old == 0)
								{
										if (board[i][j].ok == 1) 
										{
											MoveTo(i,j);
											printf ("Moving to %d,%d.\n",i,j);
											flag = 1;
										}
										else printf ("Movement to %d,%d is unsafe.\n",i,j);
								}
						}
				}
				for (i = size-1; i>=0 && flag == 0; i--)
				{					
						
						for (j = size-1; j>=0 && flag == 0; j--)
						{
							if (MovePossible(i,j) == 1 && board[i][j].old >= 1 && board[i][j].old <=5)
							{
									if (board[i][j].ok == 1) 
									{
											MoveTo(i,j);
											printf ("Moving to old %d,%d.\n",i,j);
											flag = 1;
									}
									else printf ("Movement to old %d,%d is unsafe.\n",i,j);
							}
						}
				}
			}			
}
						
void main()
{
	
	char	ch;
			srand(time(NULL));
			InitBoard();
			while (1)
			{
				system("cls");
				DisplayBoard();
				AgentDetect();
				AgentMove();
				ch = getch();
				if (win == 1) ch ='n';
				if (ch == 'n') break;
			}
}
