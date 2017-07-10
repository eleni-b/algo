#include <stdio.h>
#include <stdlib.h>

/* read long */
#define BSIZE 1<<15

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong()
{
    long d = 0L, x = 0L;
    char c;
    
    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
        else if (d == 1) return x;
    }
    return -1;
}


long readInt()
{
    int d = 0L, x = 0L;
    char c;
    
    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
        else if (d == 1) return x;
    }
    return -1;
}





/* struct used only for sorting after reading input */
struct edge2_s {
    long n1;
    long n2;
    short int cost;
};
typedef struct edge2_s edge2;


long partition(edge2 A[], long left, long right) {
    /* QUICKSORTS RANDOM PARTITION */
    /* All left < A[pivot] < A[right] */
    
    edge2 temp;
    long pivot = A[left].cost;
    long i = left - 1;
    long j = right + 1;
    while (1) {
        while (A[++i].cost < pivot);
        while (A[--j].cost > pivot);
        /* swap */
        if (i<j) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            
        }
        else {
            return j;
        }
    }
}


void quicksort(edge2 A[], long left, long right) {
    
    if (left >= right)
    /* Array sorted */
        return;
    
    /* chose random pivot */
    long pivot = left + (rand() % (right - left));
    
    /* swap with first */
    edge2 temp = A[left];
    A[left] = A[pivot];
    A[pivot] = temp;
    
    /* call partiton */
    long q = partition(A, left, right);
    quicksort(A, left, q);
    quicksort(A, q+1, right);
}




struct edge_s {
    long id;    //edge id, used for parallel edges
    long to;    //links to
    short int cost;  //with cost
    struct edge_s * next;
};
typedef struct edge_s edge;

edge* create_edge(long id, long to, long cost) {
    edge * new;
    new = malloc(sizeof(*new));
    new->id = id;                /* to not recheck edge in DFS */
    new->to = to;
    new->cost = cost;
    new->next = NULL;
    return new;
}

/* insert at start */
void insert_edge(edge **root, edge *new) {
    /* if empty */
    if (*root == NULL) {
        *root = new;
        (*root)->next = NULL;
    }
    /* if not append first */
    else {
        new->next = *root;
        *root = new;
    }
}



struct node_s {
    int visited;        /* visited for DFS  */
    long low;           /* find cycles */
    long parent;        /* parent */
    long previsit;
    edge * nb;          /* adjacency list */
};
typedef struct node_s node;

node* create_node() {
    node *new;
    new = malloc(sizeof(*new));
    new->previsit = 0;
    new->visited = 0;
    new->parent = 0;
    new->low = 100000000;
    new->nb = NULL;
    return new;
}


/* Before every DFS recreate nodes *
 * delete all neibs (not necessery *
 * and restart values              */
void recreate_node(node *new) {
    new->previsit = 0;
    new->visited = 0;
    new->parent = 0;
    new->low = 100000000;
    
    while (new->nb != NULL) {
        edge *temp;
        temp = new->nb;
        new->nb = new->nb->next;
        free(temp);
    }
}











/* the node matrix */
node ** nodes;

/* union find matrix */
long *A;

/* array with checked edges (1 is checked, 0 not) */
long *checked;

/* edge array for sorting */
edge2 *edges2;

/* other global variables */
long clock, red, green, yellow;







long find(long x) {
    if (x != A[x])
        A[x] = find(A[x]);
    return A[x];
}


void unionTree(long x, long y) {
    if (x == y) return;
    A[y] = x;
}






void explore (long s) {
    nodes[s]->visited = 1;
    nodes[s]->previsit = clock++;
    nodes[s]->low = clock;
    edge *e;
    
    /* for every edge */
    e = nodes[s]->nb;
    while (e!=NULL) {
        if (checked[e->id] == 1) {
            e = e->next;
            continue;
        }
        
        checked[e->id] = 1;
        long v = e->to;
        /* loop node is a red node */
        if (v == s)
            red++;
        
        /* visit if not visited */
        else if (nodes[v]->visited == 0) {
            nodes[v]->parent = s;
            explore(v);
            /* check if edge e is on circle */
            if (nodes[v]->low <= nodes[s]->previsit) {
                /* if yes it is yellow */
                yellow++;
                if (nodes[v]->low < nodes[s]->low) {
                    nodes[s]->low = nodes[v]->low;
                }
            }
            else green++;
        }
        /* backedges are always yellow */
        else {
            yellow++;
            if (nodes[v]->previsit < nodes[s]->low) {
                nodes[s]->low = nodes[v]->previsit;
            }
        }
        e = e->next;
    }
    clock++;
}


void multiDFS(long N) {
    clock = 1;
    long i;
    
    for (i=1; i<=N; i++)
        explore(i);
}



int main() {
    
    long N, M, i;
    N = readLong();
    nodes = malloc(sizeof(*nodes) * (N+2));
    A = malloc(sizeof(*A) * (N+2));
    
    M = readLong();
    edges2 = malloc(sizeof(*edges2) * (M+2));
    checked = malloc(sizeof(long) * (M+2));
    
    green = 0;
    yellow = 0;
    red = 0;
    
    /* create and sort edges */
    for (i=1; i<=M; i++) {
        edges2[i].n1 = readLong();
        edges2[i].n2 = readLong();
        edges2[i].cost = readInt();
        checked[i] = 0;
    }
    quicksort(edges2, 1, M);
    
    
    /* Create graph */
    for (i=1; i<=N; i++) {
        nodes[i] = create_node();
        A[i] = i;
    }
    
    
    long cost = edges2[1].cost;
    /* add the new edges */
    i = 1;
    while (i<=M) {
        long j;
        for (j=1; j<=N; j++) {
            recreate_node(nodes[j]);
        }
        
        long ii = i;
        while (cost == edges2[i].cost) {
            long n1 = find(edges2[i].n1);
            long n2 = find(edges2[i].n2);
            long cost = edges2[i].cost;
            edge *new;
            new = create_edge(i, n2, cost);
            insert_edge(&nodes[n1]->nb, new);
            new = create_edge(i, n1, cost);
            insert_edge(&nodes[n2]->nb, new);
            i++;
        }
        multiDFS(N);
        for(j=ii; j<i; j++)
            unionTree(find(edges2[j].n1), find(edges2[j].n2));
        cost = edges2[i].cost;
    }
    
    
    for (i=1; i<=N; i++) {
        while (nodes[i]->nb != NULL) {
            edge *temp;
            temp = nodes[i]->nb;
            nodes[i]->nb = nodes[i]->nb->next;
            free(temp);
        }
        free(nodes[i]);
    }
    free(nodes);
    free(A);
    free(edges2);
    free(checked);
    
    printf("%ld\n%ld\n%ld\n", green, red, yellow);
    return 0;
}                
