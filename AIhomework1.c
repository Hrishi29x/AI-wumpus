#include <stdio.h>
#include <string.h>
#include <conio.h>

/*
Bob = 1
Jane = 2
Mary = 3
Paul = 4
Peter = 5
John = 6
*/

void main()
{
	int		data[5][2] = {{1,3},{2,3},{3,5},{4,5},{5,6}};
	int		ans[20][2];
	char	sdata[6][20] = {"Bob", "Jane", "Mary", "Paul", "Peter", "John"};
	char	ch[30];
	int		f,i,j,s = 0, flag = 0, count;
			printf ("\n?- ");
			scanf ("%s", ch);
			if (strcmp ("parent(bob,mary).",ch) == 0) f = 1;
			else if (strcmp ("parent(bob,X).",ch) == 0) f = 2;
			else if (strcmp ("parent(X,Y).",ch) == 0) f = 3;
			else if (strcmp ("ancestor(X,Y).",ch) == 0) f = 4;
			else f = 0;
			if (f == 1)
			{
					for (i = 0; i<5; i++)
					{
							if ((data[i][0] == 1) && (data[i][1] == 3)) flag = 1;
					}
					if (flag == 1) printf ("\nyes");
					else printf ("\nno");
			}
			else if (f == 2)
			{
					for (i = 0; i<5; i++)
					{
							if (data[i][0] == 1) printf ("\nX = %s",sdata[(data[i][1]-1)]);
					}
			}
			else if (f == 3)
			{
					for (i = 0; i<5; i++)
					{
							printf ("\nX = %s",sdata[(data[i][0]-1)]);
							printf ("\nY = %s",sdata[(data[i][1]-1)]);
							printf ("\n");
					}
					printf ("\nyes");
			}
			else if (f == 4)
			{
					for (i = 0; i<5; i++)
					{
							ans[s][0] = data[i][0];
							ans[s][1] = data[i][1];
							s++;
					}
					count = 0;
					do
					{
							flag = s;
							for (i = 0; i<5; i++)
							{
									for (j = 0; j<s; j++)
									{
											if (data[i][1] == ans[j][0])
											{
													ans[s][0] = data[i][0];
													ans[s][1] = ans[j][1];
													s++;
											}
									}
							}
							count++;
					}while (count != 2);
					for (i = 0; i<s; i++)
					{
							printf ("\nX = %s",sdata[(ans[i][0]-1)]);
							printf ("\nY = %s",sdata[(ans[i][1]-1)]);
							printf ("\n");
					}
					printf ("\nno");
			}
			getch();
			return;
}				