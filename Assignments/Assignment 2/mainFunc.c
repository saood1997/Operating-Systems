#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include "pcbInitialize.c"

#define MAX 5

double noOfTimes[MAX];	
int turn = 0;
FILE *fplog;
void SwitchThread(int tid){
    int i;
    for(i = (tid + 1) % MAX; noOfTimes[i] == 0; i = (i + 1) % MAX)
        if(i == tid)
            return;
    turn = i;
}
void * thread_execution(void * pid){
	int i = (int)pid;
	int result;
	char line[BUFSIZ];
	int j,cnt2=0;

	FILE *fptr=fopen(p_queue[i].p_name,"r");
	
	while(noOfTimes[i] != 0){
        while(turn != i); 
        if(noOfTimes[i] > time_slice)
        {
        	cnt2=time_slice;		
			while(cnt2--)
			{
				fprintf(fplog, "\nProcess name: %s\n", p_queue[i].p_name); 
				fgets(line,sizeof(line),fptr);
	        		p_queue[i].insNo++;
			}        	
        		
	        noOfTimes[i]-=time_slice;
        }
        else if(noOfTimes[i] > 0 && noOfTimes[i] <= time_slice)
        {
        	while(p_queue[i].insNo!=p_queue[i].cpu_burst_time)
        	{
				fprintf(fplog, "\nProcess name: %s\n", p_queue[i].p_name);
				fgets(line,sizeof(line),fptr);
        		p_queue[i].insNo++; 
        	}
	        noOfTimes[i] = 0;
        }
        fprintf(fplog, "\n----------\n");
        SwitchThread(i);
    }
    pthread_exit(0);
}

int mainFunc(int ch){
	pcbInitialize(ch);
	if(ch==1)
	{
		fplog=fopen("logs_rr_with_thread","a");
		pthread_t threads[MAX];
	    	int i, status;
	    for(i=0; i<MAX; i++){
	        noOfTimes[i] = p_queue[i].cpu_burst_time;
	    }
	    for(i=0; i<MAX; i++)
	    {
	        status=pthread_create(&threads[i], NULL, thread_execution, (void *)i); 
	        if(status!= 0)
	        {
	            printf("While creating thread %d, pthread_create returned error code %d\n", i, status);
	            exit(-1);
	        }       
	    }
	    for(i=0;i<MAX;i++)
	    	pthread_join(threads[i], 0);
	    fprintf(fplog, "\n<--- END of Log file --->");
	    fclose(fplog);

	    printf("\nLog file 'logs_rr_with_thread' generated!\n");
	}
	else
	{
		FILE *fplog=fopen("logs_rr_without_thread","a");
		int i, j, result;
		char line[BUFSIZ];
		int checkProcessCompleted[MAX];
		int counter; 
		for(i=0;i<MAX;i++)
			checkProcessCompleted[i]=0;

		i=0, j=0;

		int lineNo;
		while(1)
		{
			time_slice=2; 
			if(counter==MAX)
				break;
			else if(i==MAX)
				i=0;
			else
			{
				if(checkProcessCompleted[i]==1)
				{
					i++;
					continue;
				}
				FILE *fptr=fopen(p_queue[i].p_name,"r");
				lineNo=1;
				while(lineNo<=p_queue[i].insNo)
				{
					fgets(line,sizeof(line),fptr);
					lineNo++;
				}
				for(j=0;j<time_slice && j<(p_queue[i].cpu_burst_time);j++)
				{
					fgets(line, sizeof(line), fptr);
					p_queue[i].insNo++;
					if(strlen(line)<10)
						continue;
					fprintf(fplog, "\nProcess name: %s\n", p_queue[i].p_name);
					decodeExec(line, fplog);
					if(p_queue[i].insNo==p_queue[i].cpu_burst_time)
					{
						checkProcessCompleted[i]=1;
						counter++;
					}
				}
				i++;
				fclose(fptr);
				fprintf(fplog, "\n----------\n");
			}
		}
		fprintf(fplog, "\n<--- END of Log file --->");
		fclose(fplog);

		printf("\nLog file 'logs_rr_without_thread' generated!\n");
	}
	
    return 0;
}
