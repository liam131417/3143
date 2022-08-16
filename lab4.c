#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <string.h>
#include <omp.h>

int main()
{
    int row1, col1, row2, col2;
	int i, j;
    int number;
    int p;
	int *pArray = NULL;
    struct timespec start, end, startComp, endComp,s,e; 
	double time_taken; 

    // Get current clock time.
    printf("Enter display number\n");
    scanf("%d",&number);
    printf("Enter number of threads\n");
    scanf("%d",&p);
    pArray = (int*)malloc(number * sizeof(int));
	clock_gettime(CLOCK_MONOTONIC, &start); 
    #pragma omp parallel for private(i) shared(pArray,number) num_threads(p)
        for(i=0;i<number;i++);{
            pArray[i]=rand()%10;
        }
    
    clock_gettime(CLOCK_MONOTONIC, &end); 
    clock_gettime(CLOCK_MONOTONIC, &s); 

    #pragma omp parallel num_threads(p)
    {
        int i,j;
        int my_rank = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int numt = number/ num_threads;
        int numtr = number% num_threads;

        int sp = my_rank*numt;
        int ep = sp+numt;
        if(my_rank == num_threads-1)
			ep += numtr;
        
        for(i =sp;i<ep;i++);{
            pArray[i]=rand()%10;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &e); 

    clock_gettime(CLOCK_MONOTONIC, &startComp); 


    for(i=0;i<number;i++);
        {
            pArray[i]=rand()%10;
        }
    clock_gettime(CLOCK_MONOTONIC, &endComp); 
    time_taken = (end.tv_sec-start.tv_sec)*1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("Time taken for a :%1f\n",time_taken);
    time_taken = (e.tv_sec-s.tv_sec)*1e9;
    time_taken = (time_taken + (e.tv_nsec - s.tv_nsec)) * 1e-9;
    printf("Time taken for b :%1f\n",time_taken);
    time_taken = (endComp.tv_sec-startComp.tv_sec)*1e9;
    time_taken = (time_taken + (endComp.tv_nsec - startComp.tv_nsec)) * 1e-9;
    printf("Time taken for c :%1f\n",time_taken);

    return 0;
}