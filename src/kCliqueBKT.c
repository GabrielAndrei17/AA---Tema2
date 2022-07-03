#include <stdio.h>
#include <stdlib.h>

int *clique;
int **graph;
int k, n, m;

int bkt(int i)
{
    if(i == k)
    {
        return 1;
    }

    int ret = 0;
    
    for(int j = 0; j < n; j++)
    {
        int ok = 1;
        for(int ii = 0; ii < i; ii++)
            if(graph[clique[ii]][j] == 0)
            {
                ok = 0;
                break;
            }
        if(ok == 1)//Optimizare: voi pune in clique[] numai daca nodul(j) este adiacent cu celelalte noduri din clique 
        {
            clique[i] = j;
            if( bkt(i + 1) == 1)
                ret = 1;
        }
    }
    return ret;
}

int main(int argc, char *argv[]){
    FILE *fp;

    fp = fopen(argv[1], "r");

    fscanf(fp, "%d", &k);
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);

    graph = (int **)calloc(n, sizeof(int *));
    clique = (int *)calloc(k, sizeof(int));

    for(int i = 0; i < n; i++)
        graph[i] = (int *)calloc(n, sizeof(int));

    for(int i = 1; i <= m; i++)
    {
        int x, y;
        fscanf(fp, "%d %d", &x, &y);

        graph[x - 1][y - 1] = 1;
        graph[y - 1][x - 1] = 1;
    }

    int ok = 0;
    for(int j = 0; j < n; j++)
    {
        clique[0] = j;
        ok =  bkt(1);
        if(ok == 1)
            break;
    } //backtracking apartine O(n^k) //timp exponential
    
    if(ok == 1)
        printf("True\n");
    else
        printf("False\n");
    
    fclose(fp);
    for(int i = 0; i < n; i++)
        free( graph[i] );

    free(graph);
    free(clique);
    
    return 0;
}