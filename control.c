#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


#include <errno.h>

//sys stuff
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define KEY 2401 //L is real

//For Señor DW: Anand did this on Mac, Meredith did this on ssh Ubuntu shell so this might be wonky
/*
union semun {
  int val;              
  struct semid_ds *buf;   
  unsigned short *array;         
  struct seminfo *__buf; 
}
*/
int main(char * arguments[]){
  printf("Hello there. \n Valid arguments include: \n
'-c': Make your story \n
'-r': Remove your story \n
'-v': View your story \n

What would you like to do?: ");

  int semid;
  int shmid;

  int fd;

  union semun data;
  data.val = 1;
  
  //-c
  
  if (strcmp(arguments[0],"-c") == 0){
    semid = semget(KEY,1,IPC_CREAT|IPC_EXCL|0644);
    shmid = shmget(KEY,256,IPC_CREAT|0644);
    fd = open("maple_story.txt",O_TRUNC | O_CREAT, 0644);
    if (fd == -1){
      printf("Could not create the story :(");
    }
    semctl(semid,0,SETVAL,data);
    close(fd);
  }

  if (strcmp(arguments[0],"-r") == 0){
    fd = open("maple_story.txt",O_TRUNC|O_CREAT,0644);
    
    semid = semget(KEY,1,IPC_CREAT|IPC_EXCL|0644);
    shmid = shmget(KEY,256,IPC_CREAT|0644);
    semctl(semid,0,IPC_RMID);
    shmctl(shmid,IPC_RMID,NULL);

    char * cur_story = malloc(9001);
    read(fd,cur_story,sizeof(cur_story));
    printf("%s",s);
    close(fd);

    remove("maple_story.txt");
  }
  if (*strcmp(arguments[0],"-v") == 0){
    fd = open("maple_story.txt",O_TRUNC|O_CREAT,0644);
    
    semid = semget(KEY,1,IPC_CREAT|IPC_EXCL|0644);
    shmid = shmget(KEY,256,IPC_CREAT|0644);
    semctl(semid,0,IPC_RMID);
    shmctl(shmid,IPC_RMID,NULL);

    char * cur_story = malloc(9001);
    read(fd,cur_story,sizeof(cur_story));
    printf("%s",s);
    close(fd);
  }
    
    
    
    
    
  
