#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <cstdlib>
#include <sys/sem.h>
#include <unistd.h>

#include "AirportAnimator.hpp"

using namespace std;

//airplanes are trying to get passengers
//passengers are like resources

//any number of passengers 88 or under can cause issues

  //our planes
  pthread_t plane[8];

//make this global so threads can change its value easily
int totalPass,
  toursDone = 0,
  totalTours;

  const int runwayKey = 1,
            passKey = 2;

   //Semaphore signals 
   struct sembuf semGo[1];
   struct sembuf semWait[1];

int semIDR,
    semIDP;


//Function for the planes (threads)
void *planeFunction (void *arg)
{
  //int* actualdata = (int *)person;
  // boarding process should be in here

  int sleepTime;
  int *planeNum = (int *) arg; // changes pointer to int

  while (toursDone < totalTours)
    {
      //boarding process

   AirportAnimator::updateStatus(*planeNum, "BOARD");
      
      for (int i = 0; i < 13; i++) 
	{
	  sleepTime = rand()%3;
	  sleep(sleepTime);
	  //updates passenger number on GUI for plane num
	  semop(semIDP, semWait,1);
	  AirportAnimator::updatePassengers(*planeNum, i);
	}

      AirportAnimator::updateStatus(*planeNum, "TAXI");
      AirportAnimator::taxiOut(*planeNum);

      //waits for runway semaphore
      semop(semIDR, semWait,1);
  
      AirportAnimator::updateStatus(*planeNum, "TKOFF");
      AirportAnimator::takeoff(*planeNum);
    
      AirportAnimator::updateStatus(*planeNum,"TOUR");
      semop(semIDR, semGo,1);
      sleepTime = (15+rand()%31);
      sleep(sleepTime);

      //check again if runway is empty


      AirportAnimator::updateStatus(*planeNum,"LNDRQ");
      sleep(2);

      //check to see if runway is empty
      semop(semIDR, semWait, 1);
  
      AirportAnimator::updateStatus(*planeNum,"LAND");
      AirportAnimator::land(*planeNum);

      toursDone++;
      AirportAnimator::updateTours(toursDone);

      AirportAnimator::updateStatus(*planeNum, "TAXI");

      //updates semaphore
      semop(semIDR, semGo,1);
  
      AirportAnimator::taxiIn(*planeNum);

      AirportAnimator::updateStatus(*planeNum, "DEPLN");

      //deboaring process
      for (int i = 0; i < 13; i++)
	{
	  AirportAnimator::updatePassengers(*planeNum, (12 - i));
	  sleep(1);
	  semop(semIDP, semGo,1);
	}
    }
 
}

//number of semaphores within
#define NUM_SEMAPHORES 1

int main(int argc, char *argv[])
{
  
  //atoi lets us store the char* in a int
  totalTours = atoi(argv[2]);

  totalPass = atoi(argv[1]);
  
  //creating our semaphore
  semIDP = semget(2, NUM_SEMAPHORES, IPC_CREAT|IPC_EXCL|0666); // for passengers

  if (semIDP < 0)
    semIDP = semget(2, NUM_SEMAPHORES, 0);
  
  semIDR = semget(1, NUM_SEMAPHORES, IPC_CREAT|IPC_EXCL|0666); // for runway

  if (semIDR < 0)
    semIDR = semget(1,  NUM_SEMAPHORES, 0);

  

  //initalize the semaphore
  semctl(semIDP, 0, SETVAL, totalPass);// totalPass = total number of passengers
  
  semctl(semIDR, 0, SETVAL, 1); // 1 because we only have one runway

   semGo[0].sem_num = 0;
   semGo[0].sem_op = 1;
   semGo[0].sem_flg = 0;

   semWait[0].sem_num = 0;
   semWait[0].sem_op = -1;
   semWait[0].sem_flg = 0;
   
  //GUI call 
  AirportAnimator::init();

  //used for the pthread_create
  int p1 = 0,
    p2 = 1,
    p3 = 2,
    p4 = 3,
    p5 = 4,
    p6 = 5,
    p7 = 6,
    p8 = 7;


  
   pthread_create (&plane[0], NULL, planeFunction, &p1);
   pthread_create (&plane[1], NULL, planeFunction, &p2);
   pthread_create (&plane[2], NULL, planeFunction, &p3);
   pthread_create (&plane[3], NULL, planeFunction, &p4);
   pthread_create (&plane[4], NULL, planeFunction, &p5);
   pthread_create (&plane[5], NULL, planeFunction, &p6);
   pthread_create (&plane[6], NULL, planeFunction, &p7);
   pthread_create (&plane[7], NULL, planeFunction, &p8);

   pthread_join(plane[0], NULL);
   pthread_join(plane[1], NULL);
   pthread_join(plane[2], NULL);
   pthread_join(plane[3], NULL);
   pthread_join(plane[4], NULL);
   pthread_join(plane[5], NULL);
   pthread_join(plane[6], NULL);
   pthread_join(plane[7], NULL);
   
  AirportAnimator::end();
  
  return 0;
}
