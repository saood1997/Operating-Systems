#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

struct pcb
{
    int p_id;
    double insNo;
    char p_name[50];
    double arrival_time;
    double cpu_burst_time;
    int priority;
};

int noOfFiles=0;
int time_slice=2;
struct pcb p_queue[10];   
void pcbInitialize(int ch)
{
    srand(time(0)); 
    time_t t=time(0);
    struct dirent *dp;
    char pname[10][50];
    char folder[]="processes/";

    DIR *fd;
    fd=opendir("processes");

    while((dp = readdir(fd)) != NULL) 
    {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;    

        char  folder[]="processes/";
        strcat(folder,dp->d_name);
        strcpy(pname[noOfFiles],folder);
        noOfFiles++; 
    }
    closedir(fd);

    FILE *f1, *fplog;
    double count=0;
    char c;
    int i;
    if(ch==1)
    {
        fplog=fopen("logs_rr_with_thread","w");
        fprintf(fplog, "Time slice = %d instructions\n\nReady Queue:\n\nFront -> ", time_slice);
    }
    else
    {
        fplog=fopen("logs_rr_without_thread","w");
        fprintf(fplog, "Time slice = %d instructions\n\nReady Queue:\n\nFront -> ", time_slice);
    }
    for(i=0;i<noOfFiles;i++)
    {
        count=0;

        if(i==noOfFiles-1)
            fprintf(fplog, "%s\n\n----------", pname[i]);
        else
            fprintf(fplog,"%s | ",pname[i]);
        p_queue[i].p_id=(i+1);
        p_queue[i].insNo=0;
        strcpy(p_queue[i].p_name,pname[i]);
        p_queue[i].arrival_time=difftime(time(0),t);
        p_queue[i].priority=rand()%10;
        f1=fopen(pname[i],"r");
        for (c = getc(f1); c != EOF; c = getc(f1))
        {
            if (c == '\n')
                count = count + 1;
        }
        p_queue[i].cpu_burst_time=count;

        fclose(f1);
    }
    fprintf(fplog, "\n");
    fclose(fplog);
}
