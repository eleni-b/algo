#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int move[26][2];
int exists[26][400];
int curr_j[26];
char grid[400][400];



int main() {


    int N, M, K, i, j, first, second, new_i, new_j;

    for (i = 0; i < 26; i++)
        curr_j[i] = 0;
    
    
    
    
    // curr_j is the position of the last added element under a certain letter
    
    i = 0;

    int index;
    char u;

    scanf("%d %d\n", &N, &M);
    
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%c", &u);
            grid[i][j] = u;
            index = u - 'a';
            exists[index][curr_j[index]] = i;
            exists[index][curr_j[index]+1] = j;
            curr_j[index] = curr_j[index] + 2;

            
        }
        if ( i != N-1)
            scanf("\n");
    }
    
    
    for (i = 0; i < 26; i++) {
        scanf("%d %d", &move[i][0], &move[i][1]);
    }
    
    
    scanf("%d\n", &K);
    
    
    int flag;
    int v;
    
    int m;
    
    int newest_i, newest_j, num;
    
    char lett;

    char input_str[50000];

    
    for (i = 0; i < K; i++) {
        
        v = 1;
        
        second = -1;
        
        fgets(input_str,sizeof(input_str),stdin);
        
        flag = 0;
        
        
        first =  input_str[0] - 'a';
        
        
        if ( (exists[first][0] == 0) && (exists[first][1] == 0) && (grid[0][0] != input_str[0]) ) {
            printf("no\n");
            continue;
        }
        
        
        while ( input_str[v] != '\n' ) {
            
            second = input_str[v] - 'a';
            
        
            for (j = 0; j < curr_j[first]; j = j+2 ) {
                new_i = exists[first][j] + move[first][0];
                new_j = exists[first][j+1] + move[first][1];
                
                if ( (new_i < 0) || (new_i >= N) || (new_j < 0) || (new_j >= M) ) {
                    new_i = exists[first][j];
                    new_j = exists[first][j+1];
                }
   
                lett = grid[new_i][new_j];
                num = lett - 'a';
                
                
                newest_i = new_i + move[num][0];
                newest_j = new_j + move[num][1];
                    
                    
                if ( (newest_i < 0) || (newest_i >= N) || (newest_j < 0) || (newest_j >= M) ) {
                        newest_i = exists[num][j];
                        newest_j = exists[num][j+1];
                    }
                    
                if (grid[newest_i][newest_j] == input_str[v]) {
                        first = second;
                        flag = 1;
                        v++;
                        break;
                }
                
                if (grid[new_i][new_j] != input_str[v]) {
                    flag = 0;
                    continue;
                }
                else {
                    first = second;
                    flag = 1;
                    v++;
                    break;
                }
            }
            
            if ( (flag == 0) && (j == curr_j[first]))
                break;
        }

        if ( second == -1) {
            if ( (exists[first][0] != 0) || (exists[first][1] != 0)|| (grid[0][0] == input_str[0])) {
                printf("yes\n");
                continue;
            }
            else {
                printf("no\n");
                continue;
            }
        }

        
        if (flag == 0)
            printf("no\n");
        else
            printf("yes\n");
        
    }

  
    return 0;

}

    
    
