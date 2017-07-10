#include <stdio.h>
#include <stdlib.h>


int partition(long long A[], long long B[], long long left, long long right) {

	long long temp;
	long long pivot = A[left];
	long long i = left - 1;
	long long j = right + 1;
	while (1) {
		while (A[++i] < pivot);
		while (A[--j] > pivot);
		
		if (i<j) {
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		  
			temp = B[i];
			B[i] = B[j];
			B[j] = temp;
		}
		else {
			return j;
		}
	}
}



void quicksort(long long A[], long long B[], long long left, long long right) {

	if (left >= right)
		return;

	long long pivot = left + (rand() % (right - left));

	long long temp = A[left];
	A[left] = A[pivot];
	A[pivot] = temp;

	temp = B[left];
	B[left] = B[pivot];
	B[pivot] = temp;

	long long q = partition(A, B, left, right);
	quicksort(A, B, left, q);
	quicksort(A, B, q+1, right);
}	




unsigned long long litres(long long s[], long long f[], int limit) {

	unsigned long long sum = 0;
	long long i = 1;
	while ( (s[i] <= limit) && (i <= s[0]) ) {
		if (f[i] < limit)
			sum = sum + (f[i] - s[i] + 1);
		else 
			sum = sum + (limit - s[i] + 1);
		i++;
	}
	return sum;
}


int main() {

	long long N, K, i;
    
    scanf("%lld %lld\n", &N, &K);

	long long * s = malloc((N+1)*sizeof(long long));
	long long * f = malloc((N+1)*sizeof(long long));


	s[0] = N;
	f[0] = N;
	for (i = 1; i <= N; i++) {
		scanf("%lld %lld\n", &s[i], &f[i]);
	}


	quicksort(s, f, 1, N);
	
	long long max_finish = 0;
	for (i = 1; i <= N; i++) {
		if (f[i] > max_finish)
			max_finish = f[i];
	}


	long long up = max_finish;
	long long low = 0;
	long long mid;

	unsigned long long filled;
	long long result = up;
	while (low <= up) {
		mid = (up + low) / 2;
		filled = litres(s, f, mid);
		if (filled > K) {
			result = mid; 
			up = mid - 1;
		}
		else if (filled < K)
			low = mid + 1;
		else {
			printf("%lld\n", mid);
			free(s);
			free(f);
			return (0);
		}
	}

	printf("%lld\n", result);

	free(s);
	free(f);
	return (0);
}










