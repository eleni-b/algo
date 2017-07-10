#include <stdio.h>
#include <stdlib.h>

int graph[1004][1004];
long heapP[1004][1004];

struct node_s {
    int x;
    int y;
    short int move;
    long heap_position;
    long label;
};
typedef struct node_s node;



node * A[1000004];
long hs;

// read long 
#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0L, bsize = 0L;

int readLong()
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


// Binary Heap -- Down in heap
void combine(long i) {
    
    // children left and right in heap
    long left = 2*i;
    long right = 2*i + 1;
    
    // node current
    long mp = i;
    
    // if left in heap and is greater than parent
    if ((left <= hs) && A[left]->label < A[mp]->label){
        mp = left;
    }
    if ((right <= hs) && (A[right]->label < A[mp]->label)) {
        mp = right;
    }
    if (mp != i) {
        node * temp;
        temp = A[i];
        A[i] = A[mp];
        A[i]->heap_position = i;
        heapP[A[i]->x][A[i]->y] = A[i]->heap_position;
        A[mp] = temp;
        A[mp]->heap_position = mp;
        heapP[A[mp]->x][A[mp]->y] = A[mp]->heap_position;
        combine(mp);
    }
}

int isEmpty() {
    return (hs == 0);
}

node * max() {
    if (isEmpty()) return NULL;
    return A[1];
}

// get and delete max
node * deleteMin() {
    if (isEmpty()) return NULL;
    node *max;
    max = A[1];
    
    A[1] = A[hs--];
    A[1]->heap_position = 1;

    combine(1);
    max->heap_position = -1;
    int x = max->x;
    int y = max->y;
    heapP[x][y] = -1;
    return max;
}

void insert_heap(node *k) {
    A[++hs] = k;
    A[hs]->heap_position = hs;
    long i = hs;
    long parent = i/2;
    while ((i>1) && (A[parent]->label > A[i]->label)) {
        node * temp;
        temp = A[i];
        A[i] = A[parent];
        A[i]->heap_position = i;
        heapP[A[i]->x][A[i]->y] = A[i]->heap_position;
        A[parent] = temp;
        A[parent]->heap_position = parent;
        heapP[A[parent]->x][A[parent]->y] = A[parent]->heap_position;
        i = parent;
        parent = i/2;
    }
}

void change_key(long hp, long key) {
    A[hp]->label = key;
    long i = hp;
    long parent = i/2;
    while ((i>1) && (A[parent]->label > A[i]->label)) {
        node * temp;
        temp = A[i];
        A[i] = A[parent];
        A[i]->heap_position = i;
        heapP[A[i]->x][A[i]->y] = A[i]->heap_position;
        A[parent] = temp;
        A[parent]->heap_position = parent;
        heapP[A[parent]->x][A[parent]->y] = A[parent]->heap_position;
        i = parent;
        parent = i/2;
    }
}

int main() {
    int i,j;
    
    int tx,ty;
    int flag = 1;
    int L,W;
    
    L = readLong();
    W = readLong();
    
    
    hs = 0;
    for (i=1;i<=L;i++) {
        for (j=1;j<=W;j++) {
            heapP[i][j] = -2;
            graph[i][j] = readLong();
            if (graph[i][j] == 0) {
                if (flag) {
                    node * current;
                    current = malloc(sizeof(*current));
                    current->x = i;
                    current->y = j;
                    current->label = -1;
                    current->heap_position = -2;
                    current->move = -1;
                    flag = 0;
                    current->label = 0;
                    insert_heap(current);
                    heapP[i][j]=current->heap_position;
                }
                else {
                    tx = i;
                    ty = j;
                }
            }
        }
    }
    
    while (hs>0) {
        node *current;
        current = deleteMin();
        if (current->x == tx && current->y == ty) {
            printf("%ld\n", current->label);
            return 0;
        }
        
        if (current->move != 0) {
            j = current->y;
            for (i=current->x+1;i<=L;i++) {
                if (graph[i][j] == 4000) break;
                node *new;
                if (heapP[i][j] == -2) {
                    new = malloc(sizeof(*new));
                    new->x = i;
                    new->y = j;
                    new->move = 0;
                    new->heap_position = hs+1;
                    new->label = current->label + graph[i][j];
                    insert_heap(new);
                }
                else if (heapP[i][j] != -1){
                    new  = A[heapP[i][j]];
                    if (new->label > ((current->label) + graph[i][j])) {
                        change_key(new->heap_position,  current->label + graph[i][j]);
                        new->move = 0;
                    }
                }
            }
            j = current->y;
            for (i=current->x-1;i>=1;i--) {
                if (graph[i][j] == 4000) break;
                node *new;
                if (heapP[i][j] == -2) {
                    new = malloc(sizeof(*new));
                    new->x = i;
                    new->y = j;
                    new->move = 0;
                    new->heap_position = hs+1;
                    new->label = current->label + graph[i][j];
                    insert_heap(new);
                }
                else if (heapP[i][j] != -1){
                    new = A[heapP[i][j]];
                    if (new->label > ((current->label) + graph[i][j])) {
                        change_key(new->heap_position,  current->label + graph[i][j]);
                        new->move = 0;
                    }
                }
            }
        }
        if (current->move != 1) {
            i = current->x;
            for (j=current->y+1;j<=W;j++) {
                if (graph[i][j] == 4000) break;
                node *new;
                if (heapP[i][j] == -2) {
                    new = malloc(sizeof(*new));
                    new->x = i;
                    new->y = j;
                    new->move = 1;
                    new->heap_position = hs+1;
                    new->label = current->label + graph[i][j];
                    insert_heap(new);
                }
                else if (heapP[i][j] != -1){
                    new = A[heapP[i][j]];
                    if (new->label > ((current->label) + graph[i][j])) {
                        change_key(new->heap_position,  current->label + graph[i][j]);
                        new->move = 1;
                    }
                }
            }
            i = current->x;
            for (j=current->y-1;j>=1;j--) {
                if (graph[i][j] == 4000) break;
                node * new;
                if (heapP[i][j] == -2) {
                    new = malloc(sizeof(*new));
                    new->x = i;
                    new->y = j;
                    new->move = 1;
                    new->heap_position = hs+1;
                    new->label = current->label + graph[i][j];
                    insert_heap(new);
                }
                else if (heapP[i][j] != -1){
                    new = A[heapP[i][j]];
                    if (new->label > ((current->label) + graph[i][j])) {
                        change_key(new->heap_position,  current->label + graph[i][j]);
                        new->move = 1;
                    }
                }
            }
        }
    }
    
    
    return 0;
    
}

