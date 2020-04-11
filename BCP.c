
/*  Press ctrl + C to kill the process as the customer count is infinite loop*/

#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h> //sleep function

#include <sys/ipc.h>

#include <sys/sem.h>

#include <sys/shm.h>

#define CUSTOMERS 0 // Customer goes for infinite count

#define BARBERS 1  // Incase, if we want to change the number of barbers

#define MUTEX 2

#define CHAIRS 5  // change the customers count here !!!

void up(int sem_id,int sem_num,struct sembuf *semaphore) {

  semaphore->sem_num=sem_num;

  semaphore->sem_op=1;

  semaphore->sem_flg=0;

  semop(sem_id,semaphore,1);

}

void down(int sem_id,int sem_num,struct sembuf *semaphore) {

  semaphore->sem_num=sem_num;

  semaphore->sem_op=-1;

  semaphore->sem_flg=0;

  semop(sem_id,semaphore,1);

}

void initSem(int sem_id,int sem_num,int val) {

  union semnum {

    int val;

    struct semid_ds *buf;

    unsigned short *array;

  }argument;

  argument.val=val;

  semctl(sem_id,sem_num,SETVAL,argument);

}

int main() {

  int sem_key=1111,shm_key=2222;

  int sem_id,shm_id;

  int *waiting;

  struct sembuf semaphore;

  int count=1;

  shm_id=shmget(shm_key,sizeof(int),IPC_CREAT|0666);

  sem_id=semget(sem_key,3,IPC_CREAT|0666);

  waiting=shmat(shm_id,NULL,0);

  *waiting=0;

  initSem(sem_id,CUSTOMERS,0);

  initSem(sem_id,BARBERS,0);

  initSem(sem_id,MUTEX,1);

  printf("There are %d chairs.\n",CHAIRS);

  if(fork()) {

    /* The barber part. */

    while(1) {

      down(sem_id,CUSTOMERS,&semaphore);

      down(sem_id,MUTEX,&semaphore);

      *waiting=*waiting-1;

      up(sem_id,BARBERS,&semaphore);

      up(sem_id,MUTEX,&semaphore);

      printf("The barber is now cutting hair.\n");

      sleep(6);   /* Slowly cut the hair */

    }

  }

  else {

    /* The customer part. */

    while(1) {

      sleep(1);   /* Customers comes in fast */

      down(sem_id,MUTEX,&semaphore);

      if(*waiting < CHAIRS) {

      printf("Customer %d is seated.\n",count++);

      *waiting=*waiting+1;

      up(sem_id,CUSTOMERS,&semaphore);

      up(sem_id,MUTEX,&semaphore);

      }

      else if( *waiting == 0)
      {
        printf("Barber goes into sleep as there are no customers.");
      }

      else{

      printf("CUSTOMER %d LEFT THE SHOP AS THERE IS  NO FREE CHAIR \n",count++);

      up(sem_id,MUTEX,&semaphore);

      }

    }

  }

}
