/*
 * adjescency_matrix.c
 *
 * Created: 24-11-2017 19:26:29
 *  Author: Swathi S
 */


#include <avr/io.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "buzzer.h"


#define X 49
#define Y 7

int start=45; ///green home
int g=0;
int max=0;


struct Maze
{
    int maze_array[Y][Y];
};

struct Graph
{
    _Bool graph_array[X][X];
};


struct Path_Array
{
	int path[X];
};
struct Path_Array path1;


struct Path_Array init_path()
{

	struct Path_Array path;
	for(int i = 0; i < X; i++)
		path.path[i] = -1;
	return path;
}
int coord_to_flat(int x, int y)
{
	return x*Y + y;
}

struct Graph buildGraph(struct Maze maze)
{
    struct Graph adj_matrix;

        int m;

    int n;
    int coord_to_flat(int,int);
    for(int i=0; i<X; i++)
        for(int j=0;j<X;j++)
        {
            adj_matrix.graph_array[i][j]=0;

        }
    for(int i=0;i<Y;i++)
        for(int j=0;j<Y;j++)
        {
            m=coord_to_flat(i,j);

            n=maze.maze_array[i][j];


            switch (n)
            {
            case 0:
                adj_matrix.graph_array[m][m+1]=1;
                adj_matrix.graph_array[m][m-1]=1;
                adj_matrix.graph_array[m][m+Y]=1;
                adj_matrix.graph_array[m][m-Y]=1;
                break;
            case 1:
                adj_matrix.graph_array[m][m+1]=1;
                adj_matrix.graph_array[m][m-1]=1;
                adj_matrix.graph_array[m][m+Y]=1;
                break;
            case 2:
                adj_matrix.graph_array[m][m-Y]=1;
                adj_matrix.graph_array[m][m-1]=1;
                adj_matrix.graph_array[m][m+Y]=1;
                break;
            case 3:
                adj_matrix.graph_array[m][m-1]=1;
                adj_matrix.graph_array[m][m+Y]=1;
                break;
            case 4:
                adj_matrix.graph_array[m][m+1]=1;
                adj_matrix.graph_array[m][m-1]=1;
                adj_matrix.graph_array[m][m-Y]=1;
                break;
            case 5:
                adj_matrix.graph_array[m][m-1]=1;
                adj_matrix.graph_array[m][m+1]=1;
                break;
            case 6:
                adj_matrix.graph_array[m][m-1]=1;
                adj_matrix.graph_array[m][m-Y]=1;
                break;
            case 7:
                adj_matrix.graph_array[m][m-1]=1;
                break;
            case 8:
                adj_matrix.graph_array[m][m-Y]=1;
                adj_matrix.graph_array[m][m+Y]=1;
                adj_matrix.graph_array[m][m+1]=1;
                break;
            case 9:
                adj_matrix.graph_array[m][m+Y]=1;
                adj_matrix.graph_array[m][m+1]=1;
                break;
            case 10:
                adj_matrix.graph_array[m][m-Y]=1;
                adj_matrix.graph_array[m][m+Y]=1;
                break;
            case 11:
                adj_matrix.graph_array[m][m+Y]=1;
                break;
            case 12:
                adj_matrix.graph_array[m][m-Y]=1;
                adj_matrix.graph_array[m][m+1]=1;
                break;
            case 13:
                adj_matrix.graph_array[m][m+1]=1;
                break;
            case 14:
                adj_matrix.graph_array[m][m-Y]=1;
                break;
            case 15:

                break;
            default:
                printf("error");
                break;

            }

        }
        printf("\n");
for (int i=0; i<X; i++)
	{
		for (int j=0;j<X;j++)
		{
			printf("%d ",adj_matrix.graph_array[i][j]);
		}
		printf("\n");
	}
printf("\n");





   return adj_matrix;
}

struct Path_Array findPath(struct Graph graph, int start, int finish)
{
	struct Path_Array path = init_path();

	int i;
	int j;
	int adj[X][X];
	int m=0;
	int pat[X];
	int visited[X];
	int n=X;
	int k=0;
	int d=0;
	int f=1;

    for(i=0;i<n;i++)
        pat[i]=0;
    for(i=0;i<n;i++)
        visited[i]=0;


    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
         adj[i][j] = graph.graph_array[i][j] ;

    pat[0]=start;
    i=start;
buzzer_on();
        for(j=0;j<n;j++)
        {   //printf("  %d...%d   ",i,j);
            /*if(pat[m]==finish)
                     break;*/



         if(adj[i][j]==1&&(visited[i]!=1||visited[j]!=1))
                 {  /*f=i-finish;
                    if(f<0)
                        f=(f*-1);*/
                     k=i;
			if(adj[i][k+1]==1&&(visited[i]!=1||visited[k+1]!=1))
			{
				d= ((k+1)-finish);
				if (d<0)
				d=(d*-1);
				if (d<f)
				{
					f=d;
					j = (k+1);

				}

			}

			if(adj[i][k-1]==1&&(visited[i]!=1||visited[k-1]!=1))
			{
				d= ((k-1)-finish);
				if (d<0)
				d=(d*-1);
				if (d<f)
				{
					f=d;
					j = (k-1);

				}
			}
			if(adj[i][k+Y]==1&&(visited[i]!=1||visited[k+Y]!=1))
			{
				d = ((k+Y)-finish);
				if (d<0)
				d=(d*-1);
				if (d<f)
				{
					f=d;
					j = (k+Y);

				}
			}
			if(adj[i][k-Y]==1&&(visited[i]!=1||visited[k-Y]!=1))
			{
				d = ((k-Y)-finish);
				if (d<0)
				d=(d*-1);
				if (d<f)
				{
					f=d;
					j = (k-Y);

				}
			}

                    visited[i]=1;
                    visited[j]=1;
                    m++;
                    pat[m]=j;

                    /*for(i=0;i<=m;i++)
                    {
                        if(pat[i]==24)////////
                            goto loop3;
                    }*/
                    if(pat[m]==finish)
                     break;
                    i=j;
                    j=0;
					continue;
                }
                else if(adj[i][j]==1&&visited[i]==1&&visited[j]==1)
                {
                    for(j=0;j<n;j++)
                    {
                        if(adj[i][j]==1&&visited[j]!=1)
                            break;
                    }
                    if(adj[i][j]==1&&visited[j]!=1)
                            continue;
                    m--;
                    i=pat[m];
                    j=0;
					continue;
                }
        }


        for(i=0;i<n;i++)
        {
            if(i>m)
            pat[i]=-1;
        }

        for(i=0;i<n;i++)
            {
                path.path[i]=pat[i];

            }






    return path;
}

struct Path_Array main_function(struct Maze maze, int start, int finish)
{

	struct Graph adjacency_matrix = buildGraph(maze);
	

	struct Path_Array path = findPath(adjacency_matrix, start, finish);
	

	return path;
}
