#include <stdio.h>
#include <stdlib.h>

int main(int address, char *argv[])
{
  unsigned long page_number;
  unsigned long offset;
  unsigned long address_location;
  address_location = atoll(argv[1]);
  page_number = address_location >> 12;
  offset = address_location & 0xfff;
  printf("The address %lu contains: \n", address_location);
  printf("page number = %lu \n", page_number);
  printf("offset = %lu \n", offset);
  return 0;
}
