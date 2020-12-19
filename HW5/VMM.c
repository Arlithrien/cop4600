#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define PAGE_SIZE 256; 
#define TLB_SIZE 16;
#define FRAME_SIZE 256;
#define FRAMES 256;
#define PHYSICAL_MEM FRAMES*FRAME_SIZE; 



int main(int argc, char *argv[]){

    int physical_memory[PHYSICAL_MEM];
    int virtual_memory[PAGE_SIZE][2];
    int tlb[TLB_SIZE][2];

    for(int i = 0; i < PAGE_SIZE; i++){
        virtual_memory[i][0] = (i > PHYSICAL_MEM - 1)? -1 : i;
        virtual_memory[i][1] = (i > PHYSICAL_MEM - 1)? -1 : PHYSICAL_MEM - i;
    }
    for(int i = 0; i < PHYSICAL_MEM; i++){
        physical_memory[i] = i;
    }

    for(int i = 0; i < TLB_SIZE; i++){
      tlb[i][0] = (i > TLB_SIZE - 1)? -1 : i;
      tlb[i][1] = (i > TLB_SIZE - 1)? -1 : TLB_SIZE - i;
    }

    if(argc != 2){
        printf("Incorrect Number of Arguments.\n");
        return 1;
    }

    FILE *addresses = fopen(argv[1], "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int pageNumber = 0;
    int physicalAddress = 0;
    int pageFaultCount = 0;
    double pageFaultRate = 0.0;

    
    printf("    Virtual Memory Manager    \n" );
    printf("Translating Addresses: \n\n");


    while((read = getline(&line, &len, addresses)) != -1){
        int offset = atoi(line) & 255;
        int page = atoi(line) & 65280;
        int page_table_number = page >> 8;
        int tlb_hit = 0;

        for(int i = 0; i < TLB_SIZE; i++){
         if(tlb[i][0] == page_table_number){
           tlb_hit = 1;
           printf("TLB HIT\n");
           break;
         }
       }

        if(virtual_memory[page_table_number][0] < 0 && !tlb_hit){
            pageFaultCount++;
            srand(time(NULL));
           int r = rand();

            int largest = 0;
            int evict = 0;
            for(int i = 0; i < PAGE_SIZE; i++){
                if(virtual_memory[i][1] > largest){
                    largest = virtual_memory[i][1];
                    evict = i;
                }
            }

            int tlb_replacement = r % 15;
            tlb[tlb_replacement][0] = page_table_number;
            tlb[tlb_replacement][1] = virtual_memory[evict][0];
            virtual_memory[page_table_number][0] = virtual_memory[evict][0];
            virtual_memory[page_table_number][1] = 0;
            virtual_memory[evict][0] = -1;
            virtual_memory[evict][1] = 0;
        }

        if (page < 100) {
            printf("Virtual Address = %d     \t", page);
        }
        else if (page < 1000) {
            printf("Virtual Address = %d   \t", page);
        }
        else {
            printf("Virtual Address = %d  \t", page);
        }


        physicalAddress = (physical_memory[virtual_memory[page_table_number][0]] * PAGE_SIZE) + offset;


        printf("Physical Address: %d\n", physicalAddress);


        pageNumber++;

        for(int i = 0; i < PAGE_SIZE; i++){
            virtual_memory[i][1]++;
        }
    }

    
    pageFaultRate = (double) pageFaultCount / 100000;
    printf("\nPage Fault Rate: %.2f%% \n", pageFaultRate);
    fclose(addresses);

    return 0;

}