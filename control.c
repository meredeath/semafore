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

union semun {
  int val;              
  struct semid_ds *buf;   
  unsigned short *array;         
  struct seminfo *__buf; 
};

int main(int argc, char *argv[]){

  int semid;
  int shmid;
  int fd;
  
  if (strcmp(argv[1],"-c") == 0){
    semid = semget(KEY,1,IPC_CREAT|IPC_EXCL|0644); //create one new semaphore
    shmid = shmget(KEY,256,IPC_CREAT|IPC_EXCL|0644); //create one new segment of shared memory
    fd = open("maple_story.txt",O_TRUNC | O_CREAT, 0644); //open story file
    if (fd == -1){
      printf("Could not create the story :(\n");
    }
    union semun data;
    data.val = 1;
    semctl(semid,0,SETVAL,data); //set semaphore value to 0
    close(fd); //close file
    printf("File, shared memory, and semaphore successfully created\n");
  }

  if (strcmp(argv[1],"-r") == 0){
    fd = open("maple_story.txt", O_RDONLY, 0644); //open file with read permissions
    
    semid = semget(KEY, 1, 0); //get key of existing semaphore
    shmid = shmget(KEY, 256, 0); //get key of existing shared memory
    shmctl(shmid,IPC_RMID,NULL); //remove shared memory

    //down the semaphore
    struct sembuf down;
    down.sem_op = -1;
    down.sem_num = 0;
    down.sem_flg = SEM_UNDO;
    semop(semid, &down, 1);
    semctl(semid, 0, IPC_RMID); //remove the semaphore
    
    char cur_story[9001]; //declare buffer
    read(fd,cur_story,9001); //read story into buffer
    printf("%s",cur_story); //print story
    close(fd); //close file

    remove("maple_story.txt"); //remove file
    printf("Successfully removed semaphore, shared memory, and file\n");
  }
  
  if (strcmp(argv[1],"-v") == 0){
    fd = open("maple_story.txt", O_RDONLY, 0644); //opens file

    //reading story into a buffer and printing it
    char cur_story[9001];
    read(fd,cur_story,9001);
    printf("%s",cur_story);
    close(fd);
  }
  
}
    
    
    
    
    
  
