#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 
  
int main() 
{ 
    key_t key; 
    int number; 
   
    key = ftok("progfile", 65); 
  
    number = msgget(key, 0666 | IPC_CREAT); 
   
    msgrcv(number, &message, sizeof(message), 1, 0); 
   
    printf("Data Received is : %s \n",  
                    message.mesg_text);
    msgctl(number, IPC_RMID, NULL); 
  
    return 0;
}
