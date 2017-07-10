#include <stdio.h>
#include <stdlib.h>

typedef struct move_ {
    long long coins;
    int x;
    int y;
} move;

int M, N, K;
int c[1000][1000];
move memF[1000][1000];
move memS[1000][1000];

move first (int i, int j);
move second (int i, int j);

move first(int i, int j) {
    
    move best;
    
    if (memF[i][j].coins >= 0)
        return memF[i][j];
    
    if ((i == N-1) && (j == M-1)) {
        best.x = N-1;
        best.y = M-1;
        best.coins = 0;
        return best;
    }
    
    int p,q;
    long long check, max = -1;
    int np, nq;
    
    for (p = 0; p <= K; p++) {
        for (q = 0 ; q <= K; q++) {
            if ((p+q > 0) && (i+p < N) && (j+q < M)) {
                check = c[i+p][j+q] + second(i+p, j+q).coins;
                if (check > max) {
                    np = i+p;
                    nq = j+q;
                    max = check;
                }
            }
        }
    }
    best.coins = max;
    best.x = np;
    best.y = nq;
    
    memF[i][j] = best;
    return best;
}



move second(int i, int j) {
    
    move best;
    best.x = N-1;
    best.y = M-1;
    best.coins = 0;
    
    if (memS[i][j].coins >= 0)
        return memS[i][j];
    
    if ((i == N-1) && (j == M-1))
        return best;
    
    best = first(i,j);
    
    memS[i][j] = first(best.x, best.y);
    return  memS[i][j];
}


int main (int argc, char **argv) {
    
    scanf("%d %d %d", &N, &M, &K);
    int i, j;
    
    
    for (i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            memF[i][j].coins = -1;
            memS[i][j].coins = -1;
            scanf("%d", &c[i][j]);
        }
    }
    
    c[0][0] = 0;
    printf("%lld %lld\n", first(0,0).coins, second(0,0).coins);
    
    return 0;
}


