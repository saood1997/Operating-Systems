#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSZ 27

int main()
{
	int shmid;
	void *memory = NULL; 
	key_t key;
	char *shm, *s;
	
	key = 5678;
	
	//initilization of the sheard memory
	shmid = shmget(key,SHMSZ,IPC_CREAT | 0666);

	if(shmid<0){
		printf("\n creation has gone as a failure,sorry");
	}

	printf("\n we are getting the sheard memory created%d",shmid);
	printf("\n");
	
	// attached to sheard memory
	shm = shmat(shmid,NULL,0);           //shmaddr,suitable address to attach the segment.
	if(shm == NULL ){
		printf("\n attachment failure,sorry");
	}

	for (s = shm ; *s != NULL; s++){
		putchar(*s);
	}
	putchar('\n');

	//detached from the sherad memory;
	shmdt(shm);
	
	// destroy the shared memory
	shmctl(shmid,IPC_RMID,NULL);
	exit(0);
}
