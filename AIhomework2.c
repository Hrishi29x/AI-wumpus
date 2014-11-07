#include <stdio.h>
#include <conio.h>
#include <string.h>
struct distances
{
	char	p1[25];
	char	p2[25];
	int		dist;
}data[16] = {{"Arad","Zerind",75},{"Arad","Timisoara",118},{"Zerind","Oradea",71},{"Timisoara","Lugoj",111},{"Lugoj","Mehadia",70},{"Mehadia","Dobreta",75},{"Arad","Sibiu",140},{"Dobreta","Craiova",120},{"Oradea","Sibiu",151},{"Sibiu","Rimnicu",80},{"Rimnicu","Craiova",146},{"Sibiu","Fagaras",99},{"Rimnicu","Pitesti",97},{"Craiova","Pitesti",138},{"Fagaras","Bucharest",211},{"Pitesti","Bucharest",101}};
void main()
{
		char	s[30][25],cur[25],temp[25];
		int		d[30],i,flag = 0,dcur,n,j,t,size;
				strcpy (s[0],"Arad");
				d[0] = 0;
				strcpy (s[1],"\0");
				d[1] = 0;
				size = 1;
				do
				{
					dcur = d[0];
					strcpy (cur,s[0]);
					for (n = 0; n<size; n++)
					{
						d[n] = d[n+1];
						strcpy (s[n],s[n+1]);
					}
					n--;
					for (i = 0; i<15; i++)
					{
						if (strcmp(cur,data[i].p1) == 0)
						{
							d[n] = dcur + data[i].dist;
							strcpy(s[n],data[i].p2);
							n++;
						}
						else if (strcmp(cur,data[i].p2) == 0)
						{
							d[n] = dcur + data[i].dist;
							strcpy(s[n],data[i].p1);
							n++;
						}
					}
					for (i = 0; i<n; i++)
					{
						for (j = i+1; j<n; j++)
						{
							if (d[i] > d[j])
							{
								t = d[i];
								d[i] = d[j];
								d[j] = t;
								strcpy (temp,s[i]);
								strcpy (s[i],s[j]);
								strcpy (s[j],temp);
							}
						}
					}
					for (i = 0; i<n; i++)
					{
						if (strcmp(s[i],"Arad") == 0)
						{
							for (j = i; j<n; j++)
							{
								strcpy(s[i],s[i+1]);
								d[i] = d[i+1];
							}
							n--;
						}
					}
					size = n;
					for (i = 0; i<size; i++)
					{
						printf ("\n%s : %d",s[i],d[i]);
					}
					printf ("\n\n");
					getch();
					if (strcmp(s[0],"Bucharest") == 0) flag = 1;
				}while (flag == 0);
				printf ("Total Distance : %d",d[0]);
				getch();
}



			