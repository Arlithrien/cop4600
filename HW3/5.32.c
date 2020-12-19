#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


int sumid=0;    
int waiting=0;   
semaphore mutex=1;   
semaphore OKToAccess=0;   

get_access(int id) 
{ 
     swait(mutex); 
     while(sumid+id > n) { 
         waiting++; 
         ssignal(mutex); 
         swait(OKToAccess); 
         swait(mutex); 
     } 
     sumid += id; 
     ssignal(mutex); 
}

release_access(int id) 
{ 
     int i; 
     swait(mutex); 
     sumid -= id; 
     for (i=0; i < waiting;++i) { 
         ssignal(OKToAccess); 
     } 
     waiting = 0; 
     ssignal(mutex); 
}

main() 
{ 
     get_access(id); 
     release_access(id); 
} 
 




