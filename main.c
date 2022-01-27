#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int rand_num(int data){
  int rand;
  int err = read(data, &rand, sizeof(rand));
  if(err == -1){
    printf("error: %s", strerror(errno));
    return 0;
  }
  return rand;
}

int main() {
  int rand1[10], i, err;
  printf("Generating random numbers:\n");
  int data = open("/dev/random", O_RDONLY);
  for(int i=0; i<10; i++){
    rand1[i] = rand_num(data);
    printf("\trandom %d: %u\n", i, rand1[i]);
  }

  printf("Writing numbers to file ...\n");
  int file = open("out.txt", O_CREAT | O_WRONLY | O_EXCL, 0644);
  if(file == -1){
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  err = write(file, rand1, sizeof(rand1));
  if(err == -1){
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  printf("Reading numbers from file...");
  file = open("out.txt", O_RDONLY);
  if(err == -1){
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  unsigned int rand2[10];
  err = read(file, rand2, sizeof(rand2));
  if(err == -1){
    printf("error: %s\n", strerror(errno));
    return 0;
  }

  printf("\nVerification that written values were the same\n");
  for(i=0; i<10; i++) printf("\trandom %d: %u\n", i , rand2[i]);
  
  return 0;
}
