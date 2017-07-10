#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int row;
    int col;
} Data;

int max (int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}

int min (int a, int b) {
    if (a <= b)
        return a;
    else
        return b;
}

int compare (const void *a, const void *b){
    Data *data_a = (Data*)a;
    Data *data_b = (Data*)b;
    
    if (data_a->col < data_b->col)
        return -1;
    else if (data_a->col > data_b->col)
        return 1;
    else if (data_a->col == data_b->col) {
        if (data_a->row < data_b->row)
            return -1;
        else
            return 1;
    }
    else return 0;
}


int main(int argc, char *argv[]) {
    
    int N, K, a, total, count, i, j, left_upper, left_lower, right_upper, right_lower, reversed, bit, flag;
    int left_upper_col, right_upper_col, left_lower_col, right_lower_col, left_shift, right_shift, right_j, left_j;
    int k = 0;
    
    scanf("%d",&N);
    scanf("%d",&K);
    
    Data * array = (Data *)malloc((N*N)*sizeof(Data));
    
    // We store pairs (row,column) of ones in the grid on array
    for (  i = 0; i < N; i++ ) {
        scanf("%d",&a);
        for (j = N-1; j >= 0; j--) {
            bit = (a & (1<<j)) >> j;
            if ( bit == 1 ) {
                array[k].row = i;
                array[k].col = N-j-1;
                k++;
            }
        }
    }
    
    
    qsort(array, k, sizeof(Data), compare);
    total = 0;
    
    
    
    for ( i = 0; i < k; i++) {
        printf("in i loop\n");


        
        count = 0;
        j = i;
        reversed = 0;
        
        left_shift = 1;
        right_shift = 1;
        
        left_upper = 0;
        right_upper = 0;
        
        left_lower = N-1;
        right_lower = N-1;
        
        left_lower_col = array[i].col;
        right_lower_col = array[i].col;
        
        left_upper_col = array[i].col;
        right_lower_col = array[i].col;
        
        
    
        left_j = array[i-1].col;
        right_j = array[i+1].col;
        
        if ( i-1 < 0 )
            left_j = array[0].col;
        
        if ( i+1 > k-1)
            right_j = array[k-1].col;
        
        j = i + right_shift;
        
        while (array[j].col == array[i].col ) {
            count++;
            j = i + right_shift;
            right_shift++;
            right_lower = array[j].row;
            right_lower_col = array[j].col;
        }
        
        j = i - left_shift;
        
        while (array[j].col == array[i].col) {
            count++;
            j = i - left_shift;
            left_shift++;
            left_upper = array[j].row;
            left_upper_col = array[j].col;
        }
        // fix left_j price
        
        total += right_lower - left_upper;   //needs fixing!!!!!
        
        if ( (array[i].row != 0) && (array[i].row != N-1) )
            total += 1;
        
        printf("and from here i gat %d   ^^\n",total);
        
        j = i;
        
        flag = 0;
    
        while (count < k) {
            
            if (j - left_shift < 0) {
                reversed = 1;
                j = i;
            }
            
            if ( (j + right_shift > k-1) && (count < k) ) {
                count = k;
                flag = 1;
            }
            
            
            
            if ((!reversed) && (j-left_shift >= 0)) {
                count++;
                j = i-left_shift;
                left_shift++;
                
                if (array[j].col != left_j) {
                    reversed = 1;
                }
            }
            else if ((reversed) && (j+right_shift <= k-1)) {
                count++;
                j = i+right_shift;
                right_shift++;
                
                if (array[j].col != right_j) {
                    reversed = 0;
                    flag = 1;
                }
            }
            

 
            
            // TODO na ftiaxo to reversed !!
            
            
            
            if (flag) {
                //count --;
                
                printf("o v e r   h e r e !  Calculating total... . . . .\n");
              
                total += ( min(left_lower,right_lower) - max(left_upper,right_upper) - 1) *  (max(left_lower_col,left_upper_col) - min(right_lower_col,right_upper_col) + 1);
                total += ( array[i].row - max(left_upper,right_upper) - 1) * ( min(left_lower,right_lower) - array[i].row) * (max(left_lower_col,left_upper_col) - min(right_lower_col,right_upper_col) + 1);
                
                if (left_upper < right_upper)
                    total += (right_upper - left_upper) * (right_lower) * (right_upper_col - array[i].col);
                else
                    total += (left_upper - right_upper) * (left_lower) * (array[i].col - left_upper_col);
                
                if (left_lower > right_lower)
                    total += (left_lower - right_lower) * (left_upper) * (array[i].col - left_lower_col);
                else
                    total += (right_lower - left_lower) * (right_upper) * (right_upper_col - array[i].col);
                
                printf("got a price of total equal to %d    ^(0_0)^ \n", total);
                
                flag = 0;
            }
               
                
                // TODO : fix 
                
                
                
     /*
                if (right_lower > left_lower) {    //to sosto!!
                    
                    total += (left_lower - array[i].row);
                    total += (left_lower - array[i].row) * 2 * max(array[i].col - left_lower_col, right_lower_col - array[i].col);
                    total += (right_lower - left_lower);
                }
                else {
                    total += (right_lower - array[i].row);
                    total += (left_lower - array[i].row) * 2 * max(array[i].col - left_lower_col, right_lower_col - array[i].col)
                    total += (left_lower - right_lower);
                }
                
                if (right_upper < left_upper) {
                    total += (array[i].row - left_upper);
                    total += (array[i].row - left_upper) * 2 * max(array[i].col - left_upper_col, right_upper_col - array[i].col);
                    total += (left_upper - right_upper);
                }
                else {
                    total += (array[i].row - right_upper);
                    total += (array[i].row - right_upper) * 2 * max(array[i].col - left_upper_col, right_upper_col - array[i].col);
                    total += (right_upper - left_upper);
                }
                
                continue;
      
      */
/*
               if (right_lower > left_lower) {
                    total += ( (left_lower - array[i].row + 1)*2 - 1) + (array[i].col - left_lower_col) - 1;
                    total += ( right_lower - array[i].row + 1)*(right_lower_col - left_lower_col);
                }
                else if (left_lower > right_lower) {
                    total += ( (right_lower - array[i].row + 1)*2 - 1)*(right_lower_col - array[i].col) - 1;
                    total +=  (array[i].row - left_lower + 1)*(right_lower_col - left_lower_col);
                }
                else if (left_lower == right_lower) {
                    total += (left_lower - array[i].row + 1)*(array[i].col - left_lower_col + 1) - 1;
                    total += (right_lower - array[i].row + 1)*(right_lower_col - left_lower_col) - 1;
                    
                }

 
 */
        
            
            if ( (!reversed) && (array[j].row >= left_upper) && (array[j].row < array[i].row) ) {
                left_upper = array[j].row;
                left_upper_col = array[j].col;
            }
            else if ( (!reversed) && (array[j].row <= left_lower) && (array[j].row > array[i].row) ) {
                left_lower = array[j].row;
                left_lower_col = array[j].col;
            }
            if ( (reversed) && (array[j].row >= right_upper) && (array[j].row < array[i].row) ) {
                right_upper = array[j].row;
                right_upper_col = array[j].col;
            }
            else if ( (reversed) && (array[j].row <= right_lower) && (array[j].row > array[i].row) ) {
                right_lower = array[j].row;
                right_lower_col = array[j].col;
            }
            else if (array[i].row == array[j].row)
                reversed = (!reversed);
        
        
            if (!reversed)
                left_j = array[j].col;
            else
                right_j = array[j].col;

            
            
            
        }
        
        
        if ((left_upper_col != 0) || (left_lower_col != 0)) {
            if (left_upper_col > left_lower_col)
                total += (left_lower - left_upper+1)*(left_lower_col);
            else
                total += (left_lower - left_upper+1)*(left_upper_col);
            printf("did i get over here??? %d\n",total );
        }
        
        if ((right_upper_col != N-1) || (right_lower_col != N-1)) {
            if (right_upper_col > right_lower_col)
                total += (right_lower - right_upper+1)*(N-1-right_upper_col);
            else
                total += (right_lower - right_upper+1)*(N-1-right_upper_col);
        }
            
        
    
        printf("current total equals %d\n", total);
    }
    

    printf("%d\n",total);
    
    free(array);

    
    return (0);
}





