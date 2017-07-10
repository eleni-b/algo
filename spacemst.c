#include<stdio.h>
#include <stdlib.h>

#define MAX 10000

int sum = 0;
int *graph[MAX];


typedef struct teleport {
    int vertex;
    int cost;
} teleport_;


struct teleport *tel;


typedef struct edges{
    int v1;
    int v2;
    int fee;
} edges_;

struct edges *mst_edges;


int N, K, M;


int *parent;
int root(int p)
{
    while(p!=parent[p])
    {
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    return p;
}
int sameSet(int p,int q)
{
    return root(p)==root(q);
}
void myunion(int p, int q)
{
    int proot = root(p);
    int qroot = root(q);
    parent[qroot] = proot;
}

void findMinEdge(int *x, int *y)
{
    int i, j, min=MAX;
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(graph[i][j]>0 && (!sameSet(i,j)) && min>graph[i][j])
            {
                *x = i;
                *y = j;
                min = graph[i][j];
            }
        }
    }
}

int max_mst_index;

void kruskalMST()
{
    sum = 0;
    
    max_mst_index = 0;
    
    int i;
    int k = 0;
    parent = malloc(sizeof(*parent) * N);
                        
    for(i=0; i<N; i++)
        parent[i] = i;
    
    int u, v;
    for(i=0; i<N-1; i++)
    {
        findMinEdge(&u, &v);
        myunion(u,v);
        sum += graph[u][v];
        mst_edges[k].v1 = u;
        mst_edges[k].v2 = v;
        mst_edges[k].fee = graph[u][v];
        k++;
    }
    
    max_mst_index = k-1;
                        
    free(parent);

}


int tel_cmp (const void *x, const void *y) {
    const struct teleport *tel1 = x;
    const struct teleport *tel2 = y;
    
    if ( tel1->cost > tel2->cost ) return 1;
    if ( tel1->cost < tel2->cost ) return -1;
    
    return 0;
}





int main()
{
                        
                        
    
    scanf("%d %d %d",&N, &K, &M);
                        
    
    int i, j, ind_i, ind_j;
                        
                        for (i=0; i< N; i++)
                            graph[i] = (int *)malloc(N * sizeof(int));
                        
                        mst_edges = malloc(M * sizeof(struct edges));
    
                        tel = malloc(K  * sizeof(struct teleport));
    
    
    for (i = 0; i < K; i++) {
        scanf("%d %d",&tel[i].vertex, &tel[i].cost);
    }
    
    qsort(tel, K, sizeof(struct teleport), tel_cmp);
    
    
    int upper_tel = 0;
    
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            graph[i][j] = -1;
            if (i == j)
                graph[i][i] = 0;
        }
    }
    
    
    
    
    for (i = 0; i < M; i++) {
        scanf("%d %d", &ind_i, &ind_j);
        ind_i--;
        ind_j--;
        scanf("%d", &graph[ind_i][ind_j]);
        graph[ind_j][ind_i] = graph[ind_i][ind_j];
        
    }
    

    
    kruskalMST();
    
    

    
    
    

    
    int the_flag = 0, prev_sum = sum;
    
    i = 1;
    
    while (( !the_flag) && (i < K)){
        if ( (tel[0].cost + tel[i].cost) < mst_edges[max_mst_index].fee ) {
            upper_tel = i;
            i++;
        }
        else
            the_flag = 1;
    }
    
    the_flag = 0;
    
    for (i = 0; i < upper_tel; i++) {
        for (j = i+1; j <= upper_tel; j++) {
            if ( (tel[i].cost + tel[j].cost) < mst_edges[max_mst_index].fee ) {
                if ( (graph[tel[i].vertex -1][tel[j].vertex -1] > (tel[i].cost + tel[j].cost)) || (graph[tel[i].vertex -1][tel[j].vertex -1] == -1) ) {
                    graph[tel[i].vertex -1][tel[j].vertex -1] = (tel[i].cost + tel[j].cost);
                }
            
            
                kruskalMST();
            
                if (sum > prev_sum) {
                    the_flag = 1;
                    sum = prev_sum;
                    break;
                }
            
                prev_sum = sum;
            }
            else
                break;

            if (the_flag)
                break;

            
        }
        
        if (the_flag)
            break;
    }

    printf("%d\n",sum);

    
    free(*graph);
    free(tel);
    free(mst_edges);
    
    return 0;
} 

