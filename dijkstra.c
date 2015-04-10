#include <limits.h>

void Dijkstra (int v[][], int x, int a)
{
    int sptSet[x]; //Shortest path tree set

    int lenght[x][2];

    lenght[a][0] = 0;
    lenght [a][1] = 0;

    int i = 0;

    while(i < x)
    {
        if(i == a)
            continue;

        lenght[0][i] = UINT_MAX;

        i++;
    }

    int j = 0, k = 0;

    for( i = 0; i < x; i++)
    {
        while(k < x)
        {
            while(!v[a][j] && j < x)
            {
                j++;
                k++;
            }

            if(lenght[0][a] + v[a][j] < lenght[0][j])
                lenght[0][j]= lenght[0][a] + v[a][j];

                
        }
    }


}
