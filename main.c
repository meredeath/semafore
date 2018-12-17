#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define KEY 2401

int main(){
  int shmid = shmget(KEY, 100, 0);
  int semid = semget(KEY, 1, 0);
  int fd = open("maple_story.txt", O_WRONLY | O_APPEND);

  //decrement semaphore in order to interact with shared memory
  struct sembuf stuff;
  stuff.sem_op = -1;
  stuff.sem_num = 0;
  stuff.sem_flg = SEM_UNDO;
  semop(semid, &stuff, 1);

  //get new line from user
  char * lastline = shmat(shmid, 0, 0);
  printf("Last line: %s\n", lastline);
  printf("Enter a new line!: \n");
  char newline[9001];
  fgets(newline, 9001, stdin);
  int len = strlen(newline);
  newline[len] = '\0';

  strcpy(lastline, newline); //update shared memory

  write(fd, newline, len); //put new line in file

  close(fd);

  //change semaphore to indicate shared memory can be accessed again
  stuff.sem_op = 1;
  semop(semid, &stuff, 1);
  return 0;
}
