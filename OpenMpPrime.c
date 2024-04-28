// 47. Write a program using OpenMP library to parallelize the for loop in sequential program of finding prime numbers in given range

#include <stdio.h>
#include <omp.h>

int is_prime(int n) {
	if (n <= 1) return 0;
	for (int i = 2; i * i <= n; i++) {
    	if (n % i == 0) return 0;
	}
	return 1;
}

int main() {
	int lower = 2, upper = 100; // Define the range
	printf("Prime numbers between %d and %d are:\n", lower, upper);

	#pragma omp parallel for
	for (int num = lower; num <= upper; num++) {
    	if (is_prime(num)) {
        	printf("%d\n", num);
    	}
	}

	return 0;
}
// gcc -fopenmp -o prime prime.c
