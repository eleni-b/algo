#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(a,b) ((a < b) ? a : b)


int cost[1501][1501];
int reaction[1501][501];


int heat(int k, int N)
{
    int i, j, l;
    int min_ = 1000;
    int min_j;


    reaction[1][1] = min_;
    
    
    for (l = 2; l <= k; l++){
        min_j = 0;
            for (i = 1; i <= N; i++)  {
                min_ = 1000;
                for (j = 1; j < i-1; j++) {
                    min_ = min(min_,reaction[j][l-1]+cost[j+1][i]);
                    if (min_ == reaction[j][l-1]+cost[j+1][i])
                        min_j = j;
                    
                }
           //     printf("min_j is %d\n",min_j);
                reaction[i][l] = min_;



          //      printf("React[%d chemicals][%d tubes] = %d\n",i,l,reaction[i][l]);
            }
    }
    
    for (j = min_j; j < i; j++)
        reaction[N][k] += cost[N][j];
    
    
    return reaction[N][k];
}


int main(int argc, char **argv)
{
    int i, j, N, k, l, m;
    scanf("%d %d", &N, &k);
    
    int min_;
    
    int total = 0, all_ones = 1, count = 1;
    
    
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N-i; j++) {
            scanf("%d",&cost[i][j+i]);
            cost[j+i][i] = cost[i][j+i];
            if (cost[j+i][i] != 1)
                all_ones = 0;
        }
        
    //  total += cost[i][i+1];
    //  reaction[i+1][1] = total;
    //  printf("React[%d chemicals][1 tubes] = %d\n",i,reaction[i][1]);

    }
    

    
    for (i = 2; i <= N; i++){
        if (i > 2)
            reaction[i][1] = reaction[i-1][1];
        else
            reaction[i][1] = cost[1][2];
        
        for (j = 1; j <= i-1; j++) {
            reaction[i][1] += cost[i][j];
        }
        
    //    printf("reaction[%d chems] [1 tube] = %d\n",i,reaction[i][1]);
 
    }
/*
    

    int top;
    
    if (N > 3) {
        for (l = 3; l <= N; l++) {
            min_ = 10000;
            for (i = 1; i < N-l; i++) {
                total = 0;
                if (i+l-1 > N-1)
                    top = N-1;
                else
                    top = i+l-1;
                
                for (j = 1; j < top; j++) {
                    total += cost[i][j+i];
                    count = 1;
                    m = i;
                    while (count < l) {
                        m++;
                        total += cost[m][j+i];
                        count++;
                
                    }
                }
                total += cost[i][l-1+i];
                printf("i is %d, j is %d and total is %d\n\n",i,j,total);
                min_ = min(min_,total);
            }
            reaction[l][1] = min_;
            printf("reaction[%d chems] [1 tube] = %d\n",l,min_);
        }
    }
 */

    if (all_ones) {
        if (N%k == 0)
            printf("%d\n",N);
        else
            printf("%d\n",N-1);
    }
    else
        printf("%d\n",heat(k, N));
    
    return 0;
    
    
    
}