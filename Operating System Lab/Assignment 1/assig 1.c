#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>

int main(){

	double total_time;
	clock_t start, end;
	start = clock();
	srand(time(NULL));
	int i;
	int count = 0;
	int STEPS = 100; // Number of Steps int i, count = 0;
	double x, y, z, pi;
	for (i = 0; i <= STEPS; i++){
		x = rand()/(double)RAND_MAX;
		y = rand()/(double)RAND_MAX;
		z = x*x + y*y;
		if (z <= 1){
			count++;
		}
	}
	pi = (double)count/STEPS*4;
	end = clock();
	total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken : %f", total_time);
	printf("N = %d\t", STEPS);
	printf("Pi = %.20f\n", pi);

}
