#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSZ 27

//stage1 : initilization of the sheard memory 
//stage 2 : attached to sheard memory
//stage 3 : detached from sheard memory


int main()
{
	char c;
	int shmid,val;
	key_t key;
	void *memory = NULL;
	char *shm,*s;

	key = 5678;

	//initilization of the sheard memory
	shmid = shmget(key,SHMSZ,IPC_CREAT | 0666);

	if(shmid<0){
		printf("\n creation has gone as a failure,sorry");
	}

	printf("\n we are getting the sheard memory created%d",shmid);
	printf("\n");
	
	// attached to sheard memory
	memory = shmat(shmid,NULL,0);

	s = (char *)memory; // pointer to sherad memory
	if(s == NULL ){
		printf("\n attachment failure,sorry");
	}

	for (c = 'a'; c <= 'z'; c++){
		*s++ = c;
		*s = NULL;
	}
	
	//detached from the sherad memory;
	val = shmdt(s);
	return 0;

}
