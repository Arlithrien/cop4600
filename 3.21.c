#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int n;
int i;
int collatz(int n);

int main(void){
  printf("Enter a number greater than 1\n");
  scanf("%d", &i);
  while(i != 1){
      // fork();
      collatz(i);
  }
  // printf("Final Value: %d",i);
}

int collatz(int n){
  
    if(n%2==0){
      n/=2;
    }
    else
    {
        n = 3*n+1;
    }
    printf("%d\n", n);
   
  
  return n;
}