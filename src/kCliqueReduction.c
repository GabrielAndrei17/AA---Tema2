#include <stdio.h>
#include <stdlib.h>

void reduction(int **graph, int k, int n)
{
    for(int i = 0; i < k; i++)
    {
        if(i != 0)
            printf("^");

        //clauza corespunzatoare insusirii
        //pe pozitia i in clique trebuie sa avem un nod
        printf("(x%dv1", i + 1);
        for(int v = 1; v < n; v++)
        {
            printf("Vx%dv%d", i + 1, v + 1);
        }
        printf(")\n"); // -> o clauza
        // -> O(n)

        //clauza corespunzatoare insusirii
        //un nod nu poate fi pe pozitii multiple in k-Clique
        for(int j = 0; j < k; j++)
            if(i != j)
                for(int v = 0; v < n; v++)    
                {
                    printf("^(~x%dv%dV~x%dv%d)\n", i + 1, v + 1, j + 1, v + 1);
                }
            // -> n(k-1) clauze
            // -> O(n * k)

        //clauza corespunzatoare insusirii
        //daca v este in k-Clique => pe o pozitie (in k-Clique) diferita se afla un nod adiacent cu v
        for(int u = 0; u < n; u++)
        {
            for(int j = 0; j < k; j++)
                if(i != j)
                {
                    printf("^(~x%dv%d", i + 1, u + 1);
                    for(int v = 0; v < n; v++)
                        if(graph[u][v] == 1)
                        {
                            printf("Vx%dv%d", j + 1, v + 1);    
                        }

                    printf(")\n");
                }
        }
            // -> n(k-1) clauze
            // -> O(n^2 * k)
        
    }
    /*
    Total clauze : 2*n*(k-1)*k + k
    Total variabile in SAT: n*k
    Total operatii: (kn^2 + kn + n)*k apartine lui O(n^2 * k^2)

    */
}

int main(int argc, char *argv[]){
    FILE *fp;

    int **graph;
    int k, n, m;

    fp = fopen(argv[1], "r");

    fscanf(fp, "%d", &k);
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);

    graph = (int **)calloc(n, sizeof(int *));

    for(int i = 0; i < n; i++)
        graph[i] = (int *)calloc(n, sizeof(int));

    for(int i = 1; i <= m; i++)
    {
        int x, y;
        fscanf(fp, "%d %d", &x, &y);

        graph[x - 1][y - 1] = 1;
        graph[y - 1][x - 1] = 1;
    }

    reduction(graph, k, n);

    fclose(fp);
    for(int i = 0; i < n; i++)
        free( graph[i] );
    free(graph);
    
    return 0;
}