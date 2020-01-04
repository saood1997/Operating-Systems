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
    message.mesg_type = 1; 
  
    printf("Write Data : "); 
    gets(message.mesg_text); 
  
    msgsnd(number, &message, sizeof(message), 0); 
    printf("Data send is : %s \n", message.mesg_text); 
  
 }
