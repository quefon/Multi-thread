#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

float global=0;
int num_loop;
int thread_num;
sem_t semaphores;

void thread(void)
{
  unsigned int t=time(NULL); 
  int i, count;
  double x, y;
  for (count=0, i = 0; i < num_loop/thread_num; i++)
  {
    x = rand_r(&t) / (double)RAND_MAX;
    y = rand_r(&t) / (double)RAND_MAX;
    if ((x *x + y * y) < 1)	
		count++;
  }	
  sem_wait(&semaphores);
    global+=count;
  sem_post(&semaphores);
}

int main(int argc,char *argv[]) 
{
  pthread_t id[10];
  int i;

  if(argc<3)
  {
    printf("only can input two argument\n");
    exit(1);
  }
  num_loop = atoi(argv[1]);
  thread_num = atoi(argv[2]);
	sem_init(&semaphores, 0, 1);	
  if(thread_num<1 && thread_num>10)
  {
    printf("you need input Thread_Number Between 1 ~ 10 in argv2");
    exit(1);
  }
  for(i=0; i<thread_num;i++)
  {
  	pthread_create(&id[i], NULL, (void *)thread, NULL);
  }
  for(i=0;i<thread_num;i++)
  {
    pthread_join(id[i],NULL);
  }
    
    printf("PI = %.8f\n", (double)4 *global / num_loop);
  return (0);
}
