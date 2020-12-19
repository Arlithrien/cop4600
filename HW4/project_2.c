// Project 2 - The Dining Philosopher's Problem

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define P 5

int MAX_ITER = 100;
double wait_time_averages[P];
int philosopher_number[P] = {0, 1, 2, 3, 4};
enum{eating, hungry, thinking} state[P];
pthread_mutex_t mutex;
pthread_cond_t cond_var[P];
pthread_t philosophers[P];
int fed = 0;



void *dinner_time(void  *arg);
void *pickup_forks( int);
void *return_forks(int);
void *test(int);

int main()
{
  pthread_mutex_init(&mutex, NULL);
  int i=0;
  for(i-0;i<P;i++)
  {
    state[i] = thinking;
    pthread_cond_init(&cond_var[i], NULL);
    wait_time_averages[i] = 0.0;
  }
  for(i=0;i<P;i++)
  {
    pthread_create(&philosophers[i], NULL, dinner_time, &philosopher_number[i]);
  }
  for(i=0;i<P;i++)
  {
    pthread_join(philosophers[i], NULL);
    printf("Thread of Philosopher %d is finished executing \n", i+1);
  }

  printf("The hungry time averages of Philosophrs are : \n");

  for(i=0; i<P; i++){
    printf("Philosopher %d ---------------%f \n", i+1, wait_time_averages[i]);
  }
  return 0;
}

void *dinner_time(void *arg)
{
  int *temp = (int *)arg;
  int id = *temp;
  double total_wait_time = 0.0;
  time_t start_t, end_t;
  double wait_time;
  printf("Philosopher %d started working \n", id +1);
  time_t t;
  srand((unsigned)time(&t));

  for(int iter=0; iter<MAX_ITER; iter++)
  {
    printf("meal count = %d \n", fed);
    int random = (rand())%2 +1;
    printf("Philosopher %d has been thinking for %d seconds. \n", id+1, random);
    sleep(random);

    time(&start_t);
    pickup_forks(id);
    time(&end_t);
    wait_time = difftime(end_t, start_t);
    printf("Philosopher %d has been hungry for %f seconds. \n", id+1, wait_time);

    int random_time = (rand())%2 +1;
    sleep(random_time);
    printf("Philosopher %d is eating for the  %dth time for %d seconds. \n", id+1, iter+1, random_time);
    return_forks(id);
    fed++;
    total_wait_time = total_wait_time + wait_time;
  }

  wait_time_averages [id] = total_wait_time / 100.00;
  return NULL;
}

void *pickup_forks(int id)
{
  pthread_mutex_lock(&mutex);
  state[id] = hungry;
  pthread_mutex_unlock(&mutex);
  test(id);
  pthread_mutex_lock(&mutex);
  while(state[id] != eating)
  {
    pthread_cond_wait(&cond_var[id], &mutex);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void *return_forks(int id)
{
  pthread_mutex_lock(&mutex);
  state[id] = thinking;
  pthread_mutex_unlock(&mutex);
  test((id + P -1) %P);
  test((id + 1) %P);
}

void *test(int id)
{
  int is_even = (id % 2 ==0);
  int num1 = (id + P - 1) %P;
  int num2 = (id + 1) % P;
  if(is_even)
  {
    pthread_mutex_lock(&mutex);
    if((state[num1] != eating)&& (state[num2] != eating) && (state[id] == hungry))
    {
      state[id] = eating;
      pthread_cond_signal(&cond_var[id]);
    }
    pthread_mutex_unlock(&mutex);
  }
  else
  {
    pthread_mutex_lock(&mutex);
    if((state[num1] != eating) && (state[num2] != eating) && (state[id] == hungry))
    {
      state[id] = eating;
      pthread_cond_signal(&cond_var[id]);
    }
    pthread_mutex_unlock(&mutex);
  }
  
}
