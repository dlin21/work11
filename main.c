#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int rand_num(){
  int err = open("/dev/urandom", O_RDONLY);
  if(err == -1){
    printf("%s\n", strerror(errno));
    return 0;
  }
  unsigned int genRand = 0;
  // & operator copies a bit to the result
  read(err, &genRand, sizeof(&genRand));
  return genRand;
}

int main() {
  unsigned int rand1[10], i, err;

  printf("Generating random numbers:");
  for(i=0; i<10; i++) printf("\n\trandom %d: %u", i, rand1[i]);
  printf("\n");

  printf("\nWriting numbers to file ...");
  int file = open("out.txt", O_CREAT | O_RDWR, 0644);
  if(file == -1){
    printf("%s\n", strerror(errno));
    return 0;
  }
  err = write(file, rand1, sizeof(rand1));
  if(err == -1){
    printf("%s\n", strerror(errno));
    return 0;
  }
  printf("\n");

  printf("\nReading numbers from file...");
  file = open("out.txt", O_RDONLY);
  if(err == -1){
    printf("%s\n", strerror(errno));
    return 0;
  }
  unsigned int rand2[10];
  err = read(file, rand2, sizeof(rand2));
  if(err == -1){
    printf("%s\n", strerror(errno));
    return 0;
  }


  printf("\nVerification that written values were the same\n");
  for(i=0; i<10; i++) printf("\n\trandom %d: %u", i , rand2[i]);
  printf("\n");
}